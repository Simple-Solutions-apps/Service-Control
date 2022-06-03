/*-------------------------------------------
  Copyright Simple Solutions, 2022
  Revised: 2022/05/23 22:13
-------------------------------------------*/

//conditional header guard wrapper to avoid processing more than once
#ifndef SERVICE_H
	#define SERVICE_H

	//standard includes
	#include <windows.h>

	//win32 function for service [Service.h]
	DWORD ServiceInitialization(DWORD argc, LPTSTR *argv, DWORD *specificError);

	//win32 function for service [Service.h]
	void WINAPI ServiceMain(DWORD argc, LPTSTR *argv);

	//win32 function for service [Service.h]	
	void WINAPI ServiceCtrlHandler(DWORD opcode);

//end of wrapper
#endif