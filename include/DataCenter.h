/********************************************************
*   Copyright (C) 2017 All rights reserved.
*
*   Filename:DataCenter.h
*   Author  :yhd
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

int DataCenter_SetCalcMode(char *pcSelectMode);
int DataCenter_GetCalcMode(char *pcSelectMode);
int DataCenter_CreateCalcMode(void);
int DataCenter_DestoryCalcMode(void);

int DataCenter_SetCalcSimOper(SimpleModeCalc_St stSimModeCalcOperand, int flag);
int DataCenter_GetCalcSimOper(SimpleModeCalc_St * pstSimModeCalcOperand);
int DataCenter_CreateCalcSimOper(void);
int DataCenter_DestoryCalcSimOper(void);
    
int DataCenter_SetCalcClassInfo(Class_St stClass, int flag);
int DataCenter_GetCalcClassInfo(Class_St * pstClass, int flag);
int DataCenter_CreateCalcClassInfo(void);
int DataCenter_DestoryCalcClassInfo(void);

#endif