#pragma once
#include "ThemeData.h"
#include "GeneralUtil.h"


// WorldClockList 대화 상자

class WorldClock;

class WorldClockList : public CDialogEx
{
	DECLARE_DYNAMIC(WorldClockList)

public:
	WorldClockList(ThemeData* currentTheme, CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~WorldClockList();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_WORLD_LIST };
#endif

private:

	ThemeData* currentTheme;
	CWnd* pParent;

	WorldClock* worldclock;

	int nBrightness;
	COLORREF bkBorderColor;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnPaint();
};
