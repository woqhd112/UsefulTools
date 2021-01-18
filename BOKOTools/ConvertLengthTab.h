#pragma once
#include "CalculateButton.h"
#include "CalculateEdit.h"
#include "CalculateStatic.h"
#include "GdipButton.h" 
#include "ThemeData.h"

// ConvertLengthTab 대화 상자

class ConvertLengthTab : public CDialogEx
{
	DECLARE_DYNAMIC(ConvertLengthTab)

public:
	ConvertLengthTab(ThemeData* currentTheme, CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~ConvertLengthTab();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TAB_LENGTH };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
	virtual void OnOK();
public:
	virtual BOOL OnInitDialog();
private:
	CGdipButton m_btn_icon;
	CalculateButton m_btn_combo;
	CalculateButton m_btn_test;
	CComboBox m_combo_left;
	CalculateEdit m_edit_left_value;
	CalculateStatic m_stt_mm;
	CalculateStatic m_stt_cm;
	CalculateStatic m_stt_m;
	CalculateStatic m_stt_km;
	CalculateStatic m_stt_in;
	CalculateStatic m_stt_ft;
	CalculateStatic m_stt_yd;
	CalculateStatic m_stt_miles;
	CalculateStatic m_stt_ja;
	CalculateStatic m_stt_gan;
	CalculateStatic m_stt_jung;
	CalculateStatic m_stt_lee;
	CalculateStatic m_stt_haelee;
	CalculateStatic m_stt_divide;
	CalculateStatic m_stt_length_all_view;

	CBrush m_backBrush;
	ThemeData* currentTheme;

	CFont comboFont;

	CRect drawBorderRect;
	CRect drawComboBorderRect;

	bool bComboShow;

	void ConvertLength();
	double ConvertLeftToMeter();
	void SetComboButtonText(CString strSymbol);
	void SetTestButtonText();
	void SetStaticValue(double dFirstValue);
	void CalcDrawLine(CPaintDC* dc, int nStartValue_y, int nStartMargin, int nDepth = 1);

public:
	afx_msg void OnBnClickedButtonCombo();
	afx_msg void OnCbnSelchangeComboLeft();

	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	
	afx_msg void OnEnChangeEditLeftValue();
	
	afx_msg void OnPaint();
};
