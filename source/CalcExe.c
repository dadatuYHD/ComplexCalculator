/********************************************************
*   Copyright (C) 2017 All rights reserved.
*
*   Filename:CalcExe.c
*   Author  :yhd
*   Date    :2017-04-30
*   Describe:The following functions are mainly used for 
*            the calculation of calculator values
*
********************************************************/
#include "../include/CalcState.h"
#include "../include/CalcExe.h"
#include "../include/calc_complex_debug.h"
#include <stdbool.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define PF(A) ((A)*(A))


/************************************************************
FUNCTION:Calculating_Sum()
Description:该函数主要用来对输入的参数进行加法运算
Arguments:
Arg1:[In] 传递加法运算的第一个参数的指针
Arg2:[In] 传递加法运算的第二个参数的指针
Arg3:[Out] 传递加法运算存放运算结果的指针
return:成功返回CALCEXE_RET_OK ,错误返回CALCEXE_RET_FAIL
***********************************************************/
int Calculating_Sum(unsigned int * gui1stNum, unsigned int * gui2ndNum,unsigned int * guiResult)
{
    /*check the parameter is valid*/
    if ((NULL == gui1stNum) || (NULL == gui2ndNum))
    {
        calc_error("[%s]Input Parameter fail!\n", __FUNCTION__);
        return CALCEXE_RET_FAIL;
    }

    *guiResult = *gui1stNum + *gui2ndNum;

    return CALCEXE_RET_OK ;
}

/************************************************************
FUNCTION:Calculating_Mub()
Description:该函数主要用来对输入的参数进行减法运算
Arguments:
Arg1:[In] 传递减法运算的第一个参数的指针
Arg2:[In] 传递减法运算的第二个参数的指针
Arg3:[Out] 传递减法运算存放运算结果的指针
return:成功返回CALCEXE_RET_OK ,如果某一个参数为NULL，返回CALCEXE_RET_FAIL，如果第一个参数小于第二个参数，返回CALCEXE_RET_FAIL_1ST_GREATER_2ND
***********************************************************/
int Calculating_Mub(unsigned int * gui1stNum, unsigned int * gui2ndNum,unsigned int * guiResult)
{
    /*check the parameter is valid*/
    if ((NULL == gui1stNum) || (NULL == gui2ndNum))
    {
        calc_error("[%s]Input Parameter fail!\n", __FUNCTION__);
        return CALCEXE_RET_FAIL;
    }

    if (*gui1stNum < *gui2ndNum)
    {
        calc_error("[%s]gui1stNumber < gui2ndNumber!\n", __FUNCTION__);
        return CALCEXE_RET_FAIL_1ST_LESS_2ND;
    }
    else
    {
        *guiResult = *gui1stNum - *gui2ndNum;
        return CALCEXE_RET_OK ;
    }
}

/************************************************************
FUNCTION:Calculating_Mul()
Description:该函数主要用来对输入的参数进行乘法运算
Arguments:
Arg1:[In] 传递乘法运算的第一个参数的指针
Arg2:[In] 传递乘法运算的第二个参数的指针
Arg3:[Out] 传递乘法运算存放运算结果的指针
return:成功返回CALCEXE_RET_OK ,错误返回CALCEXE_RET_FAIL
***********************************************************/
int Calculating_Mul(unsigned int * gui1stNum, unsigned int * gui2ndNum,unsigned int * guiResult)
{
    /*check the parameter is valid*/
    if ((NULL == gui1stNum) || (NULL == gui2ndNum))
    {
        calc_error("[%s]Input Parameter fail!\n", __FUNCTION__);
        return CALCEXE_RET_FAIL;
    }

    *guiResult = *gui1stNum * *gui2ndNum;

    return CALCEXE_RET_OK ;
}

/************************************************************
FUNCTION:Calculating_Div()
Description:该函数主要用来对输入的参数进行除法运算
Arguments:
Arg1:[In] 传递除法运算的第一个参数的指针
Arg2:[In] 传递除法运算的第二个参数的指针
Arg3:[Out] 传递除法运算存放运算结果的指针
return:成功返回CALCEXE_RET_OK ,如果输入参数的指针为NULL，返回CALCEXE_RET_FAIL，如果除数为0，返回CALCEXE_RET_FAIL_DENOMINATOR_ZERO
***********************************************************/
int Calculating_Div(unsigned int * gui1stNum, unsigned int * gui2ndNum,unsigned int * guiResult)
{
    /*check the parameter is valid*/
    if ((NULL == gui1stNum) || (NULL == gui2ndNum))
    {
        calc_error("[%s]Input Parameter fail!\n", __FUNCTION__);
        return CALCEXE_RET_FAIL;
    }

    if (0 == *gui2ndNum)
    {
        calc_error("[%s]2nd number is zero!\n", __FUNCTION__);
        return CALCEXE_RET_FAIL_DENOMINATOR_ZERO;
    }
    else
    {
        *guiResult = *gui1stNum / *gui2ndNum;
        return CALCEXE_RET_OK ;
    }
}


/************************************************************
FUNCTION:Calculating_Average()
Description:该函数主要用来对输入的参数进行求平均值运算
Arguments:
Arg1:[In] 存放学生信息的结构体数组的指针
Arg2:[In] 学生个数
Arg3:[Out] 保存结果
return:成功返回CALCEXE_RET_OK ,如果输入参数的指针为NULL，返回CALCEXE_RET_FAIL
***********************************************************/
int Calculating_StuScoreAverage(Stu_E * pstStu, unsigned int uiStuNumCount, double * dpChineseScoreAverage, 
                                            double * dpMathScoreAverage, double * dpEnglishScoreAverage)
{
    if (pstStu == NULL || dpChineseScoreAverage == NULL || dpMathScoreAverage == NULL || dpEnglishScoreAverage == NULL)
    {
        calc_error("[%s]Input parameter is fail!\n", __FUNCTION__);
        return CALCEXE_RET_FAIL;
    }

    if (uiStuNumCount == 0)
    {
        calc_error("[%s]student strcture array is null!\n", __FUNCTION__);
        return CALCEXE_RET_FAIL;
    }

    *dpChineseScoreAverage = 0.0;
    *dpMathScoreAverage= 0.0;
    *dpEnglishScoreAverage = 0.0;
    for (int i = 0; i < uiStuNumCount; i++)
    {
        *dpChineseScoreAverage += (double)((pstStu + i)->uiChineseScore) / ((double)uiStuNumCount); 
        *dpMathScoreAverage    += (double)((pstStu + i)->uiMathScore)    / ((double)uiStuNumCount);
        *dpEnglishScoreAverage += (double)((pstStu + i)->uiEnglishScore) / ((double)uiStuNumCount);
    }

    return CALCEXE_RET_OK;
}


/************************************************************
FUNCTION:Calculating_Variance()
Description:该函数主要用来对输入的参数进行求平均值运算
Arguments:
Arg1:[In] 存放学生信息的结构体数组的指针
Arg2:[In] 学生个数
Arg3:[Out] 保存结果
return:成功返回CALCEXE_RET_OK ,如果输入参数的指针为NULL，返回CALCEXE_RET_FAIL
************************************************************/
int Calculating_StuScoreVariance(Stu_E * pstStu, unsigned int uiStuNumCount, double * dpChineseScoreVariance, 
                                            double * dpMathScoreVariance, double * dpEnglishScoreVariance)
{
    double dChineseScoreAverage = 0.0;
    double dMathScoreAverage = 0.0;
    double dEnglishScoreAverage = 0.0;
    int iRet = CALCEXE_RET_OK;
    
    calc_trace();

    if (pstStu == NULL || dpChineseScoreVariance == NULL || dpMathScoreVariance == NULL || dpEnglishScoreVariance == NULL)
    {
        calc_error("[%s]Input parameter is fail!\n", __FUNCTION__);
        return CALCEXE_RET_FAIL;
    }   

    iRet = Calculating_StuScoreAverage(pstStu, uiStuNumCount, &dChineseScoreAverage, &dMathScoreAverage, &dEnglishScoreAverage);
    if (iRet == CALCEXE_RET_FAIL)
    {
        calc_error("[%s]Calculating_StuScoreAverage is fail!\n", __FUNCTION__);
        return CALCEXE_RET_FAIL;
    }


    *dpChineseScoreVariance = 0.0;
    *dpMathScoreVariance = 0.0;
    *dpEnglishScoreVariance = 0.0;
    for (int i = 0; i < uiStuNumCount; i++)
    {
        *dpChineseScoreVariance += PF((double)((pstStu + i)->uiChineseScore) - dChineseScoreAverage)
                                    / ((double)uiStuNumCount); 
        *dpMathScoreVariance    += PF((double)((pstStu + i)->uiMathScore)     - dMathScoreAverage)
                                    / ((double)uiStuNumCount); 
        *dpEnglishScoreVariance += PF((double)((pstStu + i)->uiEnglishScore) - dEnglishScoreAverage)
                                    / ((double)uiStuNumCount); 
    }

    return CALCEXE_RET_OK;
}


