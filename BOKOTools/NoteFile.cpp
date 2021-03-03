#include "pch.h"
#include "NoteFile.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

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
				char* utfFormat = UTF8toANSI(pbufWrite);
				strBuffer.Append((CString)utfFormat, dwCount);
				delete[] utfFormat;
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
			createFile.Write(outputString, (UINT)::strlen(outputString));
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

void NoteFile::GetFileFormat(NoteRenameMode mode, CString& strUpdateFileFormat, CString& strOldFileFormat)
{
	switch (mode)
	{
	case DEFAULT_NOTE:
		strUpdateFileFormat = _T("%d%d.txt");
		strOldFileFormat = _T("%d%d.txt");
		break;
	case NOTE_BY_SINGLE_RECYCLE_NOTE:
		strUpdateFileFormat = _T("sr%d%d.txt");
		strOldFileFormat = _T("%d%d.txt");
		break;
	case NOTE_BY_MULTI_RECYCLE_NOTE:
		strUpdateFileFormat = _T("r%d%d.txt");
		strOldFileFormat = _T("%d%d.txt");
		break;
	case RECYCLE_BY_SINGLE_RECYCLE_NOTE:
		strUpdateFileFormat = _T("%d%d.txt");
		strOldFileFormat = _T("sr%d%d.txt");
		break;
	case RECYCLE_BY_MULTI_RECYCLE_NOTE:
		strUpdateFileFormat = _T("%d%d.txt");
		strOldFileFormat = _T("r%d%d.txt");
		break;
	case DEFAULT_SINGLE_RECYCLE:
		strUpdateFileFormat = _T("sr%d%d.txt");
		strOldFileFormat = _T("sr%d%d.txt");
		break;
	case DEFAULT_MULTI_RECYCLE:
		strUpdateFileFormat = _T("r%d%d.txt");
		strOldFileFormat = _T("r%d%d.txt");
		break;
	default:
		break;
	}
}

void NoteFile::NoteRename(CString strSystemPath, NoteRenameMode mode, int nOldFolderSequence, int nOldNoteName, int nNewFolderSequence, int nNewNoteName)
{
	CString strUpdateFileFormat, strOldFileFormat;
	GetFileFormat(mode, strUpdateFileFormat, strOldFileFormat);
	
	CString strFolderOriginFileName, strFolderUpdateFileName;
	strFolderOriginFileName.Format(strOldFileFormat, nOldFolderSequence, nOldNoteName);
	strFolderUpdateFileName.Format(strUpdateFileFormat, nNewFolderSequence, nNewNoteName);

	if (strFolderOriginFileName.Compare(strFolderUpdateFileName) == 0) return;

	CFileFind find;

	BOOL bFind = find.FindFile(strSystemPath + _T("*.txt"));
	while (bFind)
	{
		bFind = find.FindNextFileW();
		if (find.IsDots()) continue;
		if (!find.IsDirectory())
		{
			CString strFindFileName = find.GetFileName();
			if (strFindFileName.Compare(strFolderUpdateFileName) == 0)	// 같을경우
			{
				strFolderUpdateFileName.Format(strUpdateFileFormat, nNewFolderSequence, ++nNewNoteName);
			}
		}
	}
	find.Close();

	CFile::Rename(strSystemPath + strFolderOriginFileName, strSystemPath + strFolderUpdateFileName);
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
