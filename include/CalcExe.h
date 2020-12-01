/********************************************************
*   Copyright (C) 2017 All rights reserved.
*
*   Filename:CalcExe.h
*   Author  :yhd
*   Date    :2017-04-30
*   Describe:
*
********************************************************/
#ifndef _CALCEXE_H
#define _CALCEXE_H

#define CALCEXE_RET_OK          (0)
#define CALCEXE_RET_FAIL           (-1)
#define CALCEXE_RET_FAIL_DENOMINATOR_ZERO (-2)
#define CALCEXE_RET_FAIL_1ST_LESS_2ND   (-3)


int Calculating_Sum(unsigned int * gui1stNum, unsigned int * gui2ndNum,unsigned int * guiResult);

int Calculating_Mub(unsigned int * gui1stNum, unsigned int * gui2ndNum,unsigned int * guiResult);

int Calculating_Mul(unsigned int * gui1stNum, unsigned int * gui2ndNum,unsigned int * guiResult);

int Calculating_Div(unsigned int * gui1stNum, unsigned int * gui2ndNum,unsigned int * guiResult);

int Calculating_StuScoreAverage(Stu_E * pstStu, unsigned int uiStuNumCount, double * dpChineseScoreAverage, 
                                            double * dpMathScoreAverage, double * dpEnglishScoreAverage);

int Calculating_StuScoreVariance(Stu_E * pstStu, unsigned int uiStuNumCount, double * dpChineseScoreVariance, 
                                            double * dpMathScoreVariance, double * dpEnglishScoreVariance);



#endif
