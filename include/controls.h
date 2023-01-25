//File containing control related definitions and function prototypes

//conditional header guard wrapper to avoid processing more than once
#ifndef CONTROLLS_H
	#define CONTROLLS_H

	//Controls

	//tooltips
	#define IDC_MAIN_TIPACC 1051
	#define IDC_MAIN_TIPINTERACTIVE 1053

	//tool bar
	#define IDC_MAIN_TOOLBAR 1100
	#define TB_BTN_COUNT 7
	#define TB_BTN_BITMAP_H 24
	#define TB_BTN_BITMAP_W 120

	//Toolbar buttons
	#define IDC_BTN_TBCLEAR 1052
	#define IDC_BTN_TBTEXT 1054
	#define IDC_BTN_TBBAT 1055
	#define IDC_BTN_TBSVC 1056
	#define IDC_BTN_TBABOUT 1057

	//group boxes
	#define IDC_GRPBOX_PARAMS 1036
	#define IDC_GRPBOX_CMDLINE 1037

	//labels
	#define IDC_LABEL_COMMAND 1001
	#define IDC_LABEL_SVRNAME 1002
	#define IDC_LABEL_SVCNAME 1003
	#define IDC_LABEL_TYPE 1004
	#define IDC_LABEL_INTERACT 1005
	#define IDC_LABEL_START 1006
	#define IDC_LABEL_ERROR 1007
	#define IDC_LABEL_PATHBIN 1008
	#define IDC_LABEL_GROUP 1009
	#define IDC_LABEL_TAG 1010
	#define IDC_LABEL_DEPEND 1011
	#define IDC_LABEL_ACCNAME 1012
	#define IDC_LABEL_OBJNAME 1013
	#define IDC_LABEL_DISPNAME 1014
	#define IDC_LABEL_PW 1015
	#define IDC_LABEL_CMDLINE 1038
	#define IDC_LABEL_QYTYPE 1042
	#define IDC_LABEL_STATE 1043
	#define IDC_LABEL_BUFF 1044
	#define IDC_LABEL_RESUME 1045

	//buttons
	#define IDC_BTN_BROWSE 1016
	#define IDC_BTN_RUN 1058

	//combo boxes
	#define IDC_COMBO_COMMAND 1017
	#define IDC_COMBO_TYPE 1018
	#define IDC_COMBO_INTERACT 1019
	#define IDC_COMBO_START 1020
	#define IDC_COMBO_ERROR 1021
	#define IDC_COMBO_TAG 1022
	#define IDC_COMBO_QYTYPE 1046
	#define IDC_COMBO_STATE 1047

	//edit boxes
	#define IDC_EDIT_SVRNAME 1023
	#define IDC_EDIT_SVCNAME 1024
	#define IDC_EDIT_PATHBIN 1025
	#define IDC_EDIT_GROUP 1026
	#define IDC_EDIT_DEPEND 1027
	#define IDC_EDIT_ACCNAME 1028
	#define IDC_EDIT_OBJNAME 1029
	#define IDC_EDIT_DISPNAME 1030
	#define IDC_EDIT_PW 1031
	#define IDC_EDIT_DESC 1041
	#define IDC_EDIT_CMDLINE 1039
	#define IDC_EDIT_RSLT 1040
	#define IDC_EDIT_BUFF 1048
	#define IDC_EDIT_RESUME 1049
	#define IDC_EDIT_REQ 1050

	//prototypes/functions
	int CreateControls(HWND sHdlWinMain);

//end of wrapper
#endif