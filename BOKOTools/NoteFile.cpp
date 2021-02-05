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
				strBuffer.Append((CString)pbufWrite, dwCount);
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
			CStringA uniContent = CStringA(strContent);
			createFile.Write(uniContent, uniContent.GetLength());
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

