#pragma once
#include "CalculateButton.h"
#include "CalculateStatic.h"
#include "LapTime.h"
#include "UsingManualDialog.h"

// Timer 대화 상자

class StopWatch : public CDialogEx
{
	DECLARE_DYNAMIC(StopWatch)

public:
	StopWatch(bool bUsingManual, ThemeData* currentTheme, CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~StopWatch();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_STOPWATCH };
#endif

private:

	CWnd* pParent;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
	virtual void OnOK();
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL OnInitDialog();
	virtual void PostNcDestroy();
	afx_msg void OnClose();

private:
	CalculateStatic m_stt_stopwatch_view;
	CalculateStatic m_stt_hms;
	CalculateButton m_btn_startandstop;
	CalculateButton m_btn_reset;
	CalculateButton m_btn_laptime;
	CalculateButton m_btn_laptime_reset;

	ThemeData* currentTheme;
	UsingManualDialog* usingManual;
	bool bUsingManual;

	CBrush m_backBrush;

	bool bThread;
	bool bStart;

	CWinThread* m_thread;
	CString strHMS;
	CString strM;
	CString strS;
	CString strMils;

	LapTime* laptime;
	bool bLaptime;
	CRect thisRect;
	CRect childRect;
	CRect drawlaptimeBorderRect;
	CRect drawBorderRect;

	static UINT thrStopWatch(LPVOID method);
	void StartStopWatch();
	bool DeleteMainThread();

public:
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnBnClickedButtonStartandstop();
	afx_msg void OnBnClickedButtonReset();
	afx_msg void OnBnClickedButtonLaptime();
	afx_msg void OnMove(int x, int y);
	afx_msg void OnBnClickedButtonLaptimeReset();
	afx_msg void OnPaint();
};
