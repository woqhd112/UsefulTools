#include "pch.h"
#include "NoteFile.h"


NoteFile::NoteFile()
{

}

NoteFile::~NoteFile()
{

}

bool NoteFile::NoteRead(CString strPath, CString& strBuffer)
{
	bool bReturn = false;
	CFile noteFile;
	if (noteFile.Open(strPath, CFile::modeReadWrite))
	{
		try
		{
			int dwCount = 0;
			do
			{
				char pbufWrite[1000] = { 0, };
				dwCount = noteFile.Read(pbufWrite, sizeof(pbufWrite));
				strBuffer.Append((CString)UTF8toANSI(pbufWrite), dwCount);
			} while (dwCount > 0);
			noteFile.Close();
			bReturn = true;
		}
		catch (CFileException*)
		{
			AfxMessageBox(_T("Not Found File"));
		}
	}
	return bReturn;
}

bool NoteFile::NoteWrite(CString strPath, CString strContent)
{
	bool bReturn = false;
	CFile createFile;
	if (createFile.Open(strPath, CFile::modeCreate | CFile::modeWrite))
	{
		try
		{
			CT2CA outputString(strContent, CP_UTF8);
			createFile.Write(outputString, ::strlen(outputString));
			createFile.Close();
			bReturn = true;
		}
		catch (CFileException*)
		{
			AfxMessageBox(_T("Invalid File Name"));
		}
	}
	return bReturn;
}

char* NoteFile::UTF8toANSI(char *pszCode)
{
	BSTR    bstrWide;
	char*   pszAnsi;
	int		nLength;

	// Get nLength of the Wide Char buffer   
	nLength = MultiByteToWideChar(CP_UTF8, 0, pszCode, (int)strlen(pszCode) + 1, NULL, NULL);
	bstrWide = SysAllocStringLen(NULL, nLength);

	// Change UTF-8 to Unicode (UTF-16)   
	MultiByteToWideChar(CP_UTF8, 0, pszCode, (int)strlen(pszCode) + 1, bstrWide, nLength);


	// Get nLength of the multi byte buffer    
	nLength = WideCharToMultiByte(CP_ACP, 0, bstrWide, -1, NULL, 0, NULL, NULL);
	pszAnsi = new char[nLength];


	// Change from unicode to mult byte   
	WideCharToMultiByte(CP_ACP, 0, bstrWide, -1, pszAnsi, nLength, NULL, NULL);

	SysFreeString(bstrWide);


	return pszAnsi;
}
