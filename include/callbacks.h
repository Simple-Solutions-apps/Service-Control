//file containing all callback procedures prototypes

//standard includes
#include <windows.h>

//conditional header guard wrapper to avoid proccesing more than once
#ifndef CALLBACKS_H
	#define CALLBACKS_H

	LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
	BOOL CALLBACK AboutDlgProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam);
	BOOL CALLBACK ToolDlgProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam);
	BOOL CALLBACK AuthDlgProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam);	

//end wrapper
#endif