/********************************************************
*   Copyright (C) 2017 All rights reserved.
*
*   Filename:calc_simple_YHD.h
*   Author  :yhd
*   Date    :2017-04-30
*   Describe:
*
********************************************************/
#ifndef _CALC_COMPLEX_DEBUG_H
#define _CALC_COMPLEX_DEBUG_H

//#define CALC_DEBUG
//#define CALC_TRACE
#define CALC_ERROR

#ifdef CALC_DEBUG
#define calc_printf(fmt, arg...) printf("[calc] "fmt,##arg)
#else
#define calc_printf(a,...) do{}while(0)
#endif

#ifdef CALC_TRACE
#define calc_trace(fmt, arg...) printf("[calc][%s][%d][%s]\n",__FUNCTION__,__LINE__, __FILE__)
#else
#define calc_trace(a,...) do{}while(0)
#endif

#ifdef CALC_ERROR
#define calc_error(fmt, arg...) printf("[calc][ERROR]"fmt,##arg)
#else
#define calc_error(a,...) do{}while(0)
#endif

#define calc_running(fmt, arg...) printf(">> "fmt,##arg)


#endif
