/*-------------------------------------------
  Copyright Simple Solutions, 2022
  Revised: 2022/05/21 21:12
-------------------------------------------*/

//Standard includes
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <libgen.h>

//Custom includes
#include "..\include\UtilsStorageIO.h"
#include "..\include\UtilsStrings.h"

//if file or directory exists (1 = directory, 2 = file) [UtilsStorageIO.h]
int Exists(char *cPath)
{
  if(access(cPath, R_OK | W_OK) == 0)
  {
    //file or directory exists and is read-write accessible

    //Check if directory
    DIR* dDir;
    if((dDir = opendir(cPath)) != NULL)
    {
      //is a directory
      closedir(dDir);
      return 1;
    }

    //check if file
    FILE *fFile;
   if ((fFile = fopen(cPath, "r")) != NULL)
    {
      //is a file
      fclose(fFile);
      return 2;
    }
  }
  
  //file or directory does not exists
  return 0;
}

//stores this executable file name to a pointer [UtilsStorageIO.h]
void GetThisExecName(char *cArgv, char *cThisExecFileNameBuff)
{ 
  int cFileNameLen = strlen(basename(cArgv)) + 5; //+4 characters for posible ".exe" extension insertion
  char *cTempBuff = malloc(cFileNameLen * sizeof (char));
  
  if(cTempBuff == NULL)
  {
    cThisExecFileNameBuff = NULL;
    return;
  }  

  cTempBuff = basename(cArgv);

  if(strstr(cTempBuff, ".exe") == NULL)
  {
    strcat(cTempBuff, ".exe");
  }
  
  strcat(cTempBuff, "\0");
  cThisExecFileNameBuff = strcpy(cThisExecFileNameBuff, cTempBuff);
}

//creates a unique file name [UtilsStorageIO.h]
char *CreateUniqueFileName(char *cFilePath)
{
  //declare variables
  int iSuffix = 1;
  int iFilePathLen = strlen(cFilePath);
  int iExtPos = GetLast(cFilePath, ".");
  int iExtLen = (iFilePathLen - iExtPos) + 1; //+1 = one more character: the "." (dot)
  int iNewFilePathWOutExtLen = iFilePathLen - iExtLen;

  char *cExt;
  char *cNewFilePathWOutExt;
  char *cNewFilePath;

  FILE *fTestFile;

  //define variables
  cExt = calloc((iExtLen + 1), sizeof (char));
  cNewFilePathWOutExt = calloc((iNewFilePathWOutExtLen + 1), sizeof (char));
  cNewFilePath = calloc((iFilePathLen + 7), sizeof (char));

  //assign variables
  strcpy(cExt, &cFilePath[iNewFilePathWOutExtLen]);
  strncpy(cNewFilePathWOutExt, cFilePath, iNewFilePathWOutExtLen);
  sprintf(cNewFilePath,"%s(%04d)%s", cNewFilePathWOutExt, iSuffix, cExt);

  //check if file already exists
  while((fTestFile = fopen(cNewFilePath, "r")) != NULL)
  {
    fclose(fTestFile);
    iSuffix++; //increment suffix
    //check if suffix limit
    if(iSuffix > 9999)
    {
      return NULL;
    }
    //assign incremented suffix
    sprintf(cNewFilePath,"%s(%04d)%s", cNewFilePathWOutExt, iSuffix, cExt);
  }

  fclose(fTestFile);

  return cNewFilePath;
}