/********************************************************
 *   Copyright (C) 2017 All rights reserved.
 *
 *   Filename:calc_conmplex_YHD.c
 *   Author  :叶鸿达
 *   Date    :2017-04-25
 *   Describe:主函数用于状态控制
 *
 ********************************************************/
#include "../include/calc_complex_debug.h"
#include "../include/CalcState.h"
#include "../include/CalcOutput.h"
#include <stdbool.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
    /*calculator start working.........*/
    CalcState_Main();

    return 0;
}


