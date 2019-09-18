/********************************************************
*   Copyright (C) 2017 All rights reserved.
*
*   Filename:CalState.c
*   Author  :叶鸿达
*   Date    :2017-04-27
*   Describe:计算器状态控制相关函数
*
********************************************************/
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "../include/CalcState.h"
#include "../include/CalcInput.h"
#include "../include/CalcExe.h"
#include "../include/CalcOutput.h"
#include "../include/calc_complex_debug.h"
#include "../include/DataCenter.h"

#define BUFSIZE 128

/*the major state*/
typedef enum {
    CALCSTATE_INIT = 0,
    CALCSTATE_MODESELECT,
    CALCSTATE_RUNNING,
    CALCSTATE_WAIT,
    CALCSTATE_EXIT,
    CALCSTATE_INVALID,
} CalcState_e;

/*the simple state*/
typedef enum {
    SIMPCALCSTATE_INIT = 0,
    SIMPCALCSTATE_INPUT_1ST,
    SIMPCALCSTATE_INPUT_OPERATOR,
    SIMPCALCSTATE_INPUT_2ND,
    SIMPCALCSTATE_CALCEXE,
    SIMPCALCSTATE_PRINTRESULT,
    SIMPCALCSTATE_WAIT,
    SIMPCALCSTATE_EXIT,
    SIMPCALCSTATE_INVALID,
} SimpCalcState_e;

/*the complex state*/
typedef enum {
    COMPCALCSTATE_INIT = 0,
    COMPCALCSTATE_INPUTMENU,
    COMPCALCSTATE_INPUTSTUDENTINFO,
    COMPCALCSTATE_PRINTSTUDENTINFO,
    COMPCALCSTATE_CALCAVERAGE,
    COMPCALCSTATE_CALCVARIANCE,
    COMPCALCSTATE_PRINTAVERAGE,
    COMPCALCSTATE_PRINTVARIANCE,
    COMPCALCSTATE_EXIT,
    COMPCALCSTATE_FAIL,
    COMPCALCSTATE_INVALID,
} CompCalcState_e;

typedef struct StateControl_t_ {
    int iCurState;
    int (* pfDoCurState[])(int iState);
} StateControl_t;

/*the major state */
int CalcState_Init(int iState);
int CalState_UserModeSelect(int iState);
int CalcState_Running(int iState);
int CalcState_Wait(int iState);
int CalcState_Exit(int iState);

/*the simple state*/
void SimCalcState_Main(void);
int SimCalcState_Init(int iState);
int SimCalState_Input1stNum(int iState);
int SimCalState_Input_Operator(int iState);
int SimCalState_Input2stNum(int iState);
int SimCalState_Calculating(int iState);
int SimCalState_CalcDone(int iState);
int SimCalState_Wait(int iState);
int SimCalState_Exit(int state);

/*the complex state*/
void CompCalcState_Main(void);
int ComCalcState_Init(int iState);
int ComCalcState_InputMenu(int iState);
/*selcec the calculator statistical*/
int ComCalcState_StatMethodSel(char * cpcStatMethod);
int ComCalcState_StatMethodSelISI(int iState);
int ComCalcState_StatMethodSelPSI(int iState);
int ComCalcState_StatMethodSelCA(int iState);
int ComCalcState_StatMethodSelCV(int iState);
int ComCalcState_StatMethodSelPA(int iState);
int ComCalcState_StatMethodSelPV(int iState);
int ComCalcState_StatMethodSelE(int iState);
int ComCalcState_StatMethodSelFail(int iState);

//int CalcState_GetCurState(CalState_E *epState);

StateControl_t g_stCalcState = {
    CALCSTATE_INIT,
    {
        CalcState_Init,
        CalState_UserModeSelect,
        CalcState_Running,
        CalcState_Wait,
        CalcState_Exit,
    },
};

StateControl_t g_stSimpCalcState = {
    SIMPCALCSTATE_INIT,
    {
        SimCalcState_Init,
        SimCalState_Input1stNum,
        SimCalState_Input_Operator,
        SimCalState_Input2stNum,
        SimCalState_Calculating,
        SimCalState_CalcDone,
        SimCalState_Wait,
        SimCalState_Exit,
    },
};

StateControl_t g_stCompCalcState = {
    SIMPCALCSTATE_INIT,
    {
        ComCalcState_Init,
        ComCalcState_InputMenu,
        ComCalcState_StatMethodSelISI,
        ComCalcState_StatMethodSelPSI,
        ComCalcState_StatMethodSelCA,
        ComCalcState_StatMethodSelCV,
        ComCalcState_StatMethodSelPA,
        ComCalcState_StatMethodSelPV,
        ComCalcState_StatMethodSelE,
        ComCalcState_StatMethodSelFail,
    },
};
                                
/************************************************************
 * FUNCTION:CalcState_Maint()
 * Description:该函数主要用来进行主状态机的控制
 * Arguments:无
 * return:无返回值
 * *********************************************************/
void CalcState_Main(void)
{
    while (g_stCalcState.iCurState != CALCSTATE_INVALID)
    {
        g_stCalcState.iCurState = g_stCalcState.pfDoCurState[g_stCalcState.iCurState](g_stCalcState.iCurState);
    };
    g_stCalcState.iCurState = CALCSTATE_INIT;
}


/************************************************************
 * FUNCTION:CalState_Init()
 * Description:该函数主要用来初始化主状态机的初始状态
 * Arguments[iState][In]:进行状态与执行函数的对应关系检查
 * return:
 * *********************************************************/
int CalcState_Init(int iState)
{
    if (iState != CALCSTATE_INIT)
    {
        calc_error("[%s]g_stCalcState init is fail!\n", __FUNCTION__);
        exit(-1);
    }

    int iRet = DATACENTER_RET_OK;

    /*create StateMacMajorModeSelCreate DataCenter*/
    iRet = DataCenter_StateMacMajorModeSelCreateDataCenter();
    if (iRet == DATACENTER_RET_FAIL)
    {
        calc_error("[%s]DataCenter_StateMacMajorModeSelCreateDataCenter is fail!\n", __FUNCTION__);
        return CALCSTATE_INIT;
    }
    
    return CALCSTATE_MODESELECT;
}

/************************************************************
 * FUNCTION:CalState_UserModeSelect()
 * Description:该函数主要用来进行计算器工作模式的选取
 * Arguments[iState][In]:进行状态与执行函数的对应关系检查
 * return:主状态机的下一次状态
 * *********************************************************/
int CalState_UserModeSelect(int iState)
{
    if (iState != CALCSTATE_MODESELECT)
    {
        calc_error("[%s]g_stCalcState init is fail!\n", __FUNCTION__);
        exit(-1);
    }

    char cSelectMode = '\0';
    int iRet = CALCSTATE_RET_OK;

    CalcOutput_HintMsg(CALCSTRING_SELECT_MODE); 

    iRet = CalcInput_Char(&cSelectMode);
    if (iRet == CALCINPUT_RET_FAIL)
    {
        calc_error("[%s]CalcInput_Char read is fail!\n", __FUNCTION__);  
        return CALCSTATE_MODESELECT;
    }

    /*write SelectMode to datacenter to save*/
    iRet = DataCenter_WriteStateMacMajorModeSel(&cSelectMode, DATA_SELECTMODE_DEFAULT);
    if (iRet == DATACENTER_RET_FAIL)
    {
        calc_error("[%s]DataCenter_WriteStateMacMajorModeSel is fail!\n", __FUNCTION__);   
        return CALCSTATE_RET_FAIL;
    }
    
    return CALCSTATE_RUNNING;   
}

/************************************************************
 * FUNCTION:CalcState_Running()
 * Description:该函数主要用来执行计算机相应的工作模式
 * Arguments[iState][In]:进行状态与执行函数的对应关系检查
 * return:主状态机的下一次状态
 * *********************************************************/
int CalcState_Running(int iState)
{
    if (iState != CALCSTATE_RUNNING)
    {
        calc_error("[%s]g_stCalcState init is fail!\n", __FUNCTION__);
        exit(-1);
    } 

    int iRet = DATACENTER_RET_OK;
    char cSelectMode = '\0';

    /*read SelectMode from datacenter*/
    iRet = DataCenter_ReadStateMacMajorModeSel(&cSelectMode, DATA_SELECTMODE_DEFAULT);
    if (iRet == DATACENTER_RET_FAIL)
    {
        calc_error("[%s]DataCenter_ReadStateMacMajorModeSel is fail!\n", __FUNCTION__);   
        return CALCSTATE_RET_FAIL;
    }

    /*if select the simple mode and output the hing message*/
    if (cSelectMode == 'S')
    {
        CalcOutput_HintMsg(CALCSTRING_SIMPLE_CALC_RUNNING);
        SimCalcState_Main();
    }
    /*if select the complex mode and output the hing message*/
    else if (cSelectMode == 'C')
    {
        CalcOutput_HintMsg(CALCSTRING_COMPLEX_CALC_RUNNING);
        CompCalcState_Main();
    }
    else
    {
        CalcOutput_HintMsg(CALCSTRING_CALC_MODE_INVAILD_SELECT_AGAIN);
        return CALCSTATE_MODESELECT;
    }

    return CALCSTATE_WAIT; 
}

/************************************************************
 * FUNCTION:CalcState_Wait()
 * Description:该函数跳转到exit状态
 * Arguments[iState][In]:进行状态与执行函数的对应关系检查
 * return:主状态机的下一次状态
 * *********************************************************/
int CalcState_Wait(int iState)
{
    if (iState != CALCSTATE_WAIT)
    {
        calc_error("[%s]g_stCalcState init is fail!\n", __FUNCTION__);
        exit(-1);
    }

    return CALCSTATE_EXIT;
}

/************************************************************
 * FUNCTION:CalcState_Exit()
 * Description:该函数返回计算器工作模式的选取
 * Arguments[iState][In]:进行状态与执行函数的对应关系检查
 * return:主状态机的下一次状态
 * *********************************************************/
 int CalcState_Exit(int iState)
{
    if (iState != CALCSTATE_EXIT)
    {
        calc_error("[%s]g_stCalcState init is fail!\n", __FUNCTION__);
        exit(-1);
    } 

    int iRet = DATACENTER_RET_OK;

    /*create StateMacMajorModeSelCreate DataCenter*/
    iRet = DataCenter_StateMacMajorModeSelDestoryDataCenter();
    if (iRet == DATACENTER_RET_FAIL)
    {
        calc_error("[%s]DataCenter_StateMacMajorModeSelDestoryDataCenter is fail!\n", __FUNCTION__);
        return CALCSTATE_EXIT;
    }

    return CALCSTATE_INIT;
}


/************************************************************
 * FUNCTION:CalcState_SimpleMode()
 * Description:计算器工作在简单模式下的状态机控制
 * Arguments:无
 * return:无
 * *********************************************************/
void SimCalcState_Main(void)
{
    while (g_stSimpCalcState.iCurState != SIMPCALCSTATE_INVALID)
    {
        g_stSimpCalcState.iCurState = g_stSimpCalcState.pfDoCurState[g_stSimpCalcState.iCurState](g_stSimpCalcState.iCurState);
    };
    g_stSimpCalcState.iCurState = SIMPCALCSTATE_INIT;
}

/************************************************************
 * FUNCTION:SimCalcState_Init()
 * Description:该函数用来进行计算器简单模式状态初始化
 * Arguments[iState][In]:进行状态与执行函数的对应关系检查
 * return:计算器简单模式状态机的下一次状态
 * *********************************************************/
int SimCalcState_Init(int iState)
{
    if (iState != SIMPCALCSTATE_INIT)
    {
        calc_error("[%s]g_stSimpCalcState init is fail!\n", __FUNCTION__);
        exit(-1);
    }  

    int iRet = DATACENTER_RET_OK;
    
    iRet = DataCenter_CalcSimModeOperandCreateDataCenter();
    if (iRet == DATACENTER_RET_FAIL)
    {
        calc_error("[%s]DataCenter_CalcSimModeOperandCreateDataCenter is fail!\n", __FUNCTION__);
        return SIMPCALCSTATE_INIT;
    }   


    return SIMPCALCSTATE_INPUT_1ST;   
}

/************************************************************
 * FUNCTION:SimCalState_Input1stNum()
 * Description:该函数是状态机中的对第一个数字接受并且处理的动作函数
 * Arguments[iState][In]:进行状态与执行函数的对应关系检查
 * return:计算器简单模式状态机的下一次状态
 * *********************************************************/
int SimCalState_Input1stNum(int iState)
{
    if (iState != SIMPCALCSTATE_INPUT_1ST)
    {
        calc_error("[%s]g_stSimpCalcState init is fail!\n", __FUNCTION__);
        exit(-1);
    } 

    unsigned int iInputInt = 0;
    unsigned int iRet = CALCSTATE_RET_OK;
    SimpleModeCalc_St stSimModeCalcOperand;

    CalcOutput_HintMsg(CALCSTRING_INPUT_1ST);
    /*1st number string check*/
    iRet = CalcInput_Int(&iInputInt);
    if (iRet == CALCSTATE_RET_OK)
    {
        /*save the 1stNum to the datacenter*/
        memset(&stSimModeCalcOperand, 0, sizeof(stSimModeCalcOperand));
        stSimModeCalcOperand.gui1stNum = iInputInt;
        iRet = DataCenter_WriteCalcSimModeOperand(stSimModeCalcOperand, DATA_CALCSIMPLE_WRITE_1STNUM);
        if (iRet == DATACENTER_RET_FAIL)
        {
            calc_error("[%s]DataCenter_WriteCalcSimModeOperand is fail!\n", __FUNCTION__);
            return SIMPCALCSTATE_INPUT_1ST;
        }
        return SIMPCALCSTATE_INPUT_OPERATOR;
    }
    else if (iRet == CALCINPUT_RET_INPUT_INVALID)
    {
        CalcOutput_HintMsg(CALCSTRING_INPUT_1ST_AGAIN);
        return SIMPCALCSTATE_INPUT_1ST;
    }
    else if (iRet == CALCINPUT_RET_INPUT_OUTOFRANGE)
    {
        CalcOutput_HintMsg(CALCSTRING_INPUT_1ST_AGAIN);
        return SIMPCALCSTATE_INPUT_1ST;
    }
    else
    {
        CalcOutput_HintMsg(CALCSTRING_INPUT_1ST_AGAIN);
        return SIMPCALCSTATE_INPUT_1ST;
    }
}

/************************************************************
 * FUNCTION:SimCalState_Operator()
 * Description:该函数是状态机中的对操作符接受并且处理的动作函数
 * Arguments[iState][In]:进行状态与执行函数的对应关系检查
 * return:计算器简单模式状态机的下一次状态
 * *********************************************************/
int SimCalState_Input_Operator(int iState)
{
    if (iState != SIMPCALCSTATE_INPUT_OPERATOR)
    {
        calc_error("[%s]g_stSimpCalcState init is fail!\n", __FUNCTION__);
        exit(-1);
    }

    char cOperator = '\0';
    unsigned int iRet = CALCSTATE_RET_OK;
    SimpleModeCalc_St stSimModeCalcOperand;

    CalcOutput_HintMsg(CALCSTRING_INPUT_OPERATOR);

    iRet = CalcInput_Char(&cOperator);
    if (iRet == CALCSTATE_RET_OK)
    {
        iRet = CalcInput_OperatorCheck(&cOperator);
        if (iRet == CALCINPUT_RET_OK)
        {
            /*save the operator to the datacenter*/
            memset(&stSimModeCalcOperand, 0, sizeof(stSimModeCalcOperand));
            stSimModeCalcOperand.gcOperator = cOperator;
            iRet = DataCenter_WriteCalcSimModeOperand(stSimModeCalcOperand, DATA_CALCSIMPLE_WRITE_OPERATOR);
            if (iRet == DATACENTER_RET_FAIL)
            {
                calc_error("[%s]DataCenter_WriteCalcSimModeOperand is fail!\n", __FUNCTION__);
                return SIMPCALCSTATE_INPUT_OPERATOR;
            }
            return SIMPCALCSTATE_INPUT_2ND;
        }
        else
        {
            CalcOutput_HintMsg(CALCSTRING_INPUT_OPERATOR_AGAIN);
            return SIMPCALCSTATE_INPUT_OPERATOR;
        }
    }
    else
    {
        CalcOutput_HintMsg(CALCSTRING_INPUT_OPERATOR_AGAIN);
        return SIMPCALCSTATE_INPUT_OPERATOR;
    }
}


/************************************************************
 * FUNCTION:SimCalState_Input2stNum()
 * Description:该函数是状态机中的对第二个数字接受并且处理的动作函数
 * Arguments[iState][In]:进行状态与执行函数的对应关系检查
 * return:计算器简单模式状态机的下一次状态
 * *********************************************************/
int SimCalState_Input2stNum(int iState)
{
    if (iState != SIMPCALCSTATE_INPUT_2ND)
    {
        calc_error("[%s]g_stSimpCalcState init is fail!\n", __FUNCTION__);
        exit(-1);
    }

    unsigned int iInputInt = 0;
    unsigned int iRet = CALCSTATE_RET_OK;
    SimpleModeCalc_St stSimModeCalcOperand;

    CalcOutput_HintMsg(CALCSTRING_INPUT_2ST);
    /*2nd number string check*/
    iRet = CalcInput_Int(&iInputInt);
    if (iRet == CALCSTATE_RET_OK)
    {
        /*save the 2ndNum to the datacenter*/
        memset(&stSimModeCalcOperand, 0, sizeof(stSimModeCalcOperand));
        stSimModeCalcOperand.gui2ndNum = iInputInt;
        iRet = DataCenter_WriteCalcSimModeOperand(stSimModeCalcOperand, DATA_CALCSIMPLE_WRITE_2NDNUM);
        if (iRet == DATACENTER_RET_FAIL)
        {
            calc_error("[%s]DataCenter_WriteCalcSimModeOperand is fail!\n", __FUNCTION__);
            return SIMPCALCSTATE_INPUT_2ND;
        }
        return SIMPCALCSTATE_CALCEXE;
    }
    else if (iRet == CALCINPUT_RET_INPUT_OUTOFRANGE)
    {
        CalcOutput_HintMsg(CALCSTRING_INPUT_2ST_AGAIN);
        return SIMPCALCSTATE_INPUT_2ND;
    }
    else if (iRet == CALCINPUT_RET_INPUT_OUTOFRANGE)
    {
        CalcOutput_HintMsg(CALCSTRING_INPUT_2ST_AGAIN);
        return SIMPCALCSTATE_INPUT_2ND;
    }
    else
    {
        CalcOutput_HintMsg(CALCSTRING_INPUT_2ST_AGAIN);
        return SIMPCALCSTATE_INPUT_2ND;
    }
}

/************************************************************
 * FUNCTION:SimCalState_Calculating()
 * Description:该函数是状态机中进行计算的动作函数
 * Arguments[iState][In]:进行状态与执行函数的对应关系检查
 * return:计算器简单模式状态机的下一次状态
 * *********************************************************/
int SimCalState_Calculating(int iState)
{
    if (iState != SIMPCALCSTATE_CALCEXE)
    {
        calc_error("[%s]g_stSimpCalcState init is fail!\n", __FUNCTION__);
        exit(-1);
    }

    unsigned int iRet = CALCSTATE_RET_OK;
    SimpleModeCalc_St stSimModeCalcOperand;


    /*read the SimModeCalcOperand from the datacenter*/
    memset(&stSimModeCalcOperand, 0, sizeof(stSimModeCalcOperand));
    iRet = DataCenter_ReadCalcSimModeOperand(&stSimModeCalcOperand, DATA_CALCSIMPLE_DEFAULT);
    if (iRet == DATACENTER_RET_FAIL)
    {
        calc_error("[%s]DataCenter_ReadCalcSimModeOperand is fail!\n", __FUNCTION__);
        return SIMPCALCSTATE_CALCEXE;
    }

    calc_printf("%d, %c, %d\n", stSimModeCalcOperand.gui1stNum, 
                                stSimModeCalcOperand.gcOperator,
                                stSimModeCalcOperand.gui2ndNum);
    
    switch (stSimModeCalcOperand.gcOperator)
    {
        case OPERATOR_PLUS:
            iRet = Calculating_Sum(&stSimModeCalcOperand.gui1stNum, 
                                   &stSimModeCalcOperand.gui2ndNum, 
                                   &stSimModeCalcOperand.guiResult);
            break;
        case OPERATOR_MUB:
            iRet = Calculating_Mub(&stSimModeCalcOperand.gui1stNum, 
                                   &stSimModeCalcOperand.gui2ndNum, 
                                   &stSimModeCalcOperand.guiResult);
            break;
        case OPERATOR_MUL:
            iRet = Calculating_Mul(&stSimModeCalcOperand.gui1stNum, 
                                   &stSimModeCalcOperand.gui2ndNum, 
                                   &stSimModeCalcOperand.guiResult);
            break;
        case OPERATOR_DIV:
            iRet = Calculating_Div(&stSimModeCalcOperand.gui1stNum, 
                                   &stSimModeCalcOperand.gui2ndNum, 
                                   &stSimModeCalcOperand.guiResult);
            break;
        default:
            break;
    }

    if (iRet == CALCSTATE_RET_OK)
    {
        /*save the result to the datacenter*/
        iRet = DataCenter_WriteCalcSimModeOperand(stSimModeCalcOperand, DATA_CALCSIMPLE_WRITE_RESULT);
        if (iRet == DATACENTER_RET_FAIL)
        {
            calc_error("[%s]DataCenter_WriteCalcSimModeOperand is fail!\n", __FUNCTION__);
            return SIMPCALCSTATE_CALCEXE;
        }
    
        return SIMPCALCSTATE_PRINTRESULT;
    }
    else if (iRet == CALCEXE_RET_FAIL_1ST_LESS_2ND)
    {
        CalcOutput_HintMsg(CALCSTRING_INPUT_2ST_AGAIN);
        return SIMPCALCSTATE_INPUT_2ND;
    }
    else if (iRet == CALCEXE_RET_FAIL_DENOMINATOR_ZERO)
    {
        CalcOutput_HintMsg(CALCSTRING_INPUT_2ST_AGAIN);
        return SIMPCALCSTATE_INPUT_2ND;
    }
    else
    {
        CalcOutput_HintMsg(CALCSTRING_INPUT_2ST_AGAIN);
        return SIMPCALCSTATE_INPUT_2ND;
    }
}

/************************************************************
 * FUNCTION:SimCalState_CalcDone()
 * Description:该函数是状态机中计算完毕后动作函数
 * Arguments[iState][In]:进行状态与执行函数的对应关系检查
 * return:计算器简单模式状态机的下一次状态
 * *********************************************************/
int SimCalState_CalcDone(int iState)
{
    if (iState != SIMPCALCSTATE_PRINTRESULT)
    {
        calc_error("[%s]g_stSimpCalcState init is fail!\n", __FUNCTION__);
        exit(-1);
    }

    SimpleModeCalc_St stSimModeCalcOperand;
    unsigned int iRet = CALCSTATE_RET_OK;
    char cQuit;

    /*read the SimModeCalcOperand from the datacenter*/
    memset(&stSimModeCalcOperand, 0, sizeof(stSimModeCalcOperand));
    iRet = DataCenter_ReadCalcSimModeOperand(&stSimModeCalcOperand, DATA_CALCSIMPLE_DEFAULT);
    if (iRet == DATACENTER_RET_FAIL)
    {
        calc_error("[%s]DataCenter_ReadCalcSimModeOperand is fail!\n", __FUNCTION__);
        return SIMPCALCSTATE_CALCEXE;
    }

    /*Output the result message*/
    CalcOutput_Result(stSimModeCalcOperand.gui1stNum, 
                      stSimModeCalcOperand.gcOperator, 
                      stSimModeCalcOperand.gui2ndNum, 
                      stSimModeCalcOperand.guiResult);

    /*Output the hint message*/
    CalcOutput_HintMsg(CALCSTRING_CONTINUE_OR_EXIT);

    /*read char about wheather quit*/
    iRet = CalcInput_Char(&cQuit);
    if (iRet == CALCINPUT_RET_OK)
    {
        if (cQuit != 'E')
        {
            return SIMPCALCSTATE_INPUT_1ST;
        }
        else
        {
            return SIMPCALCSTATE_WAIT;
        }
    }
}

/************************************************************
 * FUNCTION:SimCalState_Wait()
 * Description:该函数用来转移到下一个退出状态
 * Arguments[iState][In]:进行状态与执行函数的对应关系检查
 * return:计算器简单模式状态机的下一次状态
 * *********************************************************/
int SimCalState_Wait(int iState)
{
    if (iState != SIMPCALCSTATE_WAIT)
    {
        calc_error("[%s]g_stSimpCalcState init is fail!\n", __FUNCTION__);
        exit(-1);
    }

    return SIMPCALCSTATE_EXIT;
}

/************************************************************
 * FUNCTION:SimCalState_Exit()
 * Description:该函数用来退出简单模式
 * Arguments[iState][In]:进行状态与执行函数的对应关系检查
 * return:计算器简单模式状态机的下一次状态
 * *********************************************************/
int SimCalState_Exit(int iState)
{
    if (iState != SIMPCALCSTATE_EXIT)
    {
        calc_error("[%s]g_stSimpCalcState init is fail!\n", __FUNCTION__);
        exit(-1);
    }
    int iRet = DATACENTER_RET_OK;
    
    iRet = DataCenter_CalcSimModeOperandDestoryDataCenter();
    if (iRet == DATACENTER_RET_FAIL)
    {
        calc_error("[%s]DataCenter_CalcSimModeOperandDestoryDataCenter is fail!\n", __FUNCTION__);
        return SIMPCALCSTATE_EXIT;
    }

    return SIMPCALCSTATE_INVALID;
}

/************************************************************
 * FUNCTION:ComCalcState_ComplexMode()
 * Description:计算器工作在复杂模式下状态机控制
 * Arguments:无
 * return:无返回值
 * *********************************************************/
void CompCalcState_Main(void)
{
    while (g_stCompCalcState.iCurState != COMPCALCSTATE_INVALID)
    {
        g_stCompCalcState.iCurState = g_stCompCalcState.pfDoCurState[g_stCompCalcState.iCurState](g_stCompCalcState.iCurState);
    };
    g_stCompCalcState.iCurState = COMPCALCSTATE_INIT;
}

/************************************************************
 * FUNCTION:ComCalcState_Init()
 * Description:该函数用来对计算机复杂模式状态机初始状态进行初始化
 * Arguments[iState][In]:进行状态与执行函数的对应关系检查
 * return:计算器复杂模式状态机的下一次状态
 * *********************************************************/
int ComCalcState_Init(int state)
{
    if (state != COMPCALCSTATE_INIT)
    {
        calc_error("[%s]g_stCompCalcState init is fail!\n", __FUNCTION__);
        exit(-1);
    }  

    int iRet = DATACENTER_RET_OK;

    iRet = DataCenter_CalcComplexModeCreateDataCenter();
    if (iRet == DATACENTER_RET_FAIL)
    {
        calc_error("[%s]DataCenter_CalcComplexModeCreateDataCenter is fail!\n", __FUNCTION__);
        return COMPCALCSTATE_INIT;
    }

    calc_printf("DataCenter_CalcComplexModeCreateDataCenter is create!\n");
        

    return COMPCALCSTATE_INPUTMENU;   
}

/************************************************************
 * FUNCTION:ComCalcState_InputMenu()
 * Description:该函数用来选择复杂模式的工作状态
 * Arguments[iState][In]:进行状态与执行函数的对应关系检查
 * return:主状态机的下一次状态
 * *********************************************************/
int ComCalcState_InputMenu(int iState)
{
    if (iState != COMPCALCSTATE_INPUTMENU)
    {
        calc_error("[%s]g_stCompCalcState init is fail!\n", __FUNCTION__);
        exit(-1);
    }  

    char cStatMethod_a[BUFSIZE];
    int iRet = CALCINPUT_RET_OK;

    CalcOutput_HintMsg(CALCSTRING_COMPLEX_MODE_STATISTICAL_METHOD);

    /*read statistical select string*/
    memset(cStatMethod_a, 0, sizeof(cStatMethod_a));
    iRet = CalcInput_String(cStatMethod_a);
    if (iRet == CALCINPUT_RET_FAIL)
    {
        calc_error("[%s]CalcInput_String read string is fail!\n", __FUNCTION__);
        return COMPCALCSTATE_INPUTMENU;
    }

    /*selcet statistical work mode*/
    iRet = ComCalcState_StatMethodSel(cStatMethod_a);
    switch (iRet)
    {
        case COMPCALCSTATE_INPUTMENU:
            return COMPCALCSTATE_INPUTMENU;
        case COMPCALCSTATE_INPUTSTUDENTINFO:
            return COMPCALCSTATE_INPUTSTUDENTINFO;
        case COMPCALCSTATE_PRINTSTUDENTINFO:
            return COMPCALCSTATE_PRINTSTUDENTINFO;
        case COMPCALCSTATE_CALCAVERAGE:
            return COMPCALCSTATE_CALCAVERAGE;
        case COMPCALCSTATE_CALCVARIANCE:
            return COMPCALCSTATE_CALCVARIANCE;
        case COMPCALCSTATE_PRINTAVERAGE:
            return COMPCALCSTATE_PRINTAVERAGE;
        case COMPCALCSTATE_PRINTVARIANCE:
            return COMPCALCSTATE_PRINTVARIANCE;
        case COMPCALCSTATE_EXIT:
            return COMPCALCSTATE_EXIT;
        case COMPCALCSTATE_FAIL:
            return COMPCALCSTATE_FAIL;
    }
}

/************************************************************
 * FUNCTION:ComCalcstate_StatMethodSel()
 * Description:该函数是用来选择计算器在复杂模式下的统计方法
 * Arguments:
 Arg1[cpcStatMethod][In]:存储用户输入的选择后的统计方法字符串
 * return:success depend on the statmethod return, fail return CALCSTATE_RET_FAIL
 * *********************************************************/
int ComCalcState_StatMethodSel(char * cpcStatMethod)
{
    if (cpcStatMethod == NULL)
    {
        calc_error("[%s]Input parameter is error!\n", __FUNCTION__);;
        return COMPCALCSTATE_INVALID;
    }

    if (strncmp(cpcStatMethod, "ISI", 3) == 0 && cpcStatMethod[3] == '\0')
    {
        return COMPCALCSTATE_INPUTSTUDENTINFO;
    }
    else if (strncmp(cpcStatMethod, "PSI", 3) == 0 && cpcStatMethod[3] == '\0')
    {
        return COMPCALCSTATE_PRINTSTUDENTINFO;
    }
    else if (strncmp(cpcStatMethod, "CA", 2) == 0 && cpcStatMethod[2] == '\0')
    {
        return COMPCALCSTATE_CALCAVERAGE;
    }
    else if (strncmp(cpcStatMethod, "CV", 2) == 0 && cpcStatMethod[2] == '\0')
    {
        return COMPCALCSTATE_CALCVARIANCE;
    }
    else if (strncmp(cpcStatMethod, "PA", 2) == 0 && cpcStatMethod[2] == '\0')
    {
        return COMPCALCSTATE_PRINTAVERAGE;
    }
    else if (strncmp(cpcStatMethod, "PV", 2) == 0 && cpcStatMethod[2] == '\0')
    {
        return COMPCALCSTATE_PRINTVARIANCE;
    }
    else if (strncmp(cpcStatMethod, "E", 1) == 0 && cpcStatMethod[1] == '\0')
    {
        return COMPCALCSTATE_EXIT;
    }
    else
    {
        return COMPCALCSTATE_FAIL;
    }
}

/************************************************************
 * FUNCTION:ComCalcstate_StatMethodSelISI()
 * Description:输入学生信息
 * Arguments[iState][In]:进行状态与执行函数的对应关系检查
 * return:计算器复杂模式状态机的下一次状态
 * *********************************************************/
int ComCalcState_StatMethodSelISI(int iState)
{
    if (iState != COMPCALCSTATE_INPUTSTUDENTINFO)
    {
        calc_error("[%s]g_stCompCalcState init is fail!\n", __FUNCTION__);
        exit(-1);
    } 

    Stu_E stStuInfo; 
    Class_St stClass;
    int iRet = CALCINPUT_RET_OK;

    CalcOutput_HintMsg(CALCSTRING_COMPLEX_MODE_INPUT_STU_INFO_SCORE_NAME);

    while (1)
    {
        memset(&stStuInfo, 0, sizeof(stStuInfo));
        memset(&stClass, 0, sizeof(stClass));
        iRet = CalcInput_StuInfo(&stStuInfo);
        if (iRet == CALCINPUT_RET_OK)
        {   
            /*read current student number from datacenter and create buffer*/
            iRet = DataCenter_ReadCalcComplexModeClassInfo(&stClass, DATA_CALCCOMPLEX_DEFAULT);
            if (iRet == DATACENTER_RET_FAIL)
            {
                calc_error("[%s]DataCenter_ReadClassInfo is fail!\n", __FUNCTION__);
                return COMPCALCSTATE_INPUTSTUDENTINFO;
            }
            calc_printf("stStuInfo.gcStuName = %s\n stStuInfo.uiChineseScore = %d\n stStuInfo.uiMathScore = %d\n stStuInfo.uiEnglishScore = %d\n", 
                        stStuInfo.gcStuName, stStuInfo.uiChineseScore,
                        stStuInfo.uiMathScore, stStuInfo.uiEnglishScore);            
           
            if (stClass.guiCurStuNumCount < 5)
            {
                stClass.stStu_a[0] = stStuInfo;
                /*save student information to datacenter*/
                iRet = DataCenter_WriteCalcComplexModeClassInfo(stClass, DATA_CALCCOMPLEX_WRITE_STUINFO);
                if (iRet == DATACENTER_RET_FAIL)
                {
                    calc_error("[%s]DataCenter_WriteClassInfo is fail!\n", __FUNCTION__);
                    return COMPCALCSTATE_INPUTSTUDENTINFO;
                }
                break;
            }
            else
            {
                calc_error("Erro:Student count out of range\n!");
                break;
            }
        }
        else if (iRet == CALCINPUT_RET_FAIL)
        {
            continue ;
        }   
    }

    return COMPCALCSTATE_INPUTMENU;
}

/************************************************************
 * FUNCTION:ComCalcstate_StatMethodSelPSI()
 * Description:打印学生信息
 * Arguments[iState][In]:进行状态与执行函数的对应关系检查
 * return:计算器复杂模式状态机的下一次状态
 * *********************************************************/
int ComCalcState_StatMethodSelPSI(int iState)
{
    if (iState != COMPCALCSTATE_PRINTSTUDENTINFO)
    {
        calc_error("[%s]g_stCompCalcState init is fail!\n", __FUNCTION__);
        exit(-1);
    } 

    Class_St stClass;
    int iRet = DATACENTER_RET_OK;

    memset(&stClass, 0, sizeof(stClass));
    /*read current number from datacenter*/
    iRet = DataCenter_ReadCalcComplexModeClassInfo(&stClass, DATA_CALCCOMPLEX_DEFAULT);
    if (iRet == DATACENTER_RET_FAIL)
    {
        calc_error("[%s]DataCenter_ReadClassInfo is fail!\n", __FUNCTION__);
        return COMPCALCSTATE_PRINTSTUDENTINFO;
    }

    if (stClass.guiCurStuNumCount == 0)
    {
        calc_error("Error:Student list is null!\n");
        return COMPCALCSTATE_INPUTMENU;
    }
    
    for (int i = 0; i < stClass.guiCurStuNumCount; i++)
    {
        calc_running("name[   %8s] : chinese[ %d] math[ %d] english[ %d]\n",
                        stClass.stStu_a[i].gcStuName, 
                        stClass.stStu_a[i].uiChineseScore,     
                        stClass.stStu_a[i].uiMathScore,
                        stClass.stStu_a[i].uiEnglishScore);
    }

    return COMPCALCSTATE_INPUTMENU;
}

/************************************************************
 * FUNCTION:ComCalcstate_StatMethodSelCA()
 * Description:计算平均值
 * Arguments[iState][In]:进行状态与执行函数的对应关系检查
 * return:计算器复杂模式状态机的下一次状态
 * *********************************************************/
int ComCalcState_StatMethodSelCA(int iState)
{
    if (iState != COMPCALCSTATE_CALCAVERAGE)
    {
        calc_error("[%s]g_stCompCalcState init is fail!\n", __FUNCTION__);
        exit(-1);
    } 

    int iRet = CALCEXE_RET_OK; 
    Class_St stClass;

    memset(&stClass, 0, sizeof(stClass));
    /*read student information from datacenter*/
    iRet = DataCenter_ReadCalcComplexModeClassInfo(&stClass, DATA_CALCCOMPLEX_DEFAULT);
    if (iRet == DATACENTER_RET_FAIL)
    {
        calc_error("[%s]DataCenter_ReadClassInfo is fail!\n", __FUNCTION__);
        return COMPCALCSTATE_CALCAVERAGE;
    }

    /*calculator the student average score*/
    iRet = Calculating_StuScoreAverage(stClass.stStu_a, stClass.guiCurStuNumCount, &stClass.gdChineseScoreAverage, 
                                      &stClass.gdMathScoreAverage, &stClass.gdEnglishScoreAverage);
    if (iRet == CALCEXE_RET_FAIL)
    {
        calc_error("[%s]Calculating_StuScoreAverage is fail!\n", __FUNCTION__);   
        return COMPCALCSTATE_INPUTMENU;
    }
    else
    {
        /*average has been calculator*/
        stClass.gbAverageInfoReady = true; 
        /*save the average calc wheather ready OK information to datacenter*/
        iRet = DataCenter_WriteCalcComplexModeClassInfo(stClass, DATA_CALCCOMPLEX_WRITE_AVERAGE_READY);
        if (iRet == DATACENTER_RET_FAIL)
        {
            calc_error("[%s]DataCenter_WriteClassInfo is fail!\n", __FUNCTION__);
            return COMPCALCSTATE_CALCAVERAGE;
        }
        
        calc_running("subject [    Chinese] average [%f]\n", stClass.gdChineseScoreAverage);
        calc_running("subject [       Math] average [%f]\n", stClass.gdMathScoreAverage);
        calc_running("subject [    English] average [%f]\n", stClass.gdEnglishScoreAverage);
    }

    /*save the arerage information to datacenter*/
    iRet = DataCenter_WriteCalcComplexModeClassInfo(stClass, DATA_CALCCOMPLEX_WRITE_AVERAGE);
    if (iRet == DATACENTER_RET_FAIL)
    {
        calc_error("[%s]DataCenter_WriteClassInfo is fail!\n", __FUNCTION__);
        return COMPCALCSTATE_CALCAVERAGE;
    }

    return COMPCALCSTATE_INPUTMENU;
}

/************************************************************
 * FUNCTION:ComCalcstate_StatMethodSelCV()
 * Description:计算方差
 * Arguments[iState][In]:进行状态与执行函数的对应关系检查
 * return:计算器复杂模式状态机的下一次状态
 * *********************************************************/
int ComCalcState_StatMethodSelCV(int iState)
{
    if (iState != COMPCALCSTATE_CALCVARIANCE)
    {
        calc_error("[%s]g_stCompCalcState init is fail!\n", __FUNCTION__);
        exit(-1);
    } 

    int iRet = CALCEXE_RET_OK; 
    Class_St stClass;

    memset(&stClass, 0, sizeof(stClass));
    /*read student information from datacenter*/
    iRet = DataCenter_ReadCalcComplexModeClassInfo(&stClass, DATA_CALCCOMPLEX_DEFAULT);
    if (iRet == DATACENTER_RET_FAIL)
    {
        calc_error("[%s]DataCenter_ReadClassInfo is fail!\n", __FUNCTION__);
        return COMPCALCSTATE_CALCVARIANCE;
    }

    /*calculator the student Variance score*/
    iRet = Calculating_StuScoreVariance(stClass.stStu_a, stClass.guiCurStuNumCount, &stClass.gdChineseScoreVariance, 
                                &stClass.gdMathScoreVariance, &stClass.gdEnglishScoreVariance);
    if (iRet == CALCEXE_RET_FAIL)
    {
        calc_error("[%s]Calculating_StuScoreVariance is fail!\n", __FUNCTION__);   
        return COMPCALCSTATE_INPUTMENU;
    }
    else
    {
        /*Variance has been calculator*/
        stClass.gbVarianceInfoReady = true;
        /*save the variance calc wheather ready OK information to datacenter*/
        iRet = DataCenter_WriteCalcComplexModeClassInfo(stClass, DATA_CALCCOMPLEX_WRITE_VARIANCE_READY);
        if (iRet == DATACENTER_RET_FAIL)
        {
            calc_error("[%s]DataCenter_WriteClassInfo is fail!\n", __FUNCTION__);
            return COMPCALCSTATE_CALCAVERAGE;
        }
    
        calc_running("subject [    Chinese] variance [%f]\n", stClass.gdChineseScoreVariance);
        calc_running("subject [       Math] variance [%f]\n", stClass.gdMathScoreVariance);
        calc_running("subject [    English] variance [%f]\n", stClass.gdEnglishScoreVariance);   
    }

    /*save the Variance information to datacenter*/
    iRet = DataCenter_WriteCalcComplexModeClassInfo(stClass, DATA_CALCCOMPLEX_WRITE_VARIANCE);
    if (iRet == DATACENTER_RET_FAIL)
    {
        calc_error("[%s]DataCenter_WriteClassInfo is fail!\n", __FUNCTION__);
        return COMPCALCSTATE_CALCVARIANCE;
    }

    return COMPCALCSTATE_INPUTMENU;
}

/************************************************************
 * FUNCTION:ComCalcstate_StatMethodSelPA()
 * Description:打印平均值
 * Arguments[iState][In]:进行状态与执行函数的对应关系检查
 * return:计算器复杂模式状态机的下一次状态
 * *********************************************************/
int ComCalcState_StatMethodSelPA(int iState)
{
    if (iState != COMPCALCSTATE_PRINTAVERAGE)
    {
        calc_error("[%s]g_stCompCalcState init is fail!\n", __FUNCTION__);
        exit(-1);
    } 

    Class_St stClass;
    int iRet = DATACENTER_RET_OK;

    memset(&stClass, 0, sizeof(stClass));
    /*read student information from datacenter*/
    iRet = DataCenter_ReadCalcComplexModeClassInfo(&stClass, DATA_CALCCOMPLEX_DEFAULT);
    if (iRet == DATACENTER_RET_FAIL)
    {
        calc_error("[%s]DataCenter_ReadClassInfo is fail!\n", __FUNCTION__);
        return COMPCALCSTATE_CALCVARIANCE;
    }

    if (stClass.gbAverageInfoReady == true)
    {
        calc_running("subject [    Chinese] average [%f]\n", stClass.gdChineseScoreAverage);
        calc_running("subject [       Math] average [%f]\n", stClass.gdMathScoreAverage);
        calc_running("subject [    English] average [%f]\n", stClass.gdEnglishScoreAverage);

        return COMPCALCSTATE_INPUTMENU;
    }
    else
    {
        calc_error("Error:Average info not ready!\n");
        return COMPCALCSTATE_INPUTMENU;
    }
}
/************************************************************
 * FUNCTION:ComCalcstate_StatMethodSelPV()
 * Description:打印方差
 * Arguments[iState][In]:进行状态与执行函数的对应关系检查
 * return:计算器复杂模式状态机的下一次状态
 * *********************************************************/
int ComCalcState_StatMethodSelPV(int iState)
{
    if (iState != COMPCALCSTATE_PRINTVARIANCE)
    {
        calc_error("[%s]g_stCompCalcState init is fail!\n", __FUNCTION__);
        exit(-1);
    } 

    Class_St stClass;
    int iRet = DATACENTER_RET_OK;

    memset(&stClass, 0, sizeof(stClass));
    /*read student information from datacenter*/
    iRet = DataCenter_ReadCalcComplexModeClassInfo(&stClass, DATA_CALCCOMPLEX_DEFAULT);
    if (iRet == DATACENTER_RET_FAIL)
    {
        calc_error("[%s]DataCenter_ReadClassInfo is fail!\n", __FUNCTION__);
        return COMPCALCSTATE_CALCVARIANCE;
    }

    if (stClass.gbVarianceInfoReady == true)
    {
        calc_running("subject [    Chinese] variance [%f]\n", stClass.gdChineseScoreVariance);
        calc_running("subject [       Math] variance [%f]\n", stClass.gdMathScoreVariance);
        calc_running("subject [    English] variance [%f]\n", stClass.gdEnglishScoreVariance);

        return COMPCALCSTATE_INPUTMENU;
    }
    else
    {
        calc_error("Error:Variance info not ready!\n");
        return COMPCALCSTATE_INPUTMENU;
    }
}
/************************************************************
 * FUNCTION:ComCalcstate_StatMethodSelE()
 * Description:退出复杂模式
 * Arguments[iState][In]:进行状态与执行函数的对应关系检查
 * return:计算器复杂模式状态机的下一次状态
 * *********************************************************/ 
int ComCalcState_StatMethodSelE(int iState)
{
    int iRet = DATACENTER_RET_OK;

    iRet = DataCenter_CalcComplexModeDestoryDataCenter();
    if (iRet == DATACENTER_RET_FAIL)
    {
        calc_error("[%s]DataCenter_CalcComplexModeDestoryDataCenter is fail!\n", __FUNCTION__);
        return COMPCALCSTATE_FAIL;
    }

    calc_printf("DataCenter_CalcComplexModeDestoryDataCenter is destory!\n");

    return COMPCALCSTATE_INVALID;
}
    
/************************************************************
 * FUNCTION:ComCalcstate_StatMethodSelE()
 * Description:重新选择复杂模式计算机的工作状态
 * Arguments[iState][In]:进行状态与执行函数的对应关系检查
 * return:计算器复杂模式状态机的下一次状态n return CALCSTATE_RET_OK, FAIL return CALCSTATE_RET_FAIL
 * *********************************************************/ 
int ComCalcState_StatMethodSelFail(int iState)
{
    CalcOutput_HintMsg(CALCSTRING_COMPLEX_MODE_STATISTICAL_METHOD_SLECT_AGAIN);

    return COMPCALCSTATE_INPUTMENU;
}
