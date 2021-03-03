#pragma once
#include "atlstr.h"

class NoteFile
{
public:
	NoteFile();
	~NoteFile();

	enum NoteRenameMode
	{
		DEFAULT_NOTE = 0,			// ��Ʈ -> ��Ʈ �̸����� ���� 
		NOTE_BY_SINGLE_RECYCLE_NOTE = 1,	// ��Ʈ -> �������� �̱۳�Ʈ �̸����� ����
		NOTE_BY_MULTI_RECYCLE_NOTE = 2,	// ��Ʈ -> �������� ��Ƽ��Ʈ �̸����� ����
		RECYCLE_BY_SINGLE_RECYCLE_NOTE = 3,	// �������� �̱۳�Ʈ -> ��Ʈ �̸����� ����
		RECYCLE_BY_MULTI_RECYCLE_NOTE = 4, // �������� ��Ƽ��Ʈ -> ��Ʈ �̸����� ����
		DEFAULT_SINGLE_RECYCLE = 5,	// �������� �̱۳�Ʈ -> �������� �̱۳�Ʈ �̸����� ����
		DEFAULT_MULTI_RECYCLE = 6, // �������� ��Ƽ��Ʈ -> �������� ��Ƽ��Ʈ �̸����� ����
	};

	bool NoteRead(CString strPath, CString& strBuffer);
	bool NoteWrite(CString strPath, CString strContent);
	void NoteRename(CString strSystemPath, NoteRenameMode mode, int nOldFolderSequence, int nOldNoteName, int nNewFolderSequence, int nNewNoteName);

private:

	char* UTF8toANSI(char *pszCode);
	void GetFileFormat(NoteRenameMode mode, CString& strUpdateFileFormat, CString& strOldFileFormat);

};

