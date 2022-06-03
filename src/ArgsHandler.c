/*-------------------------------------------
  Copyright Simple Solutions, 2022
  Revised: 2022/05/21 20:51
-------------------------------------------*/

//Standard includes
#include <string.h>

//Custom includes
#include "..\include\ArgsHandler.h"

//get requested argument value
int GetArgIndex(char *cArg, char **cArgs, int iArgsc)
{	
	//Argument handnling    
	for(int iArg = 0; iArg < iArgsc; iArg++)
	{
		if(strcmp(cArgs[iArg], cArg) == 0)
		{
			//Argument found, return index where
			return iArg;
		}          
	}

	//Could not find requested argument
	return -1;
}