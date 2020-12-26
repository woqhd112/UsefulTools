#pragma once
#include "CalculateButton.h"
#include "CalculateEdit.h"
#include "CalculateStatic.h"
#include "GdipButton.h" 
#include "ThemeData.h"

// ConvertWidthTab 대화 상자

class ConvertWidthTab : public CDialogEx
{
	DECLARE_DYNAMIC(ConvertWidthTab)

public:
	ConvertWidthTab(ThemeData* currentTheme, CWnd* pParent = nullptr);   // 표준 생성자입니다.
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
	CGdipButton m_btn_icon;
	CGdipButton m_btn_reverse;
	CalculateButton m_btn_combo;
	CalculateButton m_btn_test1;
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
	CalculateStatic m_stt_divide;

	CBrush m_backBrush;
	CBrush m_rightValueBrush;
	ThemeData* currentTheme;

	bool bComboShow;

	void ConvertWidth();
	double ConvertLeftToSquaredKMeter();
	double ConvertSquaredKMeterToRight(double dFirstResult, CString& strSymbol);
	void SetComboButtonText(CString strSymbol);
	void SetTestButtonText();
	void SetStaticValue(double dFirstValue);
	void CalcDrawLine(CPaintDC* dc, int nStartValue_y, int nStartMargin, int nDepth = 1);

public:
	afx_msg void OnBnClickedButtonCombo2();
	afx_msg void OnCbnSelchangeComboLeft2();
	afx_msg void OnCbnSelchangeComboRight2();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnEnChangeEditLeftValue2();
	afx_msg void OnBnClickedButtonReverse3();
	
	afx_msg void OnPaint();
};
