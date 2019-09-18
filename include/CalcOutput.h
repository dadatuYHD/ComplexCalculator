/********************************************************
*   Copyright (C) 2017 All rights reserved.
*
*   Filename:CalcOutput.h
*   Author  :YHD
*   Date    :2017-05-01
*   Describe:
*
********************************************************/
#ifndef _CALCOUTPUT_H
#define _CALCOUTPUT_H

/*macro definition about hint message*/
#define CALCSTRING_CALC_MODE_INVAILD_SELECT_AGAIN                       (unsigned int)(0)
#define CALCSTRING_SELECT_MODE                                          (unsigned int)(1)
#define CALCSTRING_INPUT_1ST                                            (unsigned int)(2)
#define CALCSTRING_INPUT_2ST                                            (unsigned int)(3)
#define CALCSTRING_INPUT_OPERATOR                                       (unsigned int)(4)
#define CALCSTRING_INPUT_1ST_AGAIN                                      (unsigned int)(5)
#define CALCSTRING_INPUT_2ST_AGAIN                                      (unsigned int)(6)
#define CALCSTRING_INPUT_OPERATOR_AGAIN                                 (unsigned int)(7)
#define CALCSTRING_CONTINUE_OR_EXIT                                     (unsigned int)(8)
#define CALCSTRING_SIMPLE_CALC_RUNNING                                  (unsigned int)(9)
#define CALCSTRING_COMPLEX_CALC_RUNNING                                 (unsigned int)(10)
#define CALCSTRING_COMPLEX_MODE_STATISTICAL_METHOD                      (unsigned int)(11)
#define CALCSTRING_COMPLEX_MODE_STATISTICAL_METHOD_SLECT_AGAIN          (unsigned int)(12)
#define CALCSTRING_COMPLEX_MODE_INPUT_STU_INFO_SCORE_NAME               (unsigned int)(13)


/*macro definition about operator*/
#define OPERATOR_PLUS '+'
#define OPERATOR_MUB '-'
#define OPERATOR_MUL '*'
#define OPERATOR_DIV '/'


void CalcOutput_Result(unsigned int ui1stNum, char cOperator, unsigned int ui2ndNum, unsigned int uiResult);
void CalcOutput_HintMsg(unsigned int HintMsg);

#endif
