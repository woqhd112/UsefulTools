﻿#pragma once
#include "CalculateEdit.h"
#include "WorldClockList.h"
#include "WorldSearchList.h"
#include "AnalogWatch.h"

// WorldClock 대화 상자

class WorldClock : public CDialogEx
{
	DECLARE_DYNAMIC(WorldClock)

public:
	WorldClock(ThemeData* currentTheme, CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~WorldClock();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_WORLD_CLOCK };
#endif

private:

	CWnd* pParent;
	ThemeData* currentTheme;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()

private:

	CalculateButton m_btn_search;
	CalculateEdit m_edit_search;
	CalculateStatic m_stt_result_view;

	CBrush m_backBrush;
	CRect dynamicSearchRect;

	AnalogWatch* analogwatch;
	std::vector<AnalogWatch*> subAnalogWatchVector;

	CWinThread* m_curtimeThread;
	bool bCurTimeThread;
	static UINT thrStartWorldClock(LPVOID method);
	void StartWorldClock();

	CString GetCurTime(double dErrorSubTimeValue);

public:

	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnClose();
	virtual void PostNcDestroy();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnEnChangeEditWorldSearch();
	afx_msg void OnBnClickedButtonWorldSearch();
};
