#pragma once
#include "NoteItem.h"
#include "CalculateStatic.h"
#include <vector>

class FolderItem0
{

public:

	FolderItem0(ThemeData* currentTheme, CWnd* pParent);
	~FolderItem0();

	typedef std::vector<NoteItem*> Folder, ViewNoteList;

	struct FolderInit
	{
		Folder folder;
		CTime createTime;
		CTime updateTime;
		CString strFolderName;
		int nFolderColorIndex;
		int nFolderSize;
		int nFolderSequence;
	};

	void Initialize(FolderInit init);
	void MoveWindow(int nLeft, int nTop);
	void ShowWindow(bool isShow);

	void SetFolderName(CString strFolderName);
	void SetFolderSize(int nFolderSize);
	void SetFolderSequence(int nFolderSequence);
	void SetFolderColorIndex(int nFolderColorIndex);
	void SetFolder(FolderItem0::Folder folder);
	void SetCreateTime(CTime createTime);
	void SetUpdateTime(CTime updateTime);

	CString GetFolderName();
	int GetFolderSize();
	int GetFolderSequence();
	int GetFolderColorIndex();
	CRect GetFolderRect();
	FolderItem0::Folder GetFolder();
	CTime GetCreateTime();
	CTime GetUpdateTime();

	void Update(FolderInit init);
	void FolderImageInit(int nFolderColorIndex, int nFolderSize);

private:

	ThemeData* currentTheme;
	CWnd* pParent;

	CString strFolderName;
	int nFolderSize;
	int nFolderSequence;
	int nFolderColorIndex;
	CTime createTime;
	CTime updateTime;
	CRect folderRect;

	FolderItem0::Folder folder;

	void ExecuteFolderInitData(FolderInit init);

public:

	CGdipButton* folderButton;
	CalculateStatic* folderStatic;

};

