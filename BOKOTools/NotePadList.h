#pragma once
#include "CustomScroll.h"
#include "DragWrapper.h"
#include "FolderItem.h"
#include <algorithm>

// NotePadList 대화 상자
class NotePad;
class FolderList;

class NotePadList : public CDialogEx, public DragWrapper<NoteItem*>
{
	DECLARE_DYNAMIC(NotePadList)

	friend class FolderList;

public:
	NotePadList(ThemeData* currentTheme, CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~NotePadList();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_NOTEPAD_LIST };
#endif

private:

	typedef std::vector<NoteItem*> ViewNoteList;

	ThemeData* currentTheme;
	CWnd* pParent;
	NotePad* notepad;

	enum NoteClickState
	{
		NOTE_CLICK_STATE_NONE	= 0,
		NOTE_CLICK_STATE_WRAP	= 1,
		NOTE_CLICK_STATE_TAG	= 2,
		NOTE_CLICK_STATE_NOTE	= 3
	};

	enum NoteDragPosState
	{
		NOTE_POS_STATE_NONE			= 0,
		NOTE_POS_STATE_HALF_UP		= 1,
		NOTE_POS_STATE_HALF_DOWN	= 2
	};

	std::vector<ViewNoteList> viewNoteList;

	CustomScroll scroll;

	const int nButtonCount_X = 4;

	int nButtonID;
	int nStaticID;
	int nLockID;
	int nButtonCount;
	int nLineEndCount;
	int nLineCount;

	int nEventPos;
	NoteClickState noteClickState;
	NoteDragPosState notePosState;

	CRect SetButtonPosition(int nItemCount);
	void ViewNote(ViewNoteList notelist);
	int ButtonLocationToPos(POINT pt);
	bool InsertNewButton(int nButtonVectorIndex, int nStdID, int nHovID, int nAltID, CString strButtonName);

	NoteItem* FindNoteButton(HWND clickWND);
	BOOL DetectionPtInRect(const RECT* lprc, POINT pt);

	virtual BOOL DragEventUp(HWND upHWND, CPoint upPoint, NoteItem* findnote = nullptr);
	virtual BOOL DragEventDown(HWND downHWND, CPoint downPoint, NoteItem* findnote = nullptr);
	virtual BOOL DragEventMove(HWND moveHWND, CPoint movePoint, NoteItem* findnote = nullptr);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:

	void LoadNotePad(std::vector<ViewNoteList> allFolderList);
	void AddNotePad(CString strContent, bool isLock);
	void UpdateNotePad(NoteItem* updateNote, CString strContent, bool isLock);
	bool OpenNoteDlg(int nNoteMode, CString* strNoteContent, bool* isLock);

	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual void OnOK();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
};
