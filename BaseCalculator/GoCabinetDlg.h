﻿
// BaseCalculatorDlg.h: 헤더 파일
//

#pragma once
#include "BaseCalculate.h"
#include "EngineeringCalculate.h"
#include "UnitConverter.h"
#include "DateCalculate.h"
#include "StopWatch.h"
#include "Timer.h"
#include "GdipButton.h" 

#define BASE_BKGROUND_COLOR RGB(55, 55, 55)

// CBaseCalculatorDlg 대화 상자
class CGoCabinetDlg : public CDialogEx
{
// 생성입니다.
public:
	CGoCabinetDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

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

	CalculateStatic m_stt_engineering;
	CalculateStatic m_stt_base;
	CalculateStatic m_stt_converter;
	CalculateStatic m_stt_date;
	CalculateStatic m_stt_stopwatch;
	CalculateStatic m_stt_timer;
	CGdipButton m_btn_base_gdi;
	CGdipButton m_btn_calculator_gdi;
	CGdipButton m_btn_stopwatch_gdi;
	CGdipButton m_btn_converter_gdi;
	CGdipButton m_btn_date_gdi;
	CGdipButton m_btn_timer_gdi;

	BaseCalculate* base;
	EngineeringCalculate* engineering;
	UnitConverter* converter;
	DateCalculate* date;
	StopWatch* stopwatch;
	Timer* timer;

	//CBrush m_returnBrush;

	void SetCtlPos();

public:
	bool bBase;
	bool bEngineering;
	bool bConverter;
	bool bDate;
	bool bStopWatch;
	bool bTimer;

public:

	virtual void OnOK();

	virtual BOOL PreTranslateMessage(MSG* pMsg);
	
	afx_msg void OnBnClickedButtonBaseGdi();
	afx_msg void OnBnClickedButtonCalculatorGdi();
	afx_msg void OnBnClickedButtonStopwatchGdi();
	afx_msg void OnBnClickedButtonConverterGdi();
	afx_msg void OnBnClickedButtonDateGdi();
	afx_msg void OnBnClickedButtonTimerGdi();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
