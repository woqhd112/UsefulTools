#pragma once
#include "atlstr.h"

class NoteFile
{
public:
	NoteFile();
	~NoteFile();

	enum NoteRenameMode
	{
		DEFAULT_NOTE = 0,			// 노트 -> 노트 이름변경 포맷 
		NOTE_BY_SINGLE_RECYCLE_NOTE = 1,	// 노트 -> 쓰레기통 싱글노트 이름변경 포맷
		NOTE_BY_MULTI_RECYCLE_NOTE = 2,	// 노트 -> 쓰레기통 멀티노트 이름변경 포맷
		RECYCLE_BY_SINGLE_RECYCLE_NOTE = 3,	// 쓰레기통 싱글노트 -> 노트 이름변경 포맷
		RECYCLE_BY_MULTI_RECYCLE_NOTE = 4, // 쓰레기통 멀티노트 -> 노트 이름변경 포맷
		DEFAULT_SINGLE_RECYCLE = 5,	// 쓰레기통 싱글노트 -> 쓰레기통 싱글노트 이름변경 포맷
		DEFAULT_MULTI_RECYCLE = 6, // 쓰레기통 멀티노트 -> 쓰레기통 멀티노트 이름변경 포맷
	};

	bool NoteRead(CString strPath, CString& strBuffer);
	bool NoteWrite(CString strPath, CString strContent);
	void NoteRename(CString strSystemPath, NoteRenameMode mode, int nOldFolderSequence, int nOldNoteName, int nNewFolderSequence, int nNewNoteName);

private:

	char* UTF8toANSI(char *pszCode);
	void GetFileFormat(NoteRenameMode mode, CString& strUpdateFileFormat, CString& strOldFileFormat);

};

