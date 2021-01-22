#pragma once
#include "ThemeData.h"
#include "CalculateButton.h"
#include "UsingManualDialog.h"

// ManualList 대화 상자

class ManualList : public CDialogEx
{
	DECLARE_DYNAMIC(ManualList)

public:
	ManualList(std::vector<int> usingManualIDVector, ThemeData* currentTheme, CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~ManualList();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_MANUAL_LIST };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()

private:

	CalculateButton m_btn_base_calculator_manual;
	CalculateButton m_btn_engineering_calculator_manual;
	CalculateButton m_btn_stopwatch_manual;
	CalculateButton m_btn_unit_converter_manual;
	CalculateButton m_btn_date_calculator_manual;
	CalculateButton m_btn_work_timer_manual;
	CalculateButton m_btn_notepad_manual;
	CalculateButton m_btn_base_timer_manual;
	CalculateButton m_btn_world_clock_manual;
	CalculateButton m_btn_sort_icon_manual;
	CalculateButton m_btn_theme_setting_manual;
	CalculateButton m_btn_main_frame_manual;

	ThemeData* currentTheme;
	CWnd* pParent;
	std::vector<int> usingManualIDVector;

	int nStartButtonPos_x = 20;
	int nStartButtonPos_y = 20;
	int nButtonWidth = 100;
	int nButtonHeight = 30;
	int nButtonMargin_x = 20;
	int nButtonMargin_y = 10;

	void SetItemCtlInit(int nCtlID, int nIdx);

public:


	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnClose();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnBnClickedButtonBaseCalculatorManual();
	afx_msg void OnBnClickedButtonEngineeringCalculatorManual();
	afx_msg void OnBnClickedButtonStopwatchManual();
	afx_msg void OnBnClickedButtonUnitConverterManual();
	afx_msg void OnBnClickedDateCalculatorManual();
	afx_msg void OnBnClickedButtonWorkTimerManual();
	afx_msg void OnBnClickedButtonNotepadManual();
	afx_msg void OnBnClickedButtonBaseTimerManual();
	afx_msg void OnBnClickedButtonWorldClockManual();
	afx_msg void OnBnClickedButtonSortIconManual();
	afx_msg void OnBnClickedButtonThemeSettingManual();
	afx_msg void OnBnClickedButtonMainFrameManual();
};
