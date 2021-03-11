#pragma once
#include "CustomScroll.h"
#include "DragWrapper.h"
#include "NotePadManager.h"
//#include "FolderItem.h"
//#include <algorithm>

// NotePadList 대화 상자
class NotePad;
class FolderList;

class NotePadList : public CDialogEx, public DragWrapper<NoteItem*>
{
	DECLARE_DYNAMIC(NotePadList)

	friend class FolderList;
	friend class NotePad;

public:
	NotePadList(NotePadManager* notePadManager, ThemeData* currentTheme, CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~NotePadList();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_NOTEPAD_LIST };
#endif

private:

	//typedef std::vector<NoteItem*> ViewNoteList;
	//typedef std::vector<FolderItem0*> ViewFolderList;
	typedef NotePadContainer<NoteItem*> ViewNoteList;
	typedef NotePadContainer<FolderItem0*> ViewFolderList;

	ThemeData* currentTheme;
	CWnd* pParent;
	NotePad* notepad;
	NotePadManager* notePadManager;

	enum NoteClickState
	{
		NOTE_CLICK_STATE_NONE	= 0,
		NOTE_CLICK_STATE_WRAP	= 1,
		NOTE_CLICK_STATE_TAG	= 2,
		NOTE_CLICK_STATE_NOTE	= 3
	};

	enum NoteDragPosState
	{
		NOTE_POS_STATE_NONE			= 0,	// 아무상태 아닐때
		NOTE_POS_STATE_HALF_DETECT	= 1,	// 마우스가 아래로 내려갈때 버튼 위에 댔을때
	};

	enum DragSectorPos
	{
		DRAG_SECTOR_PARENT = 0,
		DRAG_SECTOR_NOTE = 1,
		DRAG_SECTOR_FOLDER = 2,
	};

	NotePadContainer<ViewNoteList> viewNoteList;

	CustomScroll scroll;

	const int nButtonCount_X = 4;

	int nButtonID;
	int nStaticID;
	int nLockID;
	int nButtonCount;
	int nLineEndCount;
	int nLineCount;

	int nEventPos;
	int nEventNoteSequence;
	NoteClickState noteClickState;
	NoteDragPosState notePosState;
	DragSectorPos dragSectorPos;


	int nFindSaveFolderSequence;
	ViewNoteList saveNoteList;

	CGdipButton* findFolderButton;
	int nSelectFolderSequence;
	bool bMousePointFolderAccess;


	CRect SetButtonPosition(int nItemCount, bool bScrollCalc = true);
	void ViewNote(ViewNoteList notelist);
	int LocationAndScrollToNoteSequence(int nLocToPos);
	int ButtonLocationToPos(POINT pt);
	void UpdateNoteVector(ViewNoteList updateNoteList, int nUpdateIndex);
	void SuccessUpdate();

	NoteItem* FindNoteButton(HWND clickWND);
	BOOL DetectionPtInRect(const RECT* targetRECT, const RECT* thisRECT, POINT pt);
	void SwapNoteTagSequence(int nEventPos, int nLocToPos, CString& strFindSortNoteTagSequence);

	virtual BOOL DragEventUp(HWND upHWND, CPoint upPoint, NoteItem* findnote = nullptr);
	virtual BOOL DragEventDown(HWND downHWND, CPoint downPoint, NoteItem* findnote = nullptr);
	virtual BOOL DragEventMove(HWND moveHWND, CPoint movePoint, NoteItem* findnote = nullptr);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:

	void LoadNotePad(NotePadContainer<ViewNoteList> allFolderList);
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
