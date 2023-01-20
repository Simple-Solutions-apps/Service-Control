////File containing custom message boxes reladed definitions and function prototypes

#ifndef MSGBOXES_H
	#define MSGBOXES_H

	//prototypes
	void InfoBox(STRSAFE_LPCWSTR FormatText, char *var);
	void ErrorBox(STRSAFE_LPCWSTR FormatText, char *var);
	void NumBox(STRSAFE_LPCWSTR FormatText, int var);

#endif // MSGBOXES_H
