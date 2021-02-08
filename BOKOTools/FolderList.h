#pragma once
#include "CustomScroll.h"
#include "DragWrapper.h"
#include "FolderItem.h"


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

	CustomScroll scroll;

	void ViewFolder(ViewFolderList folderlist);
	CRect SetButtonPosition(int nItemCount);

	virtual BOOL DragEventUp(HWND upHWND, CPoint upPoint);
	virtual BOOL DragEventDown(HWND downHWND, CPoint downPoint);
	virtual BOOL DragEventMove(HWND moveHWND, CPoint movePoint);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:

	void LoadFolder(ViewFolderList allFolderList);

	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
};
