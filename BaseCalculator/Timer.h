#pragma once
#include "CalculateButton.h"
#include "ConvertButton.h"
#include "CalculateEdit.h"
#include "CalculateStatic.h"
#include "CMarkup/Markup.h"
#include "CXml\Xml.h"

#pragma comment(lib, "winmm")
#include <mmsystem.h>

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
		OPERATE_STATE_RESTING	= 2,
		OPERATE_STATE_PAUSE		= 3
	};

	enum ProgressState
	{
		PROGRESS_STATE_NONE					= 0,
		PROGRESS_STATE_WORKING_START		= 1,
		PROGRESS_STATE_WORKING_END			= 2,
		PROGRESS_STATE_RESTING_START		= 3,
		PROGRESS_STATE_SOON_RESTING_START	= 4,
		PROGRESS_STATE_SOON_WORKING_START	= 5,
		PROGRESS_STATE_COUNT_0				= 6,
		PROGRESS_STATE_COUNT_1				= 7,
		PROGRESS_STATE_COUNT_2				= 8,
		PROGRESS_STATE_COUNT_3				= 9,
		PROGRESS_STATE_COUNT_4				= 10,
		PROGRESS_STATE_COUNT_5				= 11,
		PROGRESS_STATE_WORKING_END_ALL		= 12
	};

	enum EditFocusPos
	{
		FOCUS_WORK_HOUR_1 = 1,
		FOCUS_WORK_HOUR_2 = 2,
		FOCUS_WORK_MINUTE_1 = 3,
		FOCUS_WORK_MINUTE_2 = 4,
		FOCUS_WORK_SECOND_1 = 5,
		FOCUS_WORK_SECOND_2 = 6,
		FOCUS_REST_HOUR_1 = 7,
		FOCUS_REST_HOUR_2 = 8,
		FOCUS_REST_MINUTE_1 = 9,
		FOCUS_REST_MINUTE_2 = 10,
		FOCUS_REST_SECOND_1 = 11,
		FOCUS_REST_SECOND_2 = 12
	};

	struct TimerReference
	{
		bool bStart = true;				// 시작버튼 클릭 유무, 시작상태 = true
		bool bThread = false;			// 타이머스레드 동작 상태, 동작 = true
		bool bPause = false;			// 일시정지 상태, 일시정지 = true
		bool bWorkEnd = false;			// 업무 한 사이클 완료 상태, 완료 = true
		bool bRestEnd = false;			// 휴식 한 사이클 완료 상태, 완료 = true
		bool bFirstRestClock = true;	// 첫번째 휴식 사이클의 알람 실행 상태, 실행가능 = true
		bool bFirstWorkClock = false;	// 첫번째 업무 사이클의 알람 실행 상태, 실행가능 = true
		bool bLastWorkClock = false;	// 마지막 업무 사이클의 알람 실행 상태, 실행가능 = true
		bool bConstFirstWorkClock = true;	// 타이머 스레드에서 딱 한번의 알람 실행 상태, 실행가능 = true;
		OperateState os = OPERATE_STATE_NONE;	// 현재 타이머의 진행 상태
		ProgressState ps = PROGRESS_STATE_NONE;	// 현재 타이머의 사운드 출력 상태
		CWinThread* m_thread;				// 현재 타이머의 스레드 객체
		CWinThread* m_soundThread;			// 현재 타이머의 알람스레드 객체
		COLORREF none_color;				// 대기상태의 컨트롤러 색상
		COLORREF work_color;				// 업무상태의 컨트롤러 색상
		COLORREF rest_color;				// 휴식상태의 컨트롤러 색상
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
	CalculateButton m_btn_startandpause;
	CalculateButton m_btn_stop;
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
	CalculateButton m_btn_time_save;
	CalculateButton m_btn_time_load;
	CalculateButton m_btn_setting_divide;
	ConvertButton m_btn_color_none;
	ConvertButton m_btn_color_working;
	ConvertButton m_btn_color_resting;
	CButton m_radio_infinite;
	CButton m_radio_custom;
	CalculateStatic m_stt_repeat_setting;
	CalculateStatic m_stt_work_time;
	CalculateStatic m_stt_rest_time;
	CalculateStatic m_stt_color_setting;
	CalculateStatic m_stt_time_setting;
	CStatic m_stt_state;
	CStatic m_stt_color_none;
	CStatic m_stt_color_working;
	CStatic m_stt_color_resting;
	CStatic m_stt_time_load;
	CStatic m_stt_time_save;
	CStatic m_stt_work_hour;
	CStatic m_stt_work_minute;
	CStatic m_stt_work_second;
	CStatic m_stt_rest_hour;
	CStatic m_stt_rest_minute;
	CStatic m_stt_rest_second;

	CBrush m_returnBrush;
	int nBkBrightness;
	
	TimerReference tr;

	CString g_str_work_hour;
	CString g_str_work_minute;
	CString g_str_work_second;
	CString g_str_rest_hour;
	CString g_str_rest_minute;
	CString g_str_rest_second;
	CString g_str_repeat_count;

	EditFocusPos efp;
	CString strCurrentFocusText;

	static UINT thrTimer(LPVOID method);
	static UINT thrLoadSound(LPVOID method);
	void StartTimer();
	void StartSound(CString strSoundPath);
	void StartBeepSound(ProgressState ps);
	void CalculateWorkTime();
	void CalculateRestTime();
	bool CheckRepeatCount(bool bCalc);
	void SetGlobalEditText();
	void SetDefaultGlobalEditText();
	void SetOperateStateToColor(OperateState os);
	void SetOperateColor(COLORREF color, CString strOperateState);
	void ResetTimerReference();

	inline int MinRGBColor(int nRv, int nCalcv) 
	{
		if (nRv - nCalcv < 0) return 0;
		return nRv - nCalcv;
	}

	void SetEnabledCtrl(BOOL bEnabled);
	void EmptyTextCondition(int nExceptionEditCtlID = 0);
	bool TimeToUnderTenSecondCondition(bool isWork);
	void LoadSettingColor();
	void SaveXml(CMarkup* markup, CString strSaveFullPath);
	void CreateConfigFile(CString& strFullPath);
	bool CreateDefaultColorXml(CMarkup* markUp, CString strFilePath);
	void CreateDefaultDirectory(CString& strFullPath, CString strAppendPath);
	void SetSettingColor(CString strOperateState, COLORREF operateColor);
	int GetBrightness(int nRv, int nGv, int nBv);
	void SetDivideTextColor();

	bool bDivideClick;
	int nDivideMargin;

	void SetDivideMargin();

	bool TimerThreadDelete();

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
	afx_msg void OnBnClickedButtonTimeLoad();
	afx_msg void OnBnClickedButtonTimeSave();
	afx_msg void OnBnClickedButtonStop();
	afx_msg void OnBnClickedButtonSettingDivide();
};
