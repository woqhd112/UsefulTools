#pragma once
#include "atlstr.h"

class NoteFile
{
public:
	NoteFile();
	~NoteFile();

	bool NoteRead(CString strPath, CString& strBuffer);
	bool NoteWrite(CString strPath, CString strContent);

private:

	char* UTF8toANSI(char *pszCode);
};

