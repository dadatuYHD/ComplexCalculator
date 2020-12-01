/********************************************************
*   Copyright (C) 2017 All rights reserved.
*
*   Filename:CalcInput.c
*   Author  :yhd
*   Date    :2017-04-30
*   Describe:Calculator input processing related functions
*
********************************************************/
#include "../include/CalcState.h"
#include "../include/CalcInput.h"
#include "../include/calc_complex_debug.h"
#include <stdbool.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


#define BUFSIZE 128

int CalcInput_IntFromBuf(unsigned int * uipInputInt, char * pcInputBuf);
int CalcInput_NumCheck(unsigned int uipInputInt);
int CalcInput_StrNumConvertIntegerNum(unsigned int * uipInputInt, char * pcInputBuf);
int CalcInput_Operator(char * pcOperator);
int CalcInput_StringFromBuf(char * pcStuInfoName, char * pcStuInfoChineseSocre,
                                       char * pcStuInfoMathSocre, char * pcStuInfoEnglishSocre, 
                                       char * pcStuInfo);
int CalcInput_StuInfoCheck(Stu_E pStuInfo);
int CalcInput_StuInfoFromBuf(Stu_E * pStuInfo, char * pcStuInfo_a);

/*******************************************************************
* FUNCTION          :CalcInput_StuInfo()
* Description       :Read student information from standard input
* Arg1[pStuInfo][In]:Point to a buffer for storing student information
* return            :success return CALCINPUT_RET_OK,fail return 
*                    CALCINPUT_RET_FAIL
*******************************************************************/
int CalcInput_StuInfo(Stu_E * pStuInfo)
{
    char cStuInfo_a[BUFSIZE];
    int iRet = CALCINPUT_RET_OK;

    /*read student information from stdin*/
    memset(cStuInfo_a, 0, sizeof(cStuInfo_a));
    iRet = CalcInput_String(cStuInfo_a);
    if (iRet == CALCINPUT_RET_FAIL)
    {
        calc_error("CalcInput_String read string is fail!\n");
        return CALCINPUT_RET_FAIL;
    }

    /***********************************************************
     * Student information is extracted from ordinary 
     * strings and saved in the student information structure
     **********************************************************/
    iRet = CalcInput_StuInfoFromBuf(pStuInfo, cStuInfo_a);
    if (iRet == CALCINPUT_RET_FAIL)
    {
        calc_error("Error:Input student info & score fail,tryagain!\n");
        return CALCINPUT_RET_FAIL;
    }

    /*check the student information is valid*/
    iRet = CalcInput_StuInfoCheck(*pStuInfo);
    if (iRet == CALCINPUT_RET_FAIL)
    {
        calc_error("Error:Input student info & score fail,tryagain!\n");
        return CALCINPUT_RET_FAIL;
    }

    return CALCINPUT_RET_OK;
}

/******************************************************************************
* FUNCTION             :Calculating_Int()
* Description          :Read number string from standard input
* Arg1[uipInputInt][In]:Point to a buffer for storing number
* return               :success return CALCINPUT_RET_OK,string 
*                       is invalid and return CALCINPUT_RET_FAIL_INPUT_INVALID
                        OutofBound RETURN CALCINPUT_RET_FAIL_INPUT_OUTOFRANGE
*******************************************************************************/
int CalcInput_Int(unsigned int * uipInputInt)
{
    unsigned int iRet = CALCINPUT_RET_OK;
    char cInputBuf_a[BUFSIZE];

    /*read number string from standerd input*/
    memset(cInputBuf_a, 0, sizeof(cInputBuf_a));
    iRet = CalcInput_String(cInputBuf_a);
    if (iRet == CALCINPUT_RET_FAIL)
    {
        calc_error("[%s]String Input is fail!\n", __FUNCTION__);
        return CALCINPUT_RET_FAIL;
    }

    /*check number string is valid and convert to the integer number*/
    iRet = CalcInput_IntFromBuf(uipInputInt, cInputBuf_a);
    if (iRet == CALCINPUT_RET_FAIL)
    {
        calc_error("[%s]Input number is invalid!\n", __FUNCTION__);
        return CALCINPUT_RET_INPUT_INVALID;
    }

    /*check Input integer number is In a reasonable range*/
    iRet = CalcInput_NumCheck(*uipInputInt);
    if (iRet == CALCINPUT_RET_FAIL)
    {
        calc_error("[%s]Input number out of range\n", __FUNCTION__);
        return CALCINPUT_RET_INPUT_OUTOFRANGE;
    }

    return CALCINPUT_RET_OK;
}

/************************************************************
* FUNCTION            :Calculating_String()
* Description         :Read string from standard input
* Arg1[pcInputBuf][In]:Point to a buffer for storing STRING
* return              :success return CALCINPUT_RET_OK 
*                      fail return CALCINPUT_RET_FAIL
***********************************************************/
int CalcInput_String(char * pcInputBuf)
{
    /*read string number to the cc1stNum buffer*/
    memset(pcInputBuf, 0, sizeof(pcInputBuf));
    if (NULL == fgets(pcInputBuf, BUFSIZE, stdin))
    {
        perror("fgets");
        return CALCINPUT_RET_FAIL;
    }

    pcInputBuf[strlen(pcInputBuf)-1] = '\0';

    return CALCINPUT_RET_OK;
}

/***********************************************************************
* FUNCTION              :Calculating_IntFromBuf()
* Description           :string number to integer adn check Number 
*                        range
* Arguments:
* Arg1[uipInputInt][Out]:Point to after conversion integer 
* Arg2[pcInputBuf][In]  :Point to a buffer for storing string from
*                        Standard input
return                  :success return CALCINPUT_RET_OK,
*                        fail return CALCINPUT_RET_FAIL
************************************************************************/
int CalcInput_IntFromBuf(unsigned int * uipInputInt, char * pcInputBuf)
{
    int iRet = CALCINPUT_RET_OK;
    
    /*judge the input number is valid*/
    for (int i = 0; i < (strlen(pcInputBuf)); i++)
    {
        if (pcInputBuf[i] >= '0' && pcInputBuf[i] <= '9')
        {
            continue;
        }
        else
        {
            return CALCINPUT_RET_FAIL;
        }
    }

    /*string number convert to the integer number*/
    iRet = CalcInput_StrNumConvertIntegerNum(uipInputInt, pcInputBuf);
    if (iRet == CALCINPUT_RET_FAIL)
    {
        calc_error("CalcInput_StrNumConvertIntegerNum convert is fail!\n");
        return CALCINPUT_RET_FAIL;
    }

    return CALCINPUT_RET_OK;
}


/************************************************************
* FUNCTION              :CalcInput_StrNumConvertIntegerNum()
* Description           :string number to integer num
* Arg1[uipInputInt][Out]:
* Arg2[pcInputBuf][In]:
***********************************************************/
int CalcInput_StrNumConvertIntegerNum(unsigned int * uipInputInt, char * pcInputBuf)
{
    if (NULL == uipInputInt || NULL == pcInputBuf)
    {
        calc_error("Input parameter is fail!\n");
        return CALCINPUT_RET_FAIL;
    }

    *uipInputInt  = 0;
    for (int i = 0; i < (strlen(pcInputBuf)); i++)
    {
        if (pcInputBuf[i] < '0' || pcInputBuf[i] > '9')
        {
            return CALCINPUT_RET_INPUT_SCORE_FAIL;  
        }
        else
        {
            *uipInputInt  = *uipInputInt  * 10 + (pcInputBuf[i] - '0'); 
        }   
    }

    return CALCINPUT_RET_OK;
}

/************************************************************
* FUNCTION             :CalcInput_NumCheck()
* Description          :Check whether the converted number is 
*                       within a reasonable range
* Arguments:
* Arg1[uipInputInt][In]:Store the numbers to be checked
* return               :success return CALCINPUT_RET_OK,fail 
*                       return CALCINPUT_RET_FAIL
***********************************************************/
int CalcInput_NumCheck(unsigned int uipInputInt)
{
    if (uipInputInt < 0 || uipInputInt > 100)
    {
        return CALCINPUT_RET_FAIL;
    }

    return CALCINPUT_RET_OK;
}

/************************************************************
* FUNCTION   :CalcInput_char()
* Description:Handling of operator characters from 
*             standard input
* return     :success return CALCINPUT_RET_OK,fail 
*             return CALCINPUT_RET_FAIL
***********************************************************/
int CalcInput_Char(char * pcOperator)
{
    if (NULL == pcOperator)
    {
        calc_error("input param null\n");
        return CALCINPUT_RET_FAIL;
    }

    *pcOperator = getchar();

    char ch = '\0';
    /*discard current line Residual character*/
    while ((ch = getchar()) != '\n' && ch != EOF)
    {
        continue;
    }

    return CALCINPUT_RET_OK;
}


/************************************************************
* FUNCTION   :CalcInput_OperatorCheck()
* Description:Check whether the operation character is valid
* Arguments  :
* return     :success return CALCINPUT_RET_OK,fail 
*             return CALCINPUT_RET_FAIL
***********************************************************/
int CalcInput_OperatorCheck(char * pcOperator)
{
    /*judge the input Operator is valid*/
    if (*pcOperator != '+' && *pcOperator != '-'
         && *pcOperator != '*' && *pcOperator != '/')
    {
        calc_error("[%s]Operator Input is invalid!\n", __FUNCTION__);
        return CALCINPUT_RET_FAIL;
    }

    return CALCINPUT_RET_OK;
}

/**************************************************************************************
* FUNCTION                        :CalcInput_StringFromBuf()
* Description                     :Classify and extract the student string information 
*                                  from standard input into the corresponding buf
* return                          :success return CALCINPUT_RET_OK,fail 
*                                  return CALCINPUT_RET_FAIL
**************************************************************************************/
int CalcInput_StringFromBuf(char * pcStuInfoName, char * pcStuInfoChineseSocre,
                                       char * pcStuInfoMathSocre, char * pcStuInfoEnglishSocre, 
                                       char * pcStuInfo)
{
    unsigned int uiStrCount = 0;
    
    if (pcStuInfoName == NULL || pcStuInfoChineseSocre == NULL || pcStuInfoMathSocre == NULL
            || pcStuInfoEnglishSocre == NULL || pcStuInfo == NULL)
    {
        calc_error("Input parameter is fail!\n");
        return CALCINPUT_RET_FAIL;
    }

    while (uiStrCount < strlen(pcStuInfo))
    {
        while (1)
        {
            if (*pcStuInfo != ' '  && *pcStuInfo != '\0')
            {
                *pcStuInfoName = *pcStuInfo;
                pcStuInfoName++;
                pcStuInfo++;
                uiStrCount++;
            }
            else
            {
                switch (*pcStuInfo)
                {
                    case ' ':
                        pcStuInfo++;
                        uiStrCount++;
                        break;  
                    case '\0':
                        return CALCINPUT_RET_FAIL;
                    default:
                        break;          
                }
                break;
            }   
        }
        
        while (1)
        {
            if (*pcStuInfo != ' '  && *pcStuInfo != '\0')
            {
                *pcStuInfoChineseSocre = *pcStuInfo;
                pcStuInfoChineseSocre++;
                pcStuInfo++;
                uiStrCount++;
            }
            else
            {
                switch (*pcStuInfo)
                {
                    case ' ':
                        pcStuInfo++;
                        uiStrCount++;
                        break;  
                    case '\0':
                        return CALCINPUT_RET_FAIL;
                    default:
                        break;          
                }
                break;
            }   
        }
    
        while (1)
        {
            if (*pcStuInfo != ' '  && *pcStuInfo != '\0')
            {
                *pcStuInfoMathSocre = *pcStuInfo;
                pcStuInfoMathSocre++;
                pcStuInfo++;
                uiStrCount++;
            }
            else
            {
                switch (*pcStuInfo)
                {
                    case ' ':
                        pcStuInfo++;
                        uiStrCount++;
                        break;  
                    case '\0':
                        return CALCINPUT_RET_FAIL;
                    default:
                        break;          
                }
                break;
            }   
        }

        while (1)
        {
            if (*pcStuInfo != ' '  && *pcStuInfo != '\0')
            {
                *pcStuInfoEnglishSocre = *pcStuInfo;
                pcStuInfoEnglishSocre++;
                pcStuInfo++;
                uiStrCount++;
            }
            else
            {
                switch (*pcStuInfo)
                {
                    case ' ':
                        return CALCINPUT_RET_FAIL;  
                    case '\0':
                        break;
                    default:
                        break;          
                }
                break;
            }   
        }
    }

    return CALCINPUT_RET_OK;
}
                                       
/************************************************************
* FUNCTION   :CalcInput_StuInfoCheck()
* Description:Check if student information is valid
* return     :success return CALCINPUT_RET_OK,fail 
*             return CALCINPUT_RET_FAIL
***********************************************************/
int CalcInput_StuInfoCheck(Stu_E pStuInfo)
{
    for (int i = 0; pStuInfo.gcStuName[i] != '\0'; i++)
    {
        if ((pStuInfo.gcStuName[i] >= 'a' && pStuInfo.gcStuName[i] <= 'z') 
            || (pStuInfo.gcStuName[i] >= 'A' && pStuInfo.gcStuName[i] <= 'Z'))
        {
            continue;
        }
        else
        {
            return CALCINPUT_RET_FAIL;
        }
    }

    if ((pStuInfo.uiChineseScore < 0 || pStuInfo.uiChineseScore > 100) 
        || (pStuInfo.uiMathScore < 0 || pStuInfo.uiMathScore > 100)
        || (pStuInfo.uiEnglishScore < 0 || pStuInfo.uiEnglishScore > 100))
    {
        return CALCINPUT_RET_FAIL;
    }
    
    return CALCINPUT_RET_OK;
}

/************************************************************
* FUNCTION   :CalcInput_StuInfoFromBuf()
* Description:Extract the string information read by stdin 
*             into the student information structure
* return     :success return CALCINPUT_RET_OK,fail 
*             return CALCINPUT_RET_FAIL
************************************************************/
int CalcInput_StuInfoFromBuf(Stu_E * pStuInfo, char * pcStuInfo_a)
{
    char cStuInfoName_a[BUFSIZE];
    char cStuInfoChineseSocre_a[BUFSIZE];
    char cStuInfoMathSocre_a[BUFSIZE];
    char cStuInfoEnglishSocre_a[BUFSIZE];
    int iRet = CALCINPUT_RET_OK;

    /*dump student information from cStuInfo_a buf*/
    memset(cStuInfoName_a, 0, sizeof(cStuInfoName_a));
    memset(cStuInfoChineseSocre_a, 0, sizeof(cStuInfoChineseSocre_a));
    memset(cStuInfoMathSocre_a, 0, sizeof(cStuInfoMathSocre_a));
    memset(cStuInfoEnglishSocre_a, 0, sizeof(cStuInfoEnglishSocre_a));
    iRet = CalcInput_StringFromBuf(cStuInfoName_a, cStuInfoChineseSocre_a,
                                   cStuInfoMathSocre_a,cStuInfoEnglishSocre_a, pcStuInfo_a);
    if (iRet == CALCINPUT_RET_FAIL)
    {
        calc_error("CalcInput_StringFromBuf dump is fail!\n");
        return CALCINPUT_RET_FAIL;
    }

    /***********************************************************************
    * Fill the student information structure, convert the score represented 
    * by the student string into an integer representation, and save it in 
    * the student structure
    ************************************************************************/
    strncpy(pStuInfo->gcStuName, cStuInfoName_a, sizeof(cStuInfoName_a));
#if 1
    iRet = CalcInput_StrNumConvertIntegerNum(&(pStuInfo->uiChineseScore), cStuInfoChineseSocre_a);
    if (iRet == CALCINPUT_RET_INPUT_SCORE_FAIL)
    {
        calc_error("Error:Input student info & score fail,tryagain!\n");
        return CALCINPUT_RET_FAIL;
    }
    iRet = CalcInput_StrNumConvertIntegerNum(&(pStuInfo->uiMathScore), cStuInfoMathSocre_a);
    if (iRet == CALCINPUT_RET_INPUT_SCORE_FAIL)
    {
        calc_error("Error:Input student info & score fail,tryagain!\n");
        return CALCINPUT_RET_FAIL;
    }
    iRet = CalcInput_StrNumConvertIntegerNum(&(pStuInfo->uiEnglishScore), cStuInfoEnglishSocre_a);
    if (iRet == CALCINPUT_RET_INPUT_SCORE_FAIL)
    {
        calc_error("Error:Input student info & score fail,tryagain!\n");
        return CALCINPUT_RET_FAIL;
    }
#endif
    /*calc_printf("pStuInfo->gcStuName = %s, pStuInfo->uiChineseScore = %d, pStuInfo->uiMathScore = %d, pStuInfo->uiEnglishScore = %d\n", 
                        pStuInfo->gcStuName, pStuInfo->uiChineseScore, 
                        pStuInfo->uiMathScore, pStuInfo->uiEnglishScore);*/ 
}

