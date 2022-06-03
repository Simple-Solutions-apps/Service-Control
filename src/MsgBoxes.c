/*-------------------------------------------
  Copyright Simple Solutions, 2022
  Revised: 2022/05/26 21:50
-------------------------------------------*/

//Standard includes
#include <windows.h>
#include <stddef.h>
#include <stdio.h>

//custom includes
#include "..\include\MsgBoxes.h"

void InfoBox(char* FormatText, char* Var)
{
	char *cDisplayPrompt;
	size_t iDisplayPromptLen = strlen(FormatText) + strlen(Var) + 1;

	cDisplayPrompt = calloc(iDisplayPromptLen, sizeof (char));

	if(cDisplayPrompt != NULL && sprintf(cDisplayPrompt, FormatText, Var) > 0)
	{
		MessageBox(NULL, cDisplayPrompt, "Information", MB_ICONINFORMATION | MB_OK | MB_TOPMOST);
	}
	else
	{
		MessageBox(NULL, "Unable to create information box", "Error", MB_ICONERROR | MB_OK | MB_TOPMOST);
	}

	free(cDisplayPrompt);

}
void ErrorBox(char* FormatText, char * Var)
{
	char *cDisplayPrompt;
	size_t iDisplayPromptLen = strlen(FormatText) + strlen(Var) + 1;

	cDisplayPrompt = calloc(iDisplayPromptLen, sizeof (char));

	if(cDisplayPrompt != NULL && sprintf(cDisplayPrompt, FormatText, Var) > 0)
	{
		MessageBox(NULL, cDisplayPrompt, "Error", MB_ICONERROR | MB_OK | MB_TOPMOST);
	}
	else
	{
		MessageBox(NULL, "Unable to create error box", "Error", MB_ICONERROR | MB_OK | MB_TOPMOST);
	}

	free(cDisplayPrompt);

}
void NumBox(char* FormatText, int Var)
{
	char *cDisplayPrompt;
	size_t iDisplayPromptLen = strlen(FormatText) + sizeof (Var) + 1;

	cDisplayPrompt = calloc(iDisplayPromptLen, sizeof (char));

	if(cDisplayPrompt != NULL && sprintf(cDisplayPrompt, FormatText, Var) > 0)
	{
		MessageBox(NULL, cDisplayPrompt, "Information", MB_ICONINFORMATION | MB_OK | MB_TOPMOST);
	}
	else
	{
		MessageBox(NULL, "Unable to number box", "Error", MB_ICONERROR | MB_OK | MB_TOPMOST);
	}

	free(cDisplayPrompt);

}
