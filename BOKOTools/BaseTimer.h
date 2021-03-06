﻿#pragma once
#include "CalculateButton.h"
#include "CalculateEdit.h"
#include "CalculateStatic.h"
#include "UsingManualDialog.h"

#pragma comment(lib, "winmm")
#include <mmsystem.h>

// BaseTimer 대화 상자

class BaseTimer : public CDialogEx
{
	DECLARE_DYNAMIC(BaseTimer)

public:
	BaseTimer(int nManualImageID, bool bUsingManual, ThemeData* currentTheme, CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~BaseTimer();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_BASE_TIMER };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()

private:

	enum ButtonSignal
	{
		SIGNAL_NONE			= 0,
		SIGNAL_MINUTE_UP	= 1,
		SIGNAL_MINUTE_DOWN	= 2,
		SIGNAL_SECOND_UP	= 3,
		SIGNAL_SECOND_DOWN	= 4
	};

	CalculateButton m_btn_m_up;
	CalculateButton m_btn_m_down;
	CalculateButton m_btn_s_up;
	CalculateButton m_btn_s_down;
	CalculateButton m_btn_startandstop;
	CalculateButton m_btn_reset;
	CalculateStatic m_stt_basetimer_view;
	CalculateEdit m_edit_basetimer_m;
	CalculateEdit m_edit_basetimer_s;
	CalculateStatic m_stt_basetimer_colon;

	CWnd* pParent;
	ThemeData* currentTheme;
	UsingManualDialog* usingManual;
	bool bUsingManual;

	CBrush m_backBrush;

	CRect drawBorderRect;

	CWinThread* m_thread;
	CWinThread* m_soundThread;
	CWinThread* m_maintainThread;

	ButtonSignal bs;

	int nMaintainCount;

	bool bThread;
	bool bSoundThread;
	bool bMaintainThread;
	bool bStart;

	static UINT thrBaseTimer(LPVOID method);
	static UINT thrLoadSound(LPVOID method);
	static UINT thrClickMaintain(LPVOID method);
	void StartBaseTimer();
	void StartSound(int nSoundResourceID);
	void StartMaintainCount();
	bool DeleteMainThread();
	void ResetDefaultValue();

	void MinuteUp();
	void MinuteDown();
	void SecondUp();
	void SecondDown();

public:

	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnClose();
	virtual void PostNcDestroy();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnBnClickedButtonBaseTimerStartandstop();
	afx_msg void OnBnClickedButtonBaseTimerReset();
	afx_msg void OnBnClickedButtonBaseTimerMUp();
	afx_msg void OnBnClickedButtonBaseTimerMDown();
	afx_msg void OnBnClickedButtonBaseTimerSUp();
	afx_msg void OnBnClickedButtonBaseTimerSDowm();
	afx_msg void OnPaint();
};
