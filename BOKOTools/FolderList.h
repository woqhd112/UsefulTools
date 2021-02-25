#pragma once
#include "CustomScroll.h"
#include "DragWrapper.h"
#include "NotePadManager.h"
#include "FolderDlg.h"


// FolderList 대화 상자

class NotePad;
class NotePadList;

class FolderList : public CDialogEx, public DragWrapper<FolderItem0*>
{
	DECLARE_DYNAMIC(FolderList)

	friend class NotePadList;
	friend class NotePad;

public:
	FolderList(NotePadManager* notePadManager, ThemeData* currentTheme, CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~FolderList();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_FOLDER_LIST };
#endif

public:


private:

	//typedef std::vector<NoteItem*> ViewNoteList;
	//typedef std::vector<FolderItem0*> ViewFolderList;
	typedef NotePadContainer<NoteItem*> ViewNoteList;
	typedef NotePadContainer<FolderItem0*> ViewFolderList;

	ThemeData* currentTheme;
	CWnd* pParent;
	NotePad* notepad;
	NotePadManager* notePadManager;

	int nButtonCount;
	int nLineEndCount;
	//ViewFolderList folderlist;
	FolderItem0* downFolder;
	FolderItem0* undoFolder;

	CustomScroll scroll;

	void ViewFolder(ViewFolderList folderlist);
	int ButtonLocationToPos(POINT pt);
	int LocationAndScrollToFolderSequence(int nLocToPos);
	CRect SetButtonPosition(int nItemCount);
	void UpdateFolder(FolderItem0* folderItem);

	bool bThread;
	bool bPressMaintain;

	static UINT thrPressMaintainButton(LPVOID method);

	virtual BOOL DragEventUp(HWND upHWND, CPoint upPoint);
	virtual BOOL DragEventDown(HWND downHWND, CPoint downPoint);
	virtual BOOL DragEventMove(HWND moveHWND, CPoint movePoint);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:

	void LoadFolder(ViewFolderList allFolderList);
	void StartPressMaintainButton();

	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
protected:
	afx_msg LRESULT OnPressMaintain(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnFolderView(WPARAM wParam, LPARAM lParam);
};
