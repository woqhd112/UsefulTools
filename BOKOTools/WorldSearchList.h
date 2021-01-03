#pragma once
#include "ThemeData.h"
#include "GeneralUtil.h"

// WorldSearchList 대화 상자

class WorldSearchList : public CDialogEx
{
	DECLARE_DYNAMIC(WorldSearchList)

public:
	WorldSearchList(ThemeData* currentTheme, CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~WorldSearchList();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_SEARCH_LIST };
#endif

private:

	ThemeData* currentTheme;
	CWnd* pParent;

	int nBrightness;
	COLORREF bkBorderColor;

	void LoadWorldClockList();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:

	void SearchClockListFromInputText(CString strInputText);

	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnPaint();
};
