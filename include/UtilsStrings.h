/*-------------------------------------------
  Copyright Simple Solutions, 2022
  Revised: 2022/05/21 21:48
-------------------------------------------*/

//conditional header guard wrapper to avoid processing more than once
#ifndef STRINGS_H
	#define STRINGS_H

	//determins if character parameter is an integer [UtilsStrings.h]
	int IsInt(char *cString);

	//searches for a string within another starting from back to front [UtilsStrings.h]
	int GetLast(char *cString, char *cFind);

	//convert string to lowercase string [UtilsStrings.h]
	int StrToLower(char *cString, char **cStrLCase);

//end of wrapper
#endif