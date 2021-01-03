#pragma once
#include "ThemeData.h"
#include "Gdipbutton.h"
#include "CustomScroll.h"
#include "DragDialog.h"
#include <vector>

// SortButtonList 대화 상자
class SortIcon;

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
	std::vector<CGdipButton*> sortButtonVector;

	CGdipButton* downButton;

	int nButtonID;
	int nEmptyDrawLineID;

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

	bool bTopOverDetect;
	bool bLeftOverDetect;
	bool bBottomOverDetect;
	bool bRightOverDetect;

	SortIcon* sorticon;

	bool bSortButtonHoverEvent;

	void LoadSortButton(std::vector<std::vector<int>> ctlVector);
	void CreateDragButton(CGdipButton* currentClickButton);
	BOOL DragActivation(POINT mousePoint);
	void HoverSignal(bool bSignal, bool* bSignalItem);


	ThemeData::FunctionIcon GetFunctionIconByButtonID(int nButtonID);
	CString GetButtonNameByButtonID(int nButtonID);
	void DrawEmptyLine();
	void DeleteEmptyLine();
	void ButtonBringToTop();
	bool ExistButtonPos(int nButtonIndex);

public:

	DragDialog* dragDlg;
	bool bDragActivation;
	int nLineEndCount;

	CustomScroll scroll;
	std::vector<CGdipButton*> iconMoveButtonVector;
	std::vector<std::vector<int>> ctlVector;
	std::vector<std::vector<int>> saveCtlVector;

	void EnableEmptyLine(int bShow);

	CRect SetButtonPosition(int nItemCount);
	bool InsertNewButton(int nButtonVectorIndex, int nStdID, int nHovID, int nAltID, CString strButtonName);
	int ButtonLocationToPos(POINT pt);

	virtual BOOL OnInitDialog();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
