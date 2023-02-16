//File containing control related definitions and function prototypes

#include <windows.h>

//conditional header guard wrapper to avoid processing more than once
#ifndef CONTROLLS_H
	#define CONTROLLS_H

	//Controls

	//tooltips
	#define IDC_MAIN_TIPACC 1001
	#define IDC_MAIN_TIPINTERACTIVE 1002
	//tool bar
	#define IDC_MAIN_TOOLBAR 1003
	#define TB_BTN_COUNT 7
	#define TB_BTN_BITMAP_H 24
	#define TB_BTN_BITMAP_W 120

	//Toolbar buttons
	#define IDC_BTN_TBCLEAR 1004
	#define IDC_BTN_TBTEXT 1005
	#define IDC_BTN_TBBAT 1006
	#define IDC_BTN_TBSVC 1007
	#define IDC_BTN_TBABOUT 1008

	//group boxes
	#define IDC_GRPBOX_PARAMS 1009
	#define IDC_GRPBOX_CMDLINE 1010
	#define IDC_GRPBOX_RESULT 1011

	//labels
	#define IDC_LABEL_COMMAND 1012
	#define IDC_LABEL_SVRNAME 1013
	#define IDC_LABEL_SVCNAME 1014
	#define IDC_LABEL_TYPE 1015
	#define IDC_LABEL_INTERACT 1016
	#define IDC_LABEL_START 1017
	#define IDC_LABEL_ERROR 1018
	#define IDC_LABEL_PATHBIN 1019
	#define IDC_LABEL_GROUP 1020
	#define IDC_LABEL_TAG 1021
	#define IDC_LABEL_DEPEND 1022
	#define IDC_LABEL_ACCNAME 1023
	#define IDC_LABEL_OBJNAME 1024
	#define IDC_LABEL_DISPNAME 1025
	#define IDC_LABEL_PW 1026
	#define IDC_LABEL_CMDLINE 1027
	#define IDC_LABEL_QYTYPE 1028
	#define IDC_LABEL_STATE 1029
	#define IDC_LABEL_BUFF 1030
	#define IDC_LABEL_RESUME 1031

	//buttons
	#define IDC_BTN_BROWSE 1032
	#define IDC_BTN_RUN 1033

	//combo boxes
	#define IDC_COMBO_COMMAND 1034
	#define IDC_COMBO_TYPE 1035
	#define IDC_COMBO_INTERACT 1036
	#define IDC_COMBO_START 1037
	#define IDC_COMBO_ERROR 1038
	#define IDC_COMBO_TAG 1039
	#define IDC_COMBO_QYTYPE 1040
	#define IDC_COMBO_STATE 1041

	//edit boxes
	#define IDC_EDIT_SVRNAME 1042
	#define IDC_EDIT_SVCNAME 1043
	#define IDC_EDIT_PATHBIN 1044
	#define IDC_EDIT_GROUP 1045
	#define IDC_EDIT_DEPEND 1046
	#define IDC_EDIT_ACCNAME 1047
	#define IDC_EDIT_OBJNAME 1048
	#define IDC_EDIT_DISPNAME 1049
	#define IDC_EDIT_PW 1050
	#define IDC_EDIT_DESC 1051
	#define IDC_EDIT_CMDLINE 1052
	#define IDC_EDIT_RSLT 1053
	#define IDC_EDIT_BUFF 1054
	#define IDC_EDIT_RESUME 1055
	#define IDC_EDIT_REQ 1056

	#define EDIT_MAX_CHARACTERS 64000

	//prototypes/functions
	int CreateControls(HWND sHdlWinMain);

//end of wrapper
#endif