/********************************************************
 *   Copyright (C) 2017 All rights reserved.
 *
 *   Filename:CalcComplexMain.c
 *   Author  :yhd
 *   Date    :2017-04-25
 *   modified:2020-11-29
 *   Describe:Main function for state control
 *   
 ********************************************************/
#include <stdbool.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../include/calc_complex_debug.h"
#include "../include/CalcState.h"
#include "../include/CalcOutput.h"


int main(int argc, char *argv[])
{
    /***********************************
     * 
     *    calculator start working
     *
     **********************************/
    CalcState_Main();

    return 0;
}


