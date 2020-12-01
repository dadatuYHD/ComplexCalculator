/********************************************************
*   Copyright (C) 2017 All rights reserved.
*
*   Filename:CalcOutput.c
*   Author  :yhd
*   Date    :2017-05-01
*   Describe:calculator output model
*
********************************************************/
#include "../include/CalcOutput.h"
#include "../include/calc_complex_debug.h"
#include <stdbool.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


/************************************************************
 * FUNCTION   :CalcOutput_Result()
 * Description:Output Tips
***********************************************************/
void CalcOutput_Result(unsigned int ui1stNum, char cOperator, unsigned int ui2ndNum, unsigned int uiResult)
{
    switch (cOperator)
    {
        case OPERATOR_PLUS:
            calc_running("The result is: %d %c %d = %d\n", ui1stNum, cOperator, ui2ndNum, uiResult);
            break;
        case OPERATOR_MUB:
            calc_running("The result is: %d %c %d = %d\n", ui1stNum, cOperator, ui2ndNum, uiResult);
            break;
        case OPERATOR_MUL:
            calc_running("The result is: %d %c %d = %d\n", ui1stNum, cOperator, ui2ndNum, uiResult);
            break;
        case OPERATOR_DIV:
            calc_running("The result is: %d %c %d = %d\n", ui1stNum, cOperator, ui2ndNum, uiResult);
            break;
        default:
            break;
    }
}

/************************************************************
* FUNCTION        :CalcOutput_HintMsg()
* Description     :Output tips
* Arguments       :
* Arg[HintMsg][In]:slect tips
* return:void
***********************************************************/
void CalcOutput_HintMsg(unsigned int HintMsg)
{
    switch (HintMsg)
    {
        case CALCSTRING_CALC_MODE_INVAILD_SELECT_AGAIN:
            calc_running("Calc mode invalid,Select again!\n");
            break;
        case CALCSTRING_SELECT_MODE:
            calc_running("Select mode please: \n");
            calc_running("S. simple mode: \n");
            calc_running("C. complex mode: \n");
            break;
        case CALCSTRING_INPUT_1ST:
            calc_running("Please Input 1stNumber: ");
            break;
        case CALCSTRING_INPUT_2ST:
            calc_running("Please Input 2ndNumber: ");
            break;
        case CALCSTRING_INPUT_OPERATOR:
            calc_running("Please Input Operator: ");
            break;
        case CALCSTRING_INPUT_1ST_AGAIN:
            calc_running("Please Input 1stNumber again!\n");
            break;
        case CALCSTRING_INPUT_2ST_AGAIN:
            calc_running("Please Input 2ndNumber again!\n");
            break;
        case CALCSTRING_INPUT_OPERATOR_AGAIN:
            calc_running("Please Input Operator again!\n");
            break;
        case CALCSTRING_CONTINUE_OR_EXIT:
            calc_running("Input any char to continue or input E to exit!\n");
            break;
        case CALCSTRING_SIMPLE_CALC_RUNNING:
            calc_running("S.Simple calc running!\n");
            break;
        case CALCSTRING_COMPLEX_CALC_RUNNING:
            calc_running("C.Complex calc running!\n");
            break;
        case CALCSTRING_COMPLEX_MODE_STATISTICAL_METHOD:
            calc_running("Input ISI to input student info & score!\n");
            calc_running("Input PSI to print student info & score!\n");
            calc_running("Input CA to calc average!\n");
            calc_running("Input CV to calc variance!\n");
            calc_running("Input PA to print average!\n");
            calc_running("Input PV to print variance!\n");
            calc_running("Input E to exit!\n");
            break;
        case CALCSTRING_COMPLEX_MODE_STATISTICAL_METHOD_SLECT_AGAIN:
            calc_running("Select statistical method fail,Input again!\n");
            break;
        case CALCSTRING_COMPLEX_MODE_INPUT_STU_INFO_SCORE_NAME:
            calc_running("Input student info & score: name 45 64 85!\n");
            break;
        default:
            break;
    }
}
