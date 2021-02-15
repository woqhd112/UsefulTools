#pragma once
#include "ThemeData.h"
#include "GdipButton.h"
#include "CalculateButton.h"
#pragma warning(disable : 4819)
#include "Resource.h"

class NoteItem
{

public:

	NoteItem(ThemeData* currentTheme, CWnd* pParent);
	~NoteItem();

	struct NoteInit
	{
		COLORREF tagColor = RGB(0, 0, 0);
		CString strNoteContent = _T("");
		int nNoteName = 0;
		int nFolderSize = 0;
		int nFolderSequence = 0;
		bool isLock = false;
	};

	void Initialize(NoteInit init);
	void MoveWindow(int nLeft, int nTop);
	void ShowWindow(bool isShow);
	void ShowLock(bool isShow);

	void SetNoteContent(CString strNoteContent);
	void SetTagColor(COLORREF tagColor);
	void SetFolderSize(int FolderSize);
	void SetLockSetting(bool isLock);
	void SetFolderSequence(int nFolderSequence);
	void SetNoteName(int nNoteName);

	bool IsLock();
	int GetFolderSize();
	int GetFolderSequence();
	COLORREF GetTagColor();
	CString GetNoteTitle();
	CString GetNoteContent();
	CRect GetNoteRect();
	bool IsCreating();
	int GetNoteName();

	void Update(NoteInit init);

private:

	ThemeData* currentTheme;
	CWnd* pParent;

	CRect noteRect;
	COLORREF tagColor;
	CString strNoteTitle;
	CString strNoteContent;
	int nNoteName;
	int nFolderSize;
	int nFolderSequence;
	bool isLock;
	bool isCreating;

	void ExecuteNoteInitData(NoteInit init);

public:

	CGdipButton* lockButton;
	CalculateButton* noteButton;
	CalculateButton* tagButton;
	CalculateButton* wrapButton;

};

