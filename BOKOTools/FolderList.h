#pragma once
#include "CustomScroll.h"
#include "DragWrapper.h"


// FolderList 대화 상자

class NotePad;
class NotePadList;

class FolderList : public CDialogEx, public DragWrapper
{
	DECLARE_DYNAMIC(FolderList)

	friend class NotePadList;

public:
	FolderList(ThemeData* currentTheme, CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~FolderList();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_FOLDER_LIST };
#endif

public:


private:

	typedef std::vector<FolderItem0*> ViewFolderList;

	ThemeData* currentTheme;
	CWnd* pParent;
	NotePad* notepad;

	int nButtonCount;
	int nLineEndCount;
	ViewFolderList folderlist;
	FolderItem0* downFolder;
	FolderItem0* undoFolder;

	CustomScroll scroll;

	void ViewFolder(ViewFolderList folderlist);
	CRect SetButtonPosition(int nItemCount);

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
