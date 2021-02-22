#pragma once
#include "ThemeData.h"
#include "GdipButton.h"
#include "CalculateButton.h"
#pragma warning(disable : 4819)
#include "Resource.h"

class NoteItem
{

public:

	NoteItem();
	NoteItem(ThemeData* currentTheme, CWnd* pParent);
	~NoteItem();

	struct NoteInit
	{
		COLORREF tagColor = RGB(0, 0, 0);
		CString strNoteContent = _T("");
		CTime createTime;
		CTime updateTime;
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
	void SetNoteTagSequence(int nNoteSequnece);
	void SetNoteTagSequence(CString strNoteSequnece);
	void SetCreateTime(CTime createTime);
	void SetUpdateTime(CTime updateTime);

	bool IsLock();
	int GetFolderSize();
	int GetFolderSequence();
	COLORREF GetTagColor();
	CString GetNoteTitle();
	CString GetNoteContent();
	CRect GetNoteRect();
	int GetNoteName();
	CString GetNoteTagSequence();
	CTime GetCreateTime();
	CTime GetUpdateTime();

	void Update(NoteInit init);

private:

	ThemeData* currentTheme;
	CWnd* pParent;

	CRect noteRect;
	COLORREF tagColor;
	CString strNoteTitle;
	CString strNoteContent;
	CTime createTime;
	CTime updateTime;
	int nNoteName;
	int nFolderSize;
	int nFolderSequence;
	bool isLock;

	void ExecuteNoteInitData(NoteInit init);

public:

	CGdipButton* lockButton;
	CalculateButton* noteButton;
	CalculateButton* tagButton;
	CalculateButton* wrapButton;

};

