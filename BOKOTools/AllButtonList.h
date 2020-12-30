#pragma once
#include "ThemeData.h"
#include "Gdipbutton.h"
#include "CustomScroll.h"
#include "DragDialog.h"
#include <vector>


// AllButtonList 대화 상자

class AllButtonList : public CDialogEx
{
	DECLARE_DYNAMIC(AllButtonList)

public:
	AllButtonList(std::vector<std::vector<int>> ctlVector, ThemeData* currentTheme, CWnd* pParent = nullptr);   // 표준 생성자입니다.
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
	std::vector<std::vector<int>> ctlVector;
	std::vector<CGdipButton*> allButtonVector;

	CustomScroll scroll;

	int nButtonStackCount;
	int nButtonID;
	
	bool bButtonHover;
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

	void LoadAllButton();
	void StackCountCondition();
	void HoverSignal(bool bSignal, bool* bSignalItem);
	void CtlToTop();
	void CreateExitButton(int nButtonID);
	ThemeData::FunctionIcon GetFunctionIconByButtonID(int nButtonID);
	CString AllButtonList::GetButtonNameByButtonID(int nButtonID);

public:

	//CGdipButton* hoverButton;
	DragDialog* dragDlg;

	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	virtual BOOL OnInitDialog();
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
