#pragma once
#include "CalculateButton.h"
#include "ConvertButton.h"
#include "CalculateEdit.h"
#include "CMarkup/Markup.h"
#include "CXml\Xml.h"

#define BACKGROUND_COLOR_YELLOW		RGB(241, 209, 85)
#define BACKGROUND_COLOR_GREEN		RGB(101, 179, 97)
#define BACKGROUND_COLOR_RED		RGB(215, 70, 57)

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

	enum OperateState
	{
		OPERATE_STATE_NONE		= 0,
		OPERATE_STATE_WORKING	= 1,
		OPERATE_STATE_RESTING	= 2
	};

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
	CalculateEdit m_edit_custom_count;
	CalculateEdit m_edit_state;
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
	ConvertButton m_btn_color_none;
	ConvertButton m_btn_color_working;
	ConvertButton m_btn_color_resting;
	CButton m_radio_infinite;
	CButton m_radio_custom;

	CBrush m_returnBrush;
	COLORREF none_color;
	COLORREF work_color;
	COLORREF rest_color;

	OperateState os;

	bool bThread;
	bool bStart;

	bool bWorkEnd;
	bool bRestEnd;
	bool bFirstRestClock;
	bool bFirstWorkClock;

	CString g_str_work_hour;
	CString g_str_work_minute;
	CString g_str_work_second;
	CString g_str_rest_hour;
	CString g_str_rest_minute;
	CString g_str_rest_second;

	CWinThread* m_thread;

	static UINT thrTimer(LPVOID method);
	void StartTimer();
	void CalculateWorkTime();
	void CalculateRestTime();
	bool CheckRepeatCount();
	void SetGlobalEditText();
	void SetOperateStateToColor(OperateState os);

	void SetEnabledCtrl(BOOL bEnabled);
	void EmptyTextCondition(int nExceptionEditCtlID = 0);
	bool WorkTimeToUnderTenSecondCondition();
	bool RestTimeToUnderTenSecondCondition();
	void LoadSettingColor(COLORREF* none_color, COLORREF* work_color, COLORREF* rest_color);
	void SaveXml(CMarkup* markup);

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
	afx_msg void OnBnClickedRadioInfinite();
	afx_msg void OnBnClickedRadioCustom();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnBnClickedButtonColorNone();
	afx_msg void OnBnClickedButtonColorWorking();
	afx_msg void OnBnClickedButtonColorResting();
};
