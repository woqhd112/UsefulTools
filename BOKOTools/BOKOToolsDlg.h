
// BaseCalculatorDlg.h: 헤더 파일
//

#pragma once
#include "BaseCalculate.h"
#include "EngineeringCalculate.h"
#include "UnitConverter.h"
#include "DateCalculate.h"
#include "CustomScroll.h"
#include "StopWatch.h"
#include "Timer.h"
#include "NotePad.h"
#include "BaseTimer.h"
#include "WorldClock.h"

// CBaseCalculatorDlg 대화 상자
class CBOKOToolsDlg : public CDialogEx
{
// 생성입니다.
public:
	CBOKOToolsDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.
	~CBOKOToolsDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_BASECALCULATOR_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수 
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
private:

	CalculateStatic m_stt_ampm;
	CalculateStatic m_stt_week;
	CalculateStatic m_stt_current_time;

	CalculateStatic m_stt_base;
	CalculateStatic m_stt_engineering;
	CalculateStatic m_stt_converter;
	CalculateStatic m_stt_date;
	CalculateStatic m_stt_stopwatch;
	CalculateStatic m_stt_worktimer;
	CalculateStatic m_stt_notepad;
	CalculateStatic m_stt_basetimer;
	CalculateStatic m_stt_world_clock;
	CGdipButton m_btn_base_gdi;
	CGdipButton m_btn_calculator_gdi;
	CGdipButton m_btn_stopwatch_gdi;
	CGdipButton m_btn_converter_gdi;
	CGdipButton m_btn_date_gdi;
	CGdipButton m_btn_worktimer_gdi;
	CGdipButton m_btn_notepad_gdi;
	CGdipButton m_btn_basetimer_gdi;
	CGdipButton m_btn_world_clock_gdi;
	CGdipButton m_btn_comingsoon_1;
	CGdipButton m_btn_comingsoon_2;
	CGdipButton m_btn_comingsoon_3;

	BaseCalculate* base;
	EngineeringCalculate* engineering;
	UnitConverter* converter;
	DateCalculate* date;
	StopWatch* stopwatch;
	Timer* timer;
	NotePad* notepad;
	BaseTimer* basetimer;
	WorldClock* worldclock;

	CBrush m_returnBrush;

	std::vector<ThemeData*> themeList;
	ThemeData* currentTheme;
	CustomScroll scroll;


	void SetDisableCtlColor();
	void SetCtlPos(std::vector<std::vector<int>> buttonCtlPosVector);
	void LoadTheme();
	int LoadCurrnetTheme();
	void LoadButtonPos();
	void LoadUserInterface(ThemeData* currentTheme);
	void LoadResourceItem(int nResourceID);
	void CreateConfigPosFile(CString& strFullPath);
	bool CreateDefaultPosXml(CMarkup* markUp, CString strFilePath, std::vector<std::vector<int>>& buttonCtlPosVector);
	void CreateConfigThemeFile(CString& strFullPath);
	bool CreateDefaultThemeXml(CMarkup* markUp, CString strFilePath, int& nThemeFlags);
	void CreateDefaultDirectory(CString& strFullPath, CString strAppendPath);
	void SaveXml(CMarkup* markup, CString strSaveFullPath);
	void ButtonCtlDisConnect();
	void ResetScrollAndButton();
	int ConvertVectorToPos(int x, int y);
	std::vector<int> ConvertPosToVector(int nPos);
	void SavePosXml(std::vector<std::vector<int>> ctlItemVector);
	void ChangeBackBrush();


	CWinThread* m_curtimeThread;
	bool bCurTimeThread;

	static UINT thrStartCurrentTime(LPVOID method);
	void StartCurrentTime();
	void ShowCurrentTime();

	const int PICTURE_WIDTH = 128;
	const int PICTURE_HEIGHT = 128;
	const int LEFT_MARGIN = 30;
	const int TOP_MARGIN = 30;
	const int PICTURE_TO_PICTURE_MARGIN_WIDTH = 20;
	const int PICTURE_TO_PICTURE_MARGIN_HEIGHT = 30;
	const int STATIC_HEIGHT = 23;
	int nPageCount;
	int nCtlItemCount;

public:
	bool bBase;
	bool bEngineering;
	bool bConverter;
	bool bDate;
	bool bStopWatch;
	bool bTimer;
	bool bNotepad;
	bool bBaseTimer;
	bool bWorldClock;

	void ExecuteSelectTheme(ThemeData* selectTheme);
	void SetWhichSelectCtlItemPos(int nButtonCtlID, int nStaticCtlId, int nPos_x, int nPos_y);
	void SaveButtonCtlPos(std::vector<std::vector<int>> saveCtlItemVector);

	std::vector<std::vector<int>> ctlItemVector;

public:

	virtual void OnOK();

	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	
	afx_msg void OnBnClickedButtonBaseGdi();
	afx_msg void OnBnClickedButtonCalculatorGdi();
	afx_msg void OnBnClickedButtonStopwatchGdi();
	afx_msg void OnBnClickedButtonConverterGdi();
	afx_msg void OnBnClickedButtonDateGdi();
	afx_msg void OnBnClickedButtonTimerGdi();
	afx_msg void OnBnClickedButtonNotepadGdi();
	afx_msg void OnBnClickedButtonBaseTimerGdi();
	afx_msg void OnBnClickedButtonWorldClockGdi();
	afx_msg void OnMenuSettingTheme();
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMenuSortIcon();
	afx_msg void OnClose();
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
};
