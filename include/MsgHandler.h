/*-------------------------------------------
  Copyright Simple Solutions, 2022
  Revised: 2022/05/23 21:32
-------------------------------------------*/

//conditional header guard wrapper to avoid processing more than once
#ifndef MSGHANDLER_H
	#define MSGHANDLER_H

	//Custom definitions
	#define MSGERROR 1
	#define MSGINFO 2	 
	#define MSGWARN 3
	#define MSGALL 4
	#define MSGDEBUG 5

	//prints message in accordance with verbose parameter [MsgHandler.h]
	void MsgPrint(char *cString, char *cVar, int iVerbose, int iType);

//end of wrapper
#endif