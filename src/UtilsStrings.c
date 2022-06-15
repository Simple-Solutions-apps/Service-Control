/*-------------------------------------------
  Copyright Simple Solutions, 2021
  Revised: 2021/09/24 14:13
-------------------------------------------*/

//Standard includes
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

//custom includes
#include "..\include\UtilsStrings.h"

//determine if string is a integer
int IsInt(char *cString)
{
  for(int i = 0; cString[i] != '\0'; i++)
  {
    if(isdigit(cString[i]) == 0)
    {      
      return i + 1;
    }            
  }

  return 0;
}

//get last occurrence of cFind in a string
int GetLast(char *cString, char *cFind)
{
  int iStrLen = strlen(cString);
  int iFindLen = strlen(cFind);
  int iPos = 0;
  int iIndex = 0;

  char cFindBuff[iFindLen + 1];

  //recurs backwards and search for an occurrence
  for(int i = 0; i <= iStrLen; i++)
  {
    if(i < iFindLen)
    {
      continue;
    }

    iIndex = 0;
    iPos = iStrLen - i;

    for(int j = iPos; j < (iPos + iFindLen); j++)
    {
		cFindBuff[iIndex] = cString[j];
		iIndex++;
    }

    cFindBuff[iIndex] = '\0';
	    
    if(strcmp(cFindBuff, cFind) == 0)
    {
      return iPos + 1;
    } 
  }

  return -1;
}

//convert string to lowercase string
int StrToLower(char *cString, char **cLCaseBuff)
{
  if(cString == NULL)
  {
    return __LINE__;
  }

  int iStrLen = strlen(cString);

  char *cTempBuff = malloc((iStrLen + 1) * sizeof (char));

  if(cTempBuff == NULL)
  {
    return __LINE__;
  }
  
  for(int i = 0; i <= iStrLen; i++)
  {
    if(cString[i] >= 65 && cString[i] <= 90)
    {
      cTempBuff[i] = cString[i] + 32;
    }
    else
    {
      cTempBuff[i] = cString[i];
    }
  }

  cTempBuff = strcat(cTempBuff, "\0");

  *cLCaseBuff = cTempBuff;

  return 0; 
}