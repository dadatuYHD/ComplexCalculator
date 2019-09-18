#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "../include/CalcState.h"
#include "../include/DataCenter.h"
#include "../include/calc_complex_debug.h"

char * gpcSelectMode = NULL;
SimpleModeCalc_St * gpstSimModeCalcOperand = NULL;
Class_St * gpstClass = NULL;


/************************************************************
 * FUNCTION:DataCenter_WriteStateMacMajorModeSel()
 * Description:该函数主要用来把用户选择计算机的工作模式数据存入数据中心保存
 * Arguments[In][pcSelectMode]存入的数据
 * Arguments[In][flag]存入数据的模式选择
 * return:成功返回DATACENTER_RET_OK，失败返回DATACENTER_RET_FAIL
 * *********************************************************/
int DataCenter_WriteStateMacMajorModeSel(char *pcSelectMode, int flag)
{
    /*check intput parameter wheather valid*/
    if (pcSelectMode == NULL)
    {
        calc_error("[%s]input parameter is error!\n", __FUNCTION__);
        return DATACENTER_RET_FAIL;
    }

    *gpcSelectMode = *pcSelectMode;

    return DATACENTER_RET_OK;
}

/************************************************************
 * FUNCTION:DataCenter_ReadStateMacMajorModeSel()
 * Description:该函数主要用来读取用户存储到数据中心的计算机模式选择数据
 * Arguments[In][pcSelectMode]读取的数据存储buffe
 * Arguments[In][flag]读取数据的模式选择
 * return:成功返回DATACENTER_RET_OK，失败返回DATACENTER_RET_FAIL
 * *********************************************************/
int DataCenter_ReadStateMacMajorModeSel(char *pcSelectMode, int flag)
{
    /*check intput parameter wheather valid*/
    if (pcSelectMode == NULL)
    {
        calc_error("[%s]input parameter is error!\n", __FUNCTION__);
        return DATACENTER_RET_FAIL;
    }

    *pcSelectMode = *gpcSelectMode;

    return DATACENTER_RET_OK;
}

/************************************************************
 * FUNCTION:DataCenter_StateMacMajorModeSelCreateDataCenter()
 * Description:该函数主要用来创建关于保存modeselect信息的datacenter空间
 * Arguments：无
 * return:成功返回DATACENTER_RET_OK，失败返回DATACENTER_RET_FAIL
 * *********************************************************/
int DataCenter_StateMacMajorModeSelCreateDataCenter(void)
{
    gpcSelectMode = (char *)malloc(sizeof(char));
    if (gpcSelectMode == NULL)
    {
        calc_error("[%s]malloc is fail!\n", __FUNCTION__);
        return DATACENTER_RET_FAIL;
    }   

    memset(gpcSelectMode, 0, sizeof(char));

    return DATACENTER_RET_OK;
}

/************************************************************
 * FUNCTION:DataCenter_StateMacMajorModeSelDestoryDataCenter()
 * Description:该函数主要用来释放关于保存modeselect信息的datacenter空间
 * Arguments：无
 * return:成功返回DATACENTER_RET_OK，失败返回DATACENTER_RET_FAIL
 * *********************************************************/
int DataCenter_StateMacMajorModeSelDestoryDataCenter(void)
{
    free(gpcSelectMode);
    gpcSelectMode = NULL;   

    return DATACENTER_RET_OK;
}


/************************************************************
 * FUNCTION:DataCenter_WriteCalcSimModeOperand()
 * Description:该函数主要用来保存用户输入的计算器操作数信息
 * Arguments[In][uiNum]需要保存的数字
 * Arguments[In][cOperator]需要保存的运算符
 * Arguments[In][flag]写入数据的模式选择
 * return:成功返回DATACENTER_RET_OK，失败返回DATACENTER_RET_FAIL
 * *********************************************************/
int DataCenter_WriteCalcSimModeOperand(SimpleModeCalc_St stSimModeCalcOperand, int flag)
{
    calc_trace();

    if (flag == DATA_CALCSIMPLE_WRITE_1STNUM)
    {
        gpstSimModeCalcOperand->gui1stNum = stSimModeCalcOperand.gui1stNum;
        calc_printf("gpstSimModeCalcOperand->gui1stNum = %d\n", gpstSimModeCalcOperand->gui1stNum);
    }
    else if (flag == DATA_CALCSIMPLE_WRITE_2NDNUM)
    {
        gpstSimModeCalcOperand->gui2ndNum = stSimModeCalcOperand.gui2ndNum;
        calc_printf("gpstSimModeCalcOperand->gui2ndNum = %d\n", gpstSimModeCalcOperand->gui2ndNum);
    }
    else if (flag == DATA_CALCSIMPLE_WRITE_OPERATOR)
    {
        gpstSimModeCalcOperand->gcOperator = stSimModeCalcOperand.gcOperator;
        calc_printf("gpstSimModeCalcOperand->gcOperator = %c\n", gpstSimModeCalcOperand->gcOperator);
    }
    else if (flag == DATA_CALCSIMPLE_WRITE_RESULT)
    {
        gpstSimModeCalcOperand->guiResult = stSimModeCalcOperand.guiResult;
        calc_printf("gpstSimModeCalcOperand->guiResult = %d\n", gpstSimModeCalcOperand->guiResult);
    }
    else
    {
        calc_error("[%s]input flag is error!\n", __FUNCTION__);
    }

    return DATACENTER_RET_OK;
}

/************************************************************
 * FUNCTION:DataCenter_ReadCalcSimModeOperand()
 * Description:该函数主要用来读取保存到数据中心的计算器操作数信息
 * Arguments[Out][pstSimModeCalcOperand]指向一个buffer
 * Arguments[In][flag]写入数据的模式选择
 * return:成功返回DATACENTER_RET_OK，失败返回DATACENTER_RET_FAIL
 * *********************************************************/
int DataCenter_ReadCalcSimModeOperand(SimpleModeCalc_St * pstSimModeCalcOperand, int flag)
{
    if (pstSimModeCalcOperand == NULL)
    {
        calc_error("[%s]input parameter is error!\n", __FUNCTION__);
        return DATACENTER_RET_FAIL;
    }

    pstSimModeCalcOperand->gui1stNum = gpstSimModeCalcOperand->gui1stNum;
    pstSimModeCalcOperand->gui2ndNum = gpstSimModeCalcOperand->gui2ndNum;
    pstSimModeCalcOperand->gcOperator = gpstSimModeCalcOperand->gcOperator;
    pstSimModeCalcOperand->guiResult = gpstSimModeCalcOperand->guiResult;

    return DATACENTER_RET_OK;
}


/************************************************************
 * FUNCTION:DataCenter_CalcSimModeOperandDestoryDataCenter()
 * Description:该函数主要用来创建关于保存simple calc信息的datacenter空间
 * Arguments：无
 * return:成功返回DATACENTER_RET_OK，失败返回DATACENTER_RET_FAIL
 * *********************************************************/
 int DataCenter_CalcSimModeOperandCreateDataCenter(void)
{
    gpstSimModeCalcOperand = (SimpleModeCalc_St *)malloc(sizeof(SimpleModeCalc_St));
    if (gpstSimModeCalcOperand == NULL)
    {
        calc_error("[%s]malloc is fail!\n", __FUNCTION__);
        return DATACENTER_RET_FAIL;
    }
    
    memset(gpstSimModeCalcOperand, 0, sizeof(gpstSimModeCalcOperand));

    return DATACENTER_RET_OK;
}

/************************************************************
 * FUNCTION:DataCenter_CalcSimModeOperandDestoryDataCenter()
 * Description:该函数主要用来释放关于保存simple calc信息的datacenter空间
 * Arguments：无
 * return:成功返回DATACENTER_RET_OK，失败返回DATACENTER_RET_FAIL
 * *********************************************************/
int DataCenter_CalcSimModeOperandDestoryDataCenter(void)
{
    free(gpstSimModeCalcOperand);
    gpstSimModeCalcOperand = NULL;

    return DATACENTER_RET_OK;
}



/************************************************************
 * FUNCTION:DataCenter_WriteCalcComplexModeClassInfo()
 * Description:该函数主要用来保存班级的相关信息
 * Arguments[In][stClass]需要保存的结构体信息
 * Arguments[In][flag]写入数据的模式选择
 * return:成功返回DATACENTER_RET_OK，失败返回DATACENTER_RET_FAIL
 * *********************************************************/
int DataCenter_WriteCalcComplexModeClassInfo(Class_St stClass, int flag)
{
    calc_trace();

    if (flag == (DATA_CALCCOMPLEX_WRITE_STUINFO))
    {   
        strcpy(gpstClass->stStu_a[gpstClass->guiCurStuNumCount].gcStuName, stClass.stStu_a[0].gcStuName);
        gpstClass->stStu_a[gpstClass->guiCurStuNumCount].uiChineseScore = stClass.stStu_a[0].uiChineseScore;
        gpstClass->stStu_a[gpstClass->guiCurStuNumCount].uiMathScore = stClass.stStu_a[0].uiMathScore;
        gpstClass->stStu_a[gpstClass->guiCurStuNumCount].uiEnglishScore = stClass.stStu_a[0].uiEnglishScore;
        gpstClass->guiCurStuNumCount++;
    }
    else if(flag == DATA_CALCCOMPLEX_WRITE_AVERAGE)
    {
        gpstClass->gdChineseScoreAverage = stClass.gdChineseScoreAverage;
        gpstClass->gdMathScoreAverage    = stClass.gdMathScoreAverage;
        gpstClass->gdEnglishScoreAverage = stClass.gdEnglishScoreAverage;
    }
    else if (flag == DATA_CALCCOMPLEX_WRITE_VARIANCE)
    {
        gpstClass->gdChineseScoreVariance = stClass.gdChineseScoreVariance;
        gpstClass->gdMathScoreVariance    = stClass.gdMathScoreVariance;
        gpstClass->gdEnglishScoreVariance = stClass.gdEnglishScoreVariance;
    }
    else if (flag == DATA_CALCCOMPLEX_WRITE_AVERAGE_READY)
    {
        gpstClass->gbAverageInfoReady = stClass.gbAverageInfoReady;
    }
    else if (flag == DATA_CALCCOMPLEX_WRITE_VARIANCE_READY)
    {
        gpstClass->gbVarianceInfoReady = stClass.gbVarianceInfoReady;
    }
    else
    {
        /*******************/
    }
    
    return DATACENTER_RET_OK;
}

/************************************************************
 * FUNCTION:DataCenter_ReadCalcComplexModeClassInfo()
 * Description:该函数主要读取保存在数据中心的班级的相关信息
 * Arguments[Out][pstClass]读取之后数据保存的buffer
 * Arguments[In][flag]读取数据的模式选择
 * return:成功返回DATACENTER_RET_OK，失败返回DATACENTER_RET_FAIL
 * *********************************************************/
 int DataCenter_ReadCalcComplexModeClassInfo(Class_St * pstClass, int flag)
{
    if (pstClass == NULL)
    {
        calc_error("[%s]input parameter is fail!\n", __FUNCTION__);
        return DATACENTER_RET_FAIL;
    }

    if (flag == DATA_CALCCOMPLEX_DEFAULT)
    {   
        for (int i = 0; i < gpstClass->guiCurStuNumCount; i++)
        {
            pstClass->stStu_a[i] = gpstClass->stStu_a[i];
        }
        pstClass->gdChineseScoreAverage   = gpstClass->gdChineseScoreAverage;
        pstClass->gdMathScoreAverage      = gpstClass->gdMathScoreAverage;
        pstClass->gdEnglishScoreAverage   = gpstClass->gdEnglishScoreAverage;
        pstClass->gdChineseScoreVariance  = gpstClass->gdChineseScoreVariance;
        pstClass->gdMathScoreVariance     = gpstClass->gdMathScoreVariance;
        pstClass->gdEnglishScoreVariance  = gpstClass->gdEnglishScoreVariance;
        pstClass->guiCurStuNumCount       = gpstClass->guiCurStuNumCount;
        pstClass->gbAverageInfoReady      = gpstClass->gbAverageInfoReady;
        pstClass->gbVarianceInfoReady     = gpstClass->gbVarianceInfoReady; 
    }
    else
    {
        /**********/
    }

    return DATACENTER_RET_OK;
}

/************************************************************
 * FUNCTION:DataCenter_CalcComplexModeCreateDataCenter()
 * Description:该函数主要用来创建关于保存class信息的datacenter空间
 * Arguments：无
 * return:成功返回DATACENTER_RET_OK，失败返回DATACENTER_RET_FAIL
 * *********************************************************/
 int DataCenter_CalcComplexModeCreateDataCenter(void)
{
    gpstClass = (Class_St *)malloc(sizeof(Class_St));
    if (gpstClass == NULL)
    {
        calc_error("[%s]malloc is error!\n", __FUNCTION__);
        return DATACENTER_RET_FAIL;
    }
    memset(gpstClass, 0, sizeof(Class_St)); 

    for (int i = 0; i < gpstClass->guiCurStuNumCount; i++)
    {
        calc_printf("gcStuName = %s\n uiChineseScore = %d\n uiMathScore = %d\n uiEnglishScore = %d\n", 
                        (gpstClass->stStu_a + i)->gcStuName, (gpstClass->stStu_a + i)->uiChineseScore,
                        (gpstClass->stStu_a + i)->uiMathScore, (gpstClass->stStu_a + i)->uiEnglishScore);
    }
    

    calc_printf("gdChineseScoreAverage = %lf\n gdMathScoreAverage = %lf\n gdEnglishScoreAverage = %lf\n\
gdChineseScoreVariance = %lf\n gdMathScoreVariance = %lf\n gdEnglishScoreVariance = %lf\n guiCurStuNumCount = %d\n \
gbAverageInfoReady = %d\n gbVarianceInfoReady = %d\n",
                                                  gpstClass->gdChineseScoreAverage,
                                                  gpstClass->gdMathScoreAverage,
                                                  gpstClass->gdEnglishScoreAverage,
                                                  gpstClass->gdChineseScoreVariance,
                                                  gpstClass->gdMathScoreVariance,
                                                  gpstClass->gdEnglishScoreVariance,
                                                  gpstClass->guiCurStuNumCount,
                                                  gpstClass->gbAverageInfoReady,
                                                  gpstClass->gbVarianceInfoReady);

    return DATACENTER_RET_OK;
}

/************************************************************
 * FUNCTION:DataCenter_CalcComplexModeDestoryDataCenter()
 * Description:该函数主要用来释放关于保存class信息的datacenter空间
 * Arguments：无
 * return:成功返回DATACENTER_RET_OK，失败返回DATACENTER_RET_FAIL
 * *********************************************************/
int DataCenter_CalcComplexModeDestoryDataCenter(void)
{
    for (int i = 0; i < gpstClass->guiCurStuNumCount; i++)
    {
        calc_printf("gcStuName = %s\n uiChineseScore = %d\n uiMathScore = %d\n uiEnglishScore = %d\n", 
                        (gpstClass->stStu_a + i)->gcStuName, (gpstClass->stStu_a + i)->uiChineseScore,
                        (gpstClass->stStu_a + i)->uiMathScore, (gpstClass->stStu_a + i)->uiEnglishScore);
    }

    
    calc_printf("gdChineseScoreAverage = %lf\n gdMathScoreAverage = %lf\n gdEnglishScoreAverage = %lf\n\
gdChineseScoreVariance = %lf\n gdMathScoreVariance = %lf\n gdEnglishScoreVariance = %lf\n guiCurStuNumCount = %d\n \
gbAverageInfoReady = %d\n gbVarianceInfoReady = %d\n",
                                                  gpstClass->gdChineseScoreAverage,
                                                  gpstClass->gdMathScoreAverage,
                                                  gpstClass->gdEnglishScoreAverage,
                                                  gpstClass->gdChineseScoreVariance,
                                                  gpstClass->gdMathScoreVariance,
                                                  gpstClass->gdEnglishScoreVariance,
                                                  gpstClass->guiCurStuNumCount,
                                                  gpstClass->gbAverageInfoReady,
                                                  gpstClass->gbVarianceInfoReady);
    memset(gpstClass, 0, sizeof(Class_St)); 
    free(gpstClass);
    gpstClass = NULL;

    return DATACENTER_RET_OK;
}


