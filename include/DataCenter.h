/********************************************************
*   Copyright (C) 2017 All rights reserved.
*
*   Filename:DataCenter.h
*   Author  :YHD
*   Date    :2017-05-23
*   Describe:
*
********************************************************/

#ifndef _DATACENTER_H
#define _DATACENTER_H

#define DATACENTER_RET_OK                     0
#define DATACENTER_RET_FAIL                  -1

#define DATA_SELECTMODE_DEFAULT               1

#define DATA_CALCSIMPLE_DEFAULT               2
#define DATA_CALCSIMPLE_WRITE_1STNUM          3
#define DATA_CALCSIMPLE_WRITE_2NDNUM          4
#define DATA_CALCSIMPLE_WRITE_OPERATOR        5
#define DATA_CALCSIMPLE_WRITE_RESULT          6

#define DATA_CALCCOMPLEX_DEFAULT              7
#define DATA_CALCCOMPLEX_WRITE_STUINFO        8
#define DATA_CALCCOMPLEX_WRITE_AVERAGE        9
#define DATA_CALCCOMPLEX_WRITE_VARIANCE       10
#define DATA_CALCCOMPLEX_WRITE_AVERAGE_READY  11
#define DATA_CALCCOMPLEX_WRITE_VARIANCE_READY 12

int DataCenter_WriteStateMacMajorModeSel(char *pcSelectMode, int flag);
int DataCenter_ReadStateMacMajorModeSel(char *pcSelectMode, int flag);
int DataCenter_StateMacMajorModeSelCreateDataCenter(void);
int DataCenter_StateMacMajorModeSelDestoryDataCenter(void);

int DataCenter_WriteCalcSimModeOperand(SimpleModeCalc_St stSimModeCalcOperand, int flag);
int DataCenter_ReadCalcSimModeOperand(SimpleModeCalc_St * pstSimModeCalcOperand, int flag);
int DataCenter_CalcSimModeOperandCreateDataCenter(void);
int DataCenter_CalcSimModeOperandDestoryDataCenter(void);
    
int DataCenter_WriteCalcComplexModeClassInfo(Class_St stClass, int flag);
int DataCenter_ReadCalcComplexModeClassInfo(Class_St * pstClass, int flag);
int DataCenter_CalcComplexModeCreateDataCenter(void);
int DataCenter_CalcComplexModeDestoryDataCenter(void);

#endif