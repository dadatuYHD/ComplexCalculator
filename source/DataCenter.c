#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "../include/CalcState.h"
#include "../include/DataCenter.h"
#include "../include/calc_complex_debug.h"

char * g_pcSelectMode = NULL;
SimpleModeCalc_St * g_pstSimModeCalcOperand = NULL;
Class_St * g_pstClass = NULL;


/**************************************************************
 * FUNCTION:DataCenter_SetCalcMode()
 * Description                :Store the data of the working 
 *                             mode of the calculator selected 
 *                             by the user in the data center
 * Arguments[In][pcSelectMode]:mode data
 * return                     :success return DATACENTER_RET_OK
 *                             fail return DATACENTER_RET_FAIL
 *************************************************************/
int DataCenter_SetCalcMode(char *pcSelectMode)
{
    /*check intput parameter wheather valid*/
    if (pcSelectMode == NULL)
    {
        calc_error("[%s]input parameter is error!\n", __FUNCTION__);
        return DATACENTER_RET_FAIL;
    }

    *g_pcSelectMode = *pcSelectMode;

    return DATACENTER_RET_OK;
}

/***************************************************************
 * FUNCTION                   :DataCenter_GetCalcMode()
 * Description                :Read the computer mode 
                               selection data stored by the 
                               user in the data center
 * Arguments[In][pcSelectMode]:storage the mode data
 * return                     :success return DATACENTER_RET_OK
 *                             fail return DATACENTER_RET_FAIL
 * ************************************************************/
int DataCenter_GetCalcMode(char *pcSelectMode)
{
    /*check intput parameter wheather valid*/
    if (pcSelectMode == NULL)
    {
        calc_error("[%s]input parameter is error!\n", __FUNCTION__);
        return DATACENTER_RET_FAIL;
    }

    *pcSelectMode = *g_pcSelectMode;

    return DATACENTER_RET_OK;
}

/************************************************************
 * FUNCTION   :DataCenter_CreateCalcMode()
 * Description:This function is mainly used to create 
 *             datacenter space for saving modeselect 
 *             information
 * Arguments  :void
 * return     :success return DATACENTER_RET_OK，
 *             fail return DATACENTER_RET_FAIL
 * *********************************************************/
int DataCenter_CreateCalcMode(void)
{
    g_pcSelectMode = (char *)malloc(sizeof(char));
    if (g_pcSelectMode == NULL)
    {
        calc_error("[%s]malloc is fail!\n", __FUNCTION__);
        return DATACENTER_RET_FAIL;
    }   

    memset(g_pcSelectMode, 0, sizeof(char));

    return DATACENTER_RET_OK;
}

/************************************************************
 * FUNCTION   :DataCenter_DestoryCalcMode()
 * Description:Destory datacenter space for saving modeselect 
 *             information
 * Arguments  ：void
 * return     :success return DATACENTER_RET_OK，
 *             fail return DATACENTER_RET_FAIL
 * *********************************************************/
int DataCenter_DestoryCalcMode(void)
{
    free(g_pcSelectMode);
    g_pcSelectMode = NULL;   

    return DATACENTER_RET_OK;
}


/************************************************************
 * FUNCTION                :DataCenter_SetSimCalcOper()
 * Description             :Save the calculator operand 
 *                          information entered by the user
 * Arguments[In][uiNum]    :Number to be saved
 * Arguments[In][cOperator]:Operand to be saved
 * Arguments[In][flag]     :mode select
 * return                  :success return DATACENTER_RET_OK
 *                          fail return DATACENTER_RET_FAIL
 * *********************************************************/
int DataCenter_SetSimCalcOper(SimpleModeCalc_St stSimModeCalcOperand, int flag)
{
    calc_trace();

    if (flag == DATA_CALCSIMPLE_WRITE_1STNUM)
    {
        g_pstSimModeCalcOperand->gui1stNum = stSimModeCalcOperand.gui1stNum;
        calc_printf("g_pstSimModeCalcOperand->gui1stNum = %d\n", g_pstSimModeCalcOperand->gui1stNum);
    }
    else if (flag == DATA_CALCSIMPLE_WRITE_2NDNUM)
    {
        g_pstSimModeCalcOperand->gui2ndNum = stSimModeCalcOperand.gui2ndNum;
        calc_printf("g_pstSimModeCalcOperand->gui2ndNum = %d\n", g_pstSimModeCalcOperand->gui2ndNum);
    }
    else if (flag == DATA_CALCSIMPLE_WRITE_OPERATOR)
    {
        g_pstSimModeCalcOperand->gcOperator = stSimModeCalcOperand.gcOperator;
        calc_printf("g_pstSimModeCalcOperand->gcOperator = %c\n", g_pstSimModeCalcOperand->gcOperator);
    }
    else if (flag == DATA_CALCSIMPLE_WRITE_RESULT)
    {
        g_pstSimModeCalcOperand->guiResult = stSimModeCalcOperand.guiResult;
        calc_printf("g_pstSimModeCalcOperand->guiResult = %d\n", g_pstSimModeCalcOperand->guiResult);
    }
    else
    {
        calc_error("[%s]input flag is error!\n", __FUNCTION__);
    }

    return DATACENTER_RET_OK;
}

/******************************************************************************
 * FUNCTION                             :DataCenter_GetCalcSimOper()
 * Description                          :Read the calculator 
 *                                       operand information in the data center
 * Arguments[Out][pstSimModeCalcOperand]:buffer
 * return                               :success return DATACENTER_RET_OK
 *                                       fail return DATACENTER_RET_FAIL
 * ****************************************************************************/
int DataCenter_GetSimCalcOper(SimpleModeCalc_St * pstSimModeCalcOperand)
{
    if (pstSimModeCalcOperand == NULL)
    {
        calc_error("[%s]input parameter is error!\n", __FUNCTION__);
        return DATACENTER_RET_FAIL;
    }

    pstSimModeCalcOperand->gui1stNum = g_pstSimModeCalcOperand->gui1stNum;
    pstSimModeCalcOperand->gui2ndNum = g_pstSimModeCalcOperand->gui2ndNum;
    pstSimModeCalcOperand->gcOperator = g_pstSimModeCalcOperand->gcOperator;
    pstSimModeCalcOperand->guiResult = g_pstSimModeCalcOperand->guiResult;

    return DATACENTER_RET_OK;
}


/************************************************************
 * FUNCTION   :DataCenter_CreateSimCalcOper()
 * Description:Create a datacenter space for saving simple 
 *             calc operand information
 * Arguments  :void
 * return     :success return DATACENTER_RET_OK，
 *             fail return DATACENTER_RET_FAIL
 * *********************************************************/
 int DataCenter_CreateSimCalcOper(void)
{
    g_pstSimModeCalcOperand = (SimpleModeCalc_St *)malloc(sizeof(SimpleModeCalc_St));
    if (g_pstSimModeCalcOperand == NULL)
    {
        calc_error("[%s]malloc is fail!\n", __FUNCTION__);
        return DATACENTER_RET_FAIL;
    }
    
    memset(g_pstSimModeCalcOperand, 0, sizeof(g_pstSimModeCalcOperand));

    return DATACENTER_RET_OK;
}

/************************************************************
 * FUNCTION   :DataCenter_DestoryCalcSimOper()
 * Description:Destory datacenter space for saving simple 
 *             calc information
 * Arguments  :void
 * return     :success return DATACENTER_RET_OK，
 *             fail return DATACENTER_RET_FAIL
 * *********************************************************/
int DataCenter_DestorySimCalcOper(void)
{
    free(g_pstSimModeCalcOperand);
    g_pstSimModeCalcOperand = NULL;

    return DATACENTER_RET_OK;
}



/************************************************************
 * FUNCTION              :DataCenter_SetCalcClassInfo()
 * Description           :storage some information about class
 * Arguments[In][stClass]:information about class
 * Arguments[In][flag]   :data mode slect
 * return                :success return DATACENTER_RET_OK，
 *                        fail return DATACENTER_RET_FAIL
 * *********************************************************/
int DataCenter_SetCalcClassInfo(Class_St stClass, int flag)
{
    calc_trace();

    if (flag == (DATA_CALCCOMPLEX_WRITE_STUINFO))
    {   
        strcpy(g_pstClass->stStu_a[g_pstClass->guiCurStuNumCount].gcStuName, stClass.stStu_a[0].gcStuName);
        g_pstClass->stStu_a[g_pstClass->guiCurStuNumCount].uiChineseScore = stClass.stStu_a[0].uiChineseScore;
        g_pstClass->stStu_a[g_pstClass->guiCurStuNumCount].uiMathScore = stClass.stStu_a[0].uiMathScore;
        g_pstClass->stStu_a[g_pstClass->guiCurStuNumCount].uiEnglishScore = stClass.stStu_a[0].uiEnglishScore;
        g_pstClass->guiCurStuNumCount++;
    }
    else if(flag == DATA_CALCCOMPLEX_WRITE_AVERAGE)
    {
        g_pstClass->gdChineseScoreAverage = stClass.gdChineseScoreAverage;
        g_pstClass->gdMathScoreAverage    = stClass.gdMathScoreAverage;
        g_pstClass->gdEnglishScoreAverage = stClass.gdEnglishScoreAverage;
    }
    else if (flag == DATA_CALCCOMPLEX_WRITE_VARIANCE)
    {
        g_pstClass->gdChineseScoreVariance = stClass.gdChineseScoreVariance;
        g_pstClass->gdMathScoreVariance    = stClass.gdMathScoreVariance;
        g_pstClass->gdEnglishScoreVariance = stClass.gdEnglishScoreVariance;
    }
    else if (flag == DATA_CALCCOMPLEX_WRITE_AVERAGE_READY)
    {
        g_pstClass->gbAverageInfoReady = stClass.gbAverageInfoReady;
    }
    else if (flag == DATA_CALCCOMPLEX_WRITE_VARIANCE_READY)
    {
        g_pstClass->gbVarianceInfoReady = stClass.gbVarianceInfoReady;
    }
    else
    {
        /*******************/
    }
    
    return DATACENTER_RET_OK;
}

/**************************************************************
 * FUNCTION                :DataCenter_GetCalcClassInfo()
 * Description             :get some information about class 
 *                          from datacenter
 * Arguments[Out][pstClass]:storage the class info
 * Arguments[In][flag]     :mode slect
 * return                  :success return DATACENTER_RET_OK，
 *                          fail return DATACENTER_RET_FAIL
 * *********************************************************/
 int DataCenter_GetCalcClassInfo(Class_St * pstClass, int flag)
{
    if (pstClass == NULL)
    {
        calc_error("[%s]input parameter is fail!\n", __FUNCTION__);
        return DATACENTER_RET_FAIL;
    }

    if (flag == DATA_CALCCOMPLEX_DEFAULT)
    {   
        for (int i = 0; i < g_pstClass->guiCurStuNumCount; i++)
        {
            pstClass->stStu_a[i] = g_pstClass->stStu_a[i];
        }
        pstClass->gdChineseScoreAverage   = g_pstClass->gdChineseScoreAverage;
        pstClass->gdMathScoreAverage      = g_pstClass->gdMathScoreAverage;
        pstClass->gdEnglishScoreAverage   = g_pstClass->gdEnglishScoreAverage;
        pstClass->gdChineseScoreVariance  = g_pstClass->gdChineseScoreVariance;
        pstClass->gdMathScoreVariance     = g_pstClass->gdMathScoreVariance;
        pstClass->gdEnglishScoreVariance  = g_pstClass->gdEnglishScoreVariance;
        pstClass->guiCurStuNumCount       = g_pstClass->guiCurStuNumCount;
        pstClass->gbAverageInfoReady      = g_pstClass->gbAverageInfoReady;
        pstClass->gbVarianceInfoReady     = g_pstClass->gbVarianceInfoReady; 
    }
    else
    {
        /**********/
    }

    return DATACENTER_RET_OK;
}

/************************************************************
 * FUNCTION:DataCenter_CreateCalcClassInfo()
 * Description:create datacenter space about class info
 * Arguments  :void
 * return     :success return DATACENTER_RET_OK，
 *             fail return DATACENTER_RET_FAIL
 * *********************************************************/
 int DataCenter_CreateCalcClassInfo(void)
{
    g_pstClass = (Class_St *)malloc(sizeof(Class_St));
    if (g_pstClass == NULL)
    {
        calc_error("[%s]malloc is error!\n", __FUNCTION__);
        return DATACENTER_RET_FAIL;
    }
    memset(g_pstClass, 0, sizeof(Class_St)); 

    for (int i = 0; i < g_pstClass->guiCurStuNumCount; i++)
    {
        calc_printf("gcStuName = %s\n uiChineseScore = %d\n uiMathScore = %d\n uiEnglishScore = %d\n", 
                        (g_pstClass->stStu_a + i)->gcStuName, (g_pstClass->stStu_a + i)->uiChineseScore,
                        (g_pstClass->stStu_a + i)->uiMathScore, (g_pstClass->stStu_a + i)->uiEnglishScore);
    }
    

    calc_printf("gdChineseScoreAverage = %lf\n gdMathScoreAverage = %lf\n gdEnglishScoreAverage = %lf\n\
gdChineseScoreVariance = %lf\n gdMathScoreVariance = %lf\n gdEnglishScoreVariance = %lf\n guiCurStuNumCount = %d\n \
gbAverageInfoReady = %d\n gbVarianceInfoReady = %d\n",
                                                  g_pstClass->gdChineseScoreAverage,
                                                  g_pstClass->gdMathScoreAverage,
                                                  g_pstClass->gdEnglishScoreAverage,
                                                  g_pstClass->gdChineseScoreVariance,
                                                  g_pstClass->gdMathScoreVariance,
                                                  g_pstClass->gdEnglishScoreVariance,
                                                  g_pstClass->guiCurStuNumCount,
                                                  g_pstClass->gbAverageInfoReady,
                                                  g_pstClass->gbVarianceInfoReady);

    return DATACENTER_RET_OK;
}

/************************************************************
 * FUNCTION   :DataCenter_DestoryCalcClassInfo()
 * Description:destory the datacenter space about storage 
 *             the class info
 * Arguments  :void
 * return     :success return DATACENTER_RET_OK，
 *             fail return DATACENTER_RET_FAIL
 * *********************************************************/
int DataCenter_DestoryCalcClassInfo(void)
{
    for (int i = 0; i < g_pstClass->guiCurStuNumCount; i++)
    {
        calc_printf("gcStuName = %s\n uiChineseScore = %d\n uiMathScore = %d\n uiEnglishScore = %d\n", 
                        (g_pstClass->stStu_a + i)->gcStuName, (g_pstClass->stStu_a + i)->uiChineseScore,
                        (g_pstClass->stStu_a + i)->uiMathScore, (g_pstClass->stStu_a + i)->uiEnglishScore);
    }

    
    calc_printf("gdChineseScoreAverage = %lf\n gdMathScoreAverage = %lf\n gdEnglishScoreAverage = %lf\n\
gdChineseScoreVariance = %lf\n gdMathScoreVariance = %lf\n gdEnglishScoreVariance = %lf\n guiCurStuNumCount = %d\n \
gbAverageInfoReady = %d\n gbVarianceInfoReady = %d\n",
                                                  g_pstClass->gdChineseScoreAverage,
                                                  g_pstClass->gdMathScoreAverage,
                                                  g_pstClass->gdEnglishScoreAverage,
                                                  g_pstClass->gdChineseScoreVariance,
                                                  g_pstClass->gdMathScoreVariance,
                                                  g_pstClass->gdEnglishScoreVariance,
                                                  g_pstClass->guiCurStuNumCount,
                                                  g_pstClass->gbAverageInfoReady,
                                                  g_pstClass->gbVarianceInfoReady);
    memset(g_pstClass, 0, sizeof(Class_St)); 
    free(g_pstClass);
    g_pstClass = NULL;

    return DATACENTER_RET_OK;
}


