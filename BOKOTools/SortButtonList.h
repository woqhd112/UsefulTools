#pragma once
#include "CustomScroll.h"
#include "DragWrapper.h"

// SortButtonList 대화 상자
class SortIcon;

class SortButtonList : public CDialogEx, public DragWrapper
{
	DECLARE_DYNAMIC(SortButtonList)

	friend class SortIcon;
	friend class AllButtonList;

	typedef std::vector<std::vector<int>> CtlVector;
	typedef std::vector<CGdipButton*> ButtonVector;
public:
	SortButtonList(CtlVector, ThemeData* currentTheme, CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~SortButtonList();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_SORT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()

private:


	CWnd* pParent;
	ThemeData* currentTheme;
	ButtonVector sortButtonVector;

	DragWrapper* dragWrap;

	CGdipButton* downButton;

	int nButtonID;
	int nEmptyDrawLineID;

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
	bool bComingSoon3;
*/

	SortIcon* sorticon;

	bool bSortButtonHoverEvent;

	void LoadSortButton(CtlVector ctlVector);
	//void HoverSignal(bool bSignal, bool* bSignalItem);

	void DrawEmptyLine();
	void DeleteButonVector(ButtonVector& buttonVector);
	void ButtonBringToTop();
	bool ExistButtonPos(int nButtonIndex);

	int nLineEndCount;

	CustomScroll scroll;
	std::vector<CGdipButton*> iconMoveButtonVector;
	CtlVector ctlVector;
	CtlVector saveCtlVector;

	void EnableEmptyLine(int bShow);

	CRect SetButtonPosition(int nItemCount);
	bool InsertNewButton(int nButtonVectorIndex, int nStdID, int nHovID, int nAltID, CString strButtonName);
	int ButtonLocationToPos(POINT pt);



	virtual BOOL DragEventUp(HWND upHWND, CPoint upPoint);
	virtual BOOL DragEventDown(HWND downHWND, CPoint downPoint);
	virtual BOOL DragEventMove(HWND moveHWND, CPoint movePoint);

public:


	virtual BOOL OnInitDialog();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
