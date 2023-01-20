/*-------------------------------------------
  Copyright Simple Solutions, 2022
  Revised: 2022/05/26 21:50
-------------------------------------------*/

//Standard includes
#include <windows.h>
#include <strsafe.h>
#include <stddef.h>
#include <stdio.h>

//custom includes
#include "..\include\MsgBoxes.h"

void InfoBox(STRSAFE_LPCWSTR FormatText, char *Var)
{
	LPTSTR cDisplayPrompt;
	HRESULT hResult;
	size_t iDisplayPromptLen = lstrlen(FormatText) + strlen(Var) + 1;

	cDisplayPrompt = calloc(iDisplayPromptLen, sizeof (LPTSTR));
	hResult = StringCchPrintf(cDisplayPrompt, iDisplayPromptLen, FormatText, Var);

	if(cDisplayPrompt != NULL && hResult == S_OK)
	{
		MessageBox(NULL, cDisplayPrompt,  TEXT("Information"), MB_ICONINFORMATION | MB_OK | MB_TOPMOST);
	}
	else
	{
		MessageBox(NULL,  TEXT("Unable to create information box"),  TEXT("Error"), MB_ICONERROR | MB_OK | MB_TOPMOST);
	}

	free(cDisplayPrompt);

}
void ErrorBox(STRSAFE_LPCWSTR FormatText, char *Var)
{
	LPTSTR cDisplayPrompt;
	HRESULT hResult;
	size_t iDisplayPromptLen = lstrlen(FormatText) + strlen(Var) + 1;

	cDisplayPrompt = calloc(iDisplayPromptLen, sizeof (LPCWSTR));
	hResult = StringCchPrintf(cDisplayPrompt, iDisplayPromptLen, FormatText, Var);

	if(cDisplayPrompt != NULL && hResult == S_OK)
	{
		MessageBox(NULL, cDisplayPrompt, TEXT("Error"), MB_ICONERROR | MB_OK | MB_TOPMOST);
	}
	else
	{
		MessageBox(NULL, TEXT("Unable to create error box"), TEXT("Error"), MB_ICONERROR | MB_OK | MB_TOPMOST);
	}

	free(cDisplayPrompt);

}
void NumBox(STRSAFE_LPCWSTR FormatText, int Var)
{
	LPTSTR cDisplayPrompt;
	HRESULT hResult;
	size_t iDisplayPromptLen = lstrlen(FormatText) + 9;

	cDisplayPrompt = calloc(iDisplayPromptLen, sizeof (LPCWSTR));
	hResult = StringCchPrintf(cDisplayPrompt, iDisplayPromptLen, FormatText, Var);

	if(cDisplayPrompt != NULL && hResult == S_OK)
	{
		MessageBox(NULL, cDisplayPrompt, TEXT("Information"), MB_ICONINFORMATION | MB_OK | MB_TOPMOST);
	}
	else
	{
		MessageBox(NULL, TEXT("Unable to number box"), TEXT("Error"), MB_ICONERROR | MB_OK | MB_TOPMOST);
	}

	free(cDisplayPrompt);

}
