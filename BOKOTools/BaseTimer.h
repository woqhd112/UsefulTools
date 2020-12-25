#pragma once
#include "CalculateButton.h"
#include "CalculateStatic.h"

#pragma comment(lib, "winmm")
#include <mmsystem.h>

// BaseTimer 대화 상자

class BaseTimer : public CDialogEx
{
	DECLARE_DYNAMIC(BaseTimer)

public:
	BaseTimer(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~BaseTimer();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_BASE_TIMER };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()

private:

	CalculateButton m_btn_m_up;
	CalculateButton m_btn_m_down;
	CalculateButton m_btn_s_up;
	CalculateButton m_btn_s_down;
	CalculateButton m_btn_startandstop;
	CalculateButton m_btn_reset;
	CalculateStatic m_stt_ms;
	CalculateStatic m_stt_basetimer_view;

	CWnd* pParent;

	CBrush m_backBrush;

	CWinThread* m_thread;
	CWinThread* m_soundThread;

	bool bThread;
	bool bStart;

	static UINT thrBaseTimer(LPVOID method);
	static UINT thrLoadSound(LPVOID method);
	void StartBaseTimer();
	void StartSound(CString strSoundPath);
	bool DeleteMainThread();
	void ResetDefaultValue();

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
};
