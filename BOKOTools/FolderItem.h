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

	CString GetFolderName();
	int GetFolderSize();
	int GetFolderSequence();
	int GetFolderColorIndex();
	CRect GetFolderRect();
	FolderItem0::Folder GetFolder();

	void Update(FolderInit init);

private:

	ThemeData* currentTheme;
	CWnd* pParent;

	CString strFolderName;
	int nFolderSize;
	int nFolderSequence;
	int nFolderColorIndex;
	CRect folderRect;

	FolderItem0::Folder folder;

	void FolderImageInit(int nFolderColorIndex, int nFolderSize);
	void ExecuteFolderInitData(FolderInit init);

public:

	CGdipButton* folderButton;
	CalculateStatic* folderStatic;

};

