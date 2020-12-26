﻿#pragma once
#include "CalculateStatic.h"
#include "CalculateButton.h"
#include "CalculateEdit.h"
#include "ThemeData.h"

// BaseCalculate 대화 상자

class BaseCalculate : public CDialogEx
{
	DECLARE_DYNAMIC(BaseCalculate)

public:
	BaseCalculate(ThemeData* currentTheme, CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~BaseCalculate();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_BASE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
private:
	void SetComboBox();
	void SelectComboBox();
	char ConvertIntToChar(int nInt);
	int ConvertCharToInt(CString strStr);
	void InputTenToSet(int nMacro, CString strOutput);
	CString OutputSetToTen(int nMacro);

	CWnd* pParent;
	ThemeData* currentTheme;

	CRect drawBorderRect;

	CComboBox m_select;
	CComboBox m_result;

	// 2진법 계산기 컨트롤러
	CalculateButton m_btn_result_select_from_base;
	CalculateEdit m_edit_input_ten_from_base;
	CalculateEdit m_edit_output_select_from_base;
	//CalculateStatic m_stt_group_base;
	CalculateStatic m_stt_base_view;
	CalculateStatic m_stt_base;
	CStatic m_stt_input_select;
	CStatic m_stt_output_result;

public:
	afx_msg void OnBnClickedButtonResultTwoFrom2();
	virtual BOOL PreTranslateMessage(MSG* pMsg);

	virtual void OnOK();
	afx_msg void OnCbnSelchangeComboResult();
	virtual BOOL OnInitDialog();
	
	afx_msg void OnClose();
	virtual void PostNcDestroy();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnPaint();
};