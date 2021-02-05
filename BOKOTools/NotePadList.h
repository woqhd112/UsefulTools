#pragma once
#include "CustomScroll.h"
#include "DragWrapper.h"
#include "CustomXml.h"
#include "CalculateStatic.h"
#include "NoteFile.h"

// NotePadList 대화 상자
class NotePad;

class NotePadList : public CDialogEx, public DragWrapper
{
	DECLARE_DYNAMIC(NotePadList)

public:
	NotePadList(ThemeData* currentTheme, CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~NotePadList();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_NOTEPAD_LIST };
#endif

private:
	typedef std::vector<CString> NoteVector;
	typedef std::vector<NoteVector> NoteList;
	typedef std::vector<CGdipButton*> NoteButtonList;
	typedef std::vector<CalculateStatic*> NoteTitleList;
	typedef std::vector<CGdipButton*> LockButtonList;

	ThemeData* currentTheme;
	CWnd* pParent;
	NotePad* notepad;
	NoteList notelist;
	NoteButtonList notebuttonlist;
	NoteTitleList notetitlelist;
	LockButtonList lockbuttonlist;

	CGdipButton* trashButton;
	CGdipButton* downButton;
	CustomScroll scroll;

	const int nButtonCount_X = 4;

	int nButtonID;
	int nStaticID;
	int nLockID;
	int nButtonCount;
	int nLineEndCount;
	int nLineCount;

	bool CreateDefaultNoteXml(CMarkup* markUp, CString strFullPath);
	void SaveNoteXml(int nIndex, bool bLocked);
	CRect SetButtonPosition(int nItemCount);
	void InsertNewNote(bool isFolder, CString strFolderName, CString strNoteTitle, bool bLocked);
	void ShowButtonCtl(bool bShow, int nStart, int nEnd);
	int ButtonLocationToPos(POINT pt);
	bool InsertNewButton(int nButtonVectorIndex, int nStdID, int nHovID, int nAltID, CString strButtonName);


	virtual BOOL DragEventUp(HWND upHWND, CPoint upPoint);
	virtual BOOL DragEventDown(HWND downHWND, CPoint downPoint);
	virtual BOOL DragEventMove(HWND moveHWND, CPoint movePoint);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:

	void LoadNotePad();
	void AddNotePad(CString strTitle, CString strContent);

	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual void OnOK();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
};
