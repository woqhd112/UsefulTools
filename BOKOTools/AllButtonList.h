#pragma once
#include "CustomScroll.h"
#include "DragWrapper.h"


// AllButtonList 대화 상자

class SortIcon;

class AllButtonList : public CDialogEx, public DragWrapper
{
	DECLARE_DYNAMIC(AllButtonList)

	friend class SortIcon;
	friend class SortButtonList;

	typedef std::vector<std::vector<int>> CtlVector;
	typedef std::vector<CGdipButton*> ButtonVector;
public:
	AllButtonList(CtlVector ctlVector, ThemeData* currentTheme, CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~AllButtonList();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_ALL };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()

private:


	CWnd* pParent;
	ThemeData* currentTheme;
	CGdipButton* downButton;

	CustomScroll scroll;

	int nButtonStackCount;
	int nButtonID;

	bool bLineEnd;
	
	/*bool bButtonHover;
	bool bHoverBase;
	bool bHoverEngineering;
	bool bStopWatch;
	bool bConverter;
	bool bDateCal;
	bool bWorkTimer;
	bool bNotePad;
	bool bBaseTimer;
	bool bWorldClock;
	bool bComingSoon1;
	bool bComingSoon2;
	bool bComingSoon3;*/

	SortIcon* sorticon;
	DragWrapper* dragWrap;

	bool bSortButtonHoverEvent;

	//void HoverSignal(bool bSignal, bool* bSignalItem);
	void CtlToTop();
	void CreateExitButton(int nButtonID);


	bool bScrollButtonDetect;

	CtlVector ctlVector;
	ButtonVector allButtonVector;
	//DragDialog* dragDlg;

	void LoadAllButton();
	void DeleteAllButton();

	virtual BOOL DragEventUp(HWND upHWND, CPoint upPoint);
	virtual BOOL DragEventDown(HWND downHWND, CPoint downPoint);
	virtual BOOL DragEventMove(HWND moveHWND, CPoint movePoint);

public:


	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	virtual BOOL OnInitDialog();
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
};
