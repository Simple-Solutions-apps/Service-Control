/*-------------------------------------------
  Copyright Simple Solutions, 2022
  Revised: 2022/05/21 21:11
-------------------------------------------*/

//Standard includes
#include <stdio.h>

//Custom includes
#include "..\include\MsgHandler.h"

//print verbose message
void MsgPrint(char *cString, char *cVar, int iVerbose, int iType)
{	
	//standard messages
	if(iVerbose == iType || iVerbose == MSGALL)
	{
		switch(iVerbose)
		{
			case 1:
				printf("(X) %s %s\n", cString, cVar);
				break;
			case 2:
				printf("(i) %s %s\n", cString, cVar);
				break;
			case 3:
				printf("(!) %s %s\n", cString, cVar);
				break;
			case 4: //print all non debug messages
				switch(iType)
				{
					case MSGERROR:
						printf("(X) %s %s\n", cString, cVar);
						break;
					case MSGINFO:
						printf("(i) %s %s\n", cString, cVar);
						break;
					case MSGWARN:
						printf("(!) %s %s\n", cString, cVar);
						break;
				}
				break;		
		}
	}

	//debug messages
	if(iVerbose == iType && iType == MSGDEBUG)
	{
		printf("(%c) %s %s\n", 15, cString, cVar);
	}
}