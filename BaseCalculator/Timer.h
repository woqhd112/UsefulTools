#pragma once
#include "CalculateButton.h"
#include "CalculateEdit.h"

// Timer 대화 상자

class Timer : public CDialogEx
{
	DECLARE_DYNAMIC(Timer)

public:
	Timer(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~Timer();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_TIMER };
#endif

private:

	CWnd* pParent;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
	virtual void OnOK();

private:

	CalculateEdit m_edit_work_hour_1;
	CalculateEdit m_edit_work_hour_2;
	CalculateEdit m_edit_work_minute_1;
	CalculateEdit m_edit_work_minute_2;
	CalculateEdit m_edit_work_second_1;
	CalculateEdit m_edit_work_second_2;
	CalculateEdit m_edit_rest_hour_1;
	CalculateEdit m_edit_rest_hour_2;
	CalculateEdit m_edit_rest_minute_1;
	CalculateEdit m_edit_rest_minute_2;
	CalculateEdit m_edit_rest_second_1;
	CalculateEdit m_edit_rest_second_2;
	CalculateButton m_btn_startandstop;
	CalculateButton m_btn_reset;
	CalculateButton m_btn_work_hour_up;
	CalculateButton m_btn_work_hour_down;
	CalculateButton m_btn_work_minute_up;
	CalculateButton m_btn_work_minute_down;
	CalculateButton m_btn_work_second_up;
	CalculateButton m_btn_work_second_down;
	CalculateButton m_btn_rest_hour_up;
	CalculateButton m_btn_rest_hour_down;
	CalculateButton m_btn_rest_minute_up;
	CalculateButton m_btn_rest_minute_down;
	CalculateButton m_btn_rest_second_up;
	CalculateButton m_btn_rest_second_down;

	CBrush m_backBrush;

	bool bThread;
	bool bStart;

	bool bWorkEnd;
	bool bRestEnd;

	CWinThread* m_thread;

	static UINT thrTimer(LPVOID method);
	void StartTimer();
	void CalculateWorkTime();

	void SetEnabledCtrl(BOOL bEnabled);
	void EmptyTextCondition(int nExceptionEditCtlID = 0);

public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnClose();
	virtual void PostNcDestroy();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonWorkHourUp();
	afx_msg void OnBnClickedButtonWorkHourDown();
	afx_msg void OnBnClickedButtonWorkMinuteUp();
	afx_msg void OnBnClickedButtonWorkMinuteDown();
	afx_msg void OnBnClickedButtonWorkSecondUp();
	afx_msg void OnBnClickedButtonWorkSecondDown();
	afx_msg void OnBnClickedButtonRestHourUp();
	afx_msg void OnBnClickedButtonRestHourDown();
	afx_msg void OnBnClickedButtonRestMinuteUp();
	afx_msg void OnBnClickedButtonRestMinuteDown();
	afx_msg void OnBnClickedButtonRestSecondUp();
	afx_msg void OnBnClickedButtonRestSecondDown();
	afx_msg void OnBnClickedButtonStartandstop2();
	afx_msg void OnBnClickedButtonReset2();
};
