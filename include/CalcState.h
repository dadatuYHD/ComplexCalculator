/********************************************************
*   Copyright (C) 2017 All rights reserved.
*
*   Filename:CalState.h
*   Author  :YHD
*   Date    :2017-04-27
*   Describe:
*
********************************************************/
#ifndef _CALSTATE_H
#define _CALSTATE_H

/*macro definition about return value*/
#define CALCSTATE_RET_OK                    (0)
#define CALCSTATE_RET_FAIL                  (-1)
#define CALCSTATE_RET_FAIL_INPUTPARAMNULL   (-2)

#define STUDENT_CEILING 5
#include <stdbool.h>

/*declare strcture about student message*/
typedef struct 
{
    char gcStuName[128];                            /*calculator complex mode student name string global*/
    unsigned int uiChineseScore;                    /*calculator complex mode student  Chinese Score global*/
    unsigned int uiMathScore;                       /*calculator complex mode student  Math  Score global*/
    unsigned int uiEnglishScore;                    /*calculator complex mode student  English  Score global*/
}Stu_E;

/*declare strcture about class message*/
typedef struct
{
    Stu_E stStu_a[STUDENT_CEILING];
    double gdChineseScoreAverage;                   /*the average of chinese*/
    double gdMathScoreAverage;
    double gdEnglishScoreAverage;
    double gdChineseScoreVariance;              /*the variance of chinese*/
    double gdMathScoreVariance;
    double gdEnglishScoreVariance;
    unsigned int guiCurStuNumCount;              /*student numbers count global*/
    bool gbAverageInfoReady;                    /*judge the average is calculator*/
    bool gbVarianceInfoReady;
}Class_St;

/*calculator simple mode operand structure*/
typedef struct
{
    unsigned int gui1stNum;                         /*calculator simple mode 1st number global*/
    unsigned int gui2ndNum;                         /*calculator simple mode 2nd number globol*/
    unsigned int guiResult;                         /*calculator simple mode operating result global*/
    char gcOperator;                                /*calculator simple mode operator char global*/    
}SimpleModeCalc_St;

/*major state*/
void CalcState_Main(void);


#endif
