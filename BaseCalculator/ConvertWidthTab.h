﻿#pragma once
#include "ConvertButton.h"
#include "CalculateEdit.h"
#include "CalculateStatic.h"

// ConvertWidthTab 대화 상자

class ConvertWidthTab : public CDialogEx
{
	DECLARE_DYNAMIC(ConvertWidthTab)

public:
	ConvertWidthTab(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~ConvertWidthTab();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TAB_WIDTH };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
	virtual void OnOK();
public:
	virtual BOOL OnInitDialog();
private:
	ConvertButton m_btn_icon;
	ConvertButton m_btn_combo;
	ConvertButton m_btn_test;
	CComboBox m_combo_left;
	CComboBox m_combo_right;
	CalculateEdit m_edit_left_value;
	CalculateEdit m_edit_right_value;
	CalculateStatic m_stt_squared_m;
	CalculateStatic m_stt_are;
	CalculateStatic m_stt_hectare;
	CalculateStatic m_stt_squared_km;
	CalculateStatic m_stt_squared_ft;
	CalculateStatic m_stt_squared_yd;
	CalculateStatic m_stt_acre;
	CalculateStatic m_stt_square_ruler;
	CalculateStatic m_stt_square;
	CalculateStatic m_stt_danbo;
	CalculateStatic m_stt_jungbo;

	CBrush m_backBrush;

	bool bComboShow;

	void ConvertLength();
	double ConvertLeftToSquaredKMeter();
	double ConvertSquaredKMeterToRight(double dFirstResult, CString& strSymbol);
	void SetComboButtonText(CString strSymbol);
	void SetTestButtonText();
	void SetStaticValue(double dFirstValue);

public:
	afx_msg void OnBnClickedButtonCombo2();
	afx_msg void OnCbnSelchangeComboLeft2();
	afx_msg void OnCbnSelchangeComboRight2();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnEnChangeEditLeftValue2();
};
