#pragma once
#include "CustomScroll.h"
#include "DragWrapper.h"
#include "FolderItem.h"

// NotePadList 대화 상자
class NotePad;
class FolderList;

class NotePadList : public CDialogEx, public DragWrapper
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

	ViewNoteList viewNoteList;
	std::vector<ViewNoteList> allFolderList;

	CustomScroll scroll;

	const int nButtonCount_X = 4;

	int nButtonID;
	int nStaticID;
	int nLockID;
	int nButtonCount;
	int nLineEndCount;
	int nLineCount;

	CRect SetButtonPosition(int nItemCount);
	void ViewNote(ViewNoteList notelist);
	int ButtonLocationToPos(POINT pt);
	bool InsertNewButton(int nButtonVectorIndex, int nStdID, int nHovID, int nAltID, CString strButtonName);


	virtual BOOL DragEventUp(HWND upHWND, CPoint upPoint);
	virtual BOOL DragEventDown(HWND downHWND, CPoint downPoint);
	virtual BOOL DragEventMove(HWND moveHWND, CPoint movePoint);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:

	void LoadNotePad(std::vector<ViewNoteList> allFolderList);
	void AddNotePad(CString strTitle, CString strContent);

	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual void OnOK();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
};
