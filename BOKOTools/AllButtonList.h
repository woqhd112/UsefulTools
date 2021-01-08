#pragma once
#include "CustomScroll.h"
#include "DragDialog.h"


// AllButtonList 대화 상자

class SortIcon;

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
	CGdipButton* downButton;

	CustomScroll scroll;

	int nButtonStackCount;
	int nButtonID;

	bool bLineEnd;
	
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

	SortIcon* sorticon;
	
	bool bTopOverDetect;
	bool bLeftOverDetect;
	bool bBottomOverDetect;
	bool bRightOverDetect;

	bool bSortButtonHoverEvent;

	void HoverSignal(bool bSignal, bool* bSignalItem);
	void CtlToTop();
	void CreateExitButton(int nButtonID);
	ThemeData::FunctionIcon GetFunctionIconByButtonID(int nButtonID);
	CString GetButtonNameByButtonID(int nButtonID);


	void CreateDragButton(CGdipButton* currentClickButton);
	BOOL DragActivation(POINT mousePoint);


	bool bScrollButtonDetect;
	/*bool bScrollThread;
	int nScrollButtonDetectCount;
	CWinThread* m_scrollThread;
	static UINT thrScrollDetect(LPVOID method);
	void StartScrollThread();*/


public:

	std::vector<std::vector<int>> ctlVector;
	std::vector<CGdipButton*> allButtonVector;
	DragDialog* dragDlg;
	bool bDragActivation;

	void LoadAllButton();
	void DeleteAllButton();

	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	virtual BOOL OnInitDialog();
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
};
