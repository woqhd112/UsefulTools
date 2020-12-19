
// BaseCalculatorDlg.h: 헤더 파일
//

#pragma once
#include "BaseCalculate.h"
#include "EngineeringCalculate.h"
#include "UnitConverter.h"
#include "DateCalculate.h"
#include "StopWatch.h"
#include "Timer.h"

// CBaseCalculatorDlg 대화 상자
class CGojasToolsDlg : public CDialogEx
{
// 생성입니다.
public:
	CGojasToolsDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

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

	CalculateButton m_btn_base;
	CalculateButton m_btn_engineering;
	CalculateButton m_btn_converter;
	CalculateButton m_btn_date;
	CalculateButton m_btn_stopwatch;
	CalculateButton m_btn_timer;
	CalculateStatic m_stt_engineering;
	CalculateStatic m_stt_base;
	CalculateStatic m_stt_converter;
	CalculateStatic m_stt_date;
	CalculateStatic m_stt_stopwatch;
	CalculateStatic m_stt_timer;

	BaseCalculate* base;
	EngineeringCalculate* engineering;
	UnitConverter* converter;
	DateCalculate* date;
	StopWatch* stopwatch;
	Timer* timer;


public:
	bool bBase;
	bool bEngineering;
	bool bConverter;
	bool bDate;
	bool bStopWatch;
	bool bTimer;

public:
	afx_msg void OnBnClickedButtonBase();
	afx_msg void OnBnClickedButtonCalculator();
	afx_msg void OnBnClickedButtonConverter();
	afx_msg void OnBnClickedButtonTime();
	afx_msg void OnBnClickedButtonStopWatch();
	virtual void OnOK();

	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnBnClickedButtonTimer1();
};
