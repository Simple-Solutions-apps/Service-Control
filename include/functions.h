/*-------------------------------------------
  Copyright Simple Solutions, 2022
  Revised: 2022/05/21 21:43
-------------------------------------------*/

//conditional header guard wrapper to avoid processing more than once
#ifndef FUNCTIONS_H
	#define FUNCTIONS_H

	//Prints help message [functions.h]
	void PrintHelp(const char *cThisExecName);

	//scans queue folder and processes file [functions.h]
	int ScanFolder(char *cFolderPathQueue, char *cFilePathBroker, char *cThisExecFileName);

//end of wrapper
#endif