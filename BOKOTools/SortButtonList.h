#pragma once
#include "ThemeData.h"
#include "Gdipbutton.h"
#include "CustomScroll.h"
#include <vector>

// SortButtonList 대화 상자

class SortButtonList : public CDialogEx
{
	DECLARE_DYNAMIC(SortButtonList)

public:
	SortButtonList(std::vector<std::vector<int>> ctlVector, ThemeData* currentTheme, CWnd* pParent = nullptr);   // 표준 생성자입니다.
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
	std::vector<std::vector<int>> ctlVector;
	std::vector<CGdipButton*> sortButtonVector;

	int nButtonID;
	CustomScroll scroll;

	void LoadSortButton();
	CRect SetButtonPosition(int nItemCount);

public:
	virtual BOOL OnInitDialog();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
};
