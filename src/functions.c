/*-------------------------------------------
  Copyright Simple Solutions, 2022
  Revised: 2022/05/21 20:51
-------------------------------------------*/

//Standard includes
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <errno.h>

//Custom includes
#include "..\include\functions.h"
#include "..\include\UtilsStrings.h"
#include "..\include\UtilsStorageIO.h"

//Prints help message
void PrintHelp(const char *cThisExecName)
{
	printf("\n                 Version: 1.0\n");
	printf("DESCRIPTION:\n");
	printf("          %s  monitors a directory for file additions and forwards them\n", cThisExecName);
	printf("                         to a broker executable as its only argument/parameter\n");
	printf("USAGE:\n");
	printf("          %s [options...]\n", cThisExecName);
	printf("OPTIONS:\n");
	printf("          -v <verbose message level> ---------1 = Errors only\n");
	printf("                                              2 = Information only\n");
	printf("                                              3 = Warnings only\n");
	printf("                                              4 = All messages\n");
	printf("          -h ---------------------------------Prints this help message\n");
	printf("          -q <folder path> -------------------Queue folder path\n");
	printf("                                              (folder to monitored)\n");
	printf("          -b <file path of broker executable> Executable that handles\n");
	printf("                                              files in queue folder\n");
	printf("          -s <seconds> -----------------------Seconds of delay\n");
	printf("                                              between each scan\n");
	printf("          -c --------------------------------- Run in command line mode (not as service)\n");
	printf("EXAMPLE:\n");
	printf("          FolderMonSVC -c -b \"C:\\FileBroker.exe\" -q \"C:\\QueueFolder\"\n");
}

int ScanFolder(char *cFolderPathQueue, char *cFilePathBroker, char *cThisExecFileName)
{
	//validate arguments
	if(Exists(cFolderPathQueue) != 1)
	{
		return __LINE__;
	}
	if(Exists(cFilePathBroker) != 2)
	{
		return __LINE__;
	}

	//declare length of string
	int iStrLen = 0;

	//declare error result
	int iErrorResult;

	//declare command line to execute in system call
	char *cCommandLine;

	//declare directory item file path
	char *cFilePathItem;

	//declare temporary lower case directory item
	char *cLCaseBuff;

	//declare this executable/program file name in lower case
	char *cThisExecFileNameLCase;

	//declare processed folder path
	char *cFolderPathProcessed;

	//declare processed file path
	char *cFilePathProcessed;	

	//define path of file to process
	iStrLen = strlen(cFolderPathQueue) + FILENAME_MAX + 2; //+2 to accommodate NULL/terminator character and "\"
    cFilePathItem = malloc(iStrLen * sizeof (char));

	//define path of folder for processed files
	iStrLen = strlen(cFolderPathQueue) + 15; //+15 to accommodate "\Processed", NULL/terminator character
	cFolderPathProcessed = malloc(iStrLen * sizeof (char));

	//define path of file after processed
	iStrLen = iStrLen + FILENAME_MAX + 7; //+2 to accommodate NULL/terminator character and "\"
	cFilePathProcessed = malloc(iStrLen * sizeof (char));

	//define command line to execute
	iStrLen = strlen(cFilePathBroker) + iStrLen + 20; //+20 to accommodate additional command line characters
    cCommandLine = malloc(iStrLen * sizeof (char));

	//define this executable's filename in lowercase
    cThisExecFileNameLCase = malloc(iStrLen * sizeof (char)); 

	//assign this executable's filename in lowercase
	iErrorResult = StrToLower(cThisExecFileName, &cThisExecFileNameLCase);	

	//assign path of folder for processed files
	cFolderPathProcessed = strcpy(cFolderPathProcessed, cFolderPathQueue);
	cFolderPathProcessed = strcat(cFolderPathProcessed, "\\Processed");

	//error creating lower case string
	if(iErrorResult != 0)
	{
		return __LINE__;
	}

	//try to create processed folder
	if((mkdir(cFolderPathProcessed)) == -1 && errno != EEXIST)
	{
		return __LINE__;
	}

	//Try to open queue folder (folder to be monitored)
	DIR *dFolderQueue;
	struct dirent *sEntry;
	dFolderQueue = opendir(cFolderPathQueue);	
	if(dFolderQueue == NULL)
	{
		return __LINE__;
	}
	
	//scan folder
	while((sEntry = readdir(dFolderQueue)) != NULL)
	{
		//assign item file path 
		sprintf(cFilePathItem, "%s\\%s", cFolderPathQueue, sEntry->d_name);
				
		//assign temporary buffer with lower case entry item file name
		iErrorResult = StrToLower(sEntry->d_name, &cLCaseBuff);
		if(iErrorResult != 0)
		{
			return __LINE__;
		}
		
		//ignore ".", ".." and this executable/program name as files whenever found
		if(Exists(cFilePathItem) == 2
			&& strcmp(sEntry->d_name, ".") != 0
			&& strcmp(sEntry->d_name, "..") != 0
			&& strcmp(cThisExecFileNameLCase, cLCaseBuff) != 0
			)
		{
			//assign processed file path 
			sprintf(cFilePathProcessed, "%s\\%s", cFolderPathProcessed, sEntry->d_name);		
			if(cFilePathProcessed == NULL)
			{
				return __LINE__;
			}

			//assign unique processed file path
			cFilePathProcessed = CreateUniqueFileName(cFilePathProcessed);
			if(cFilePathProcessed == NULL)
			{
				return __LINE__;
			}
		
			//assign command line to execute with new file name
			sprintf(cCommandLine, "\"start /b \"\" \"%s\" \"%s\"\"", cFilePathBroker, cFilePathProcessed);

			//try to move item file to processed folder
			if(rename(cFilePathItem, cFilePathProcessed) == -1)
			{
				//skip item/file until next scan is called (file may be opened by another process)
				continue;
			}

			//call system command "start" and execute broker executable file
			system(cCommandLine);
			                
		}	    
	}

	//free dynamic memory
	free(cCommandLine);
	free(cFilePathItem);
	free(cLCaseBuff);
	free(cThisExecFileNameLCase);
	free(cFolderPathProcessed);
	free(cFilePathProcessed);

	return 0;
}
