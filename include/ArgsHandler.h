/*-------------------------------------------
  Copyright Simple Solutions, 2022
  Revised: 2022/05/21 21:42
-------------------------------------------*/

//conditional header guard wrapper to avoid processing more than once
#ifndef ARGHANDLER_H
	#define ARGHANDLER_H

	//returns the index of the argument found [ArgsHandler.h]
	int GetArgIndex(char* cArg, char **cArgs, int iArgsc);

//end of wrapper
#endif