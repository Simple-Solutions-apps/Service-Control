/*-------------------------------------------
  Copyright Simple Solutions, 2022
  Revised: 2022/05/21 21:24
-------------------------------------------*/

//conditional header guard wrapper to avoid Processing more than once
#ifndef STORAGEIO_H
	#define STORAGEIO_H

	//determins if a file or folder exists and is accessible [UtilsStorageIO.h]
	int Exists(char *cPath);
	
	//saves this executable/program file name to a pointer [UtilsStorageIO.h]
	void GetThisExecName(char *cArgv, char *cThisExecFileNameBuff);

	//Creates a unique file name in parent folder of a file name path [UtilsStorageIO.h]
	char *CreateUniqueFileName(char *cFilePath);

//end of wrapper
#endif