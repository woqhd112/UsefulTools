#pragma once
#include "NoteItem.h"
#include "FolderItem.h"
#include "CustomScroll.h"


// NotePadRecycle 대화 상자

class NotePad;
class NotePadRecycle : public CDialogEx
{
	DECLARE_DYNAMIC(NotePadRecycle)

public:

	//typedef std::vector<NoteItem*> ViewNoteList;
	//typedef std::vector<FolderItem0*> ViewFolderList;
	typedef NotePadContainer<NoteItem*> ViewNoteList;
	typedef NotePadContainer<FolderItem0*> ViewFolderList;

	NotePadRecycle(ThemeData* currentTheme, CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~NotePadRecycle();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_NOTEPAD_RECYCLE };
#endif

private:

	ThemeData* currentTheme;
	CWnd* pParent;
	NotePad* notepad;

	CustomScroll scroll;

	ViewNoteList recycleNoteList;
	ViewFolderList recycleFolderList;


public:

	int GetCurrentScrollLine();
	void SetCurrentScrollLine(int nScrollCount);
	void LoadRecycleData(ViewNoteList recycleNoteList, ViewFolderList recycleFolderList);
	void Init(ViewNoteList recycleNoteList, ViewFolderList recycleFolderList);

private:

	int nStartPos_x = 30;
	int nStartPos_y = 30;
	int nStartPos_Sumx = 30;
	int nStartPos_Sumy = 30;

	CRect SetNoteButtonPosition(int nNoteIndex);
	CRect SetFolderButtonPosition(int nFolderIndex);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnClose();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
};
