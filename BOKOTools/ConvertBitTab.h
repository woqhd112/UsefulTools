#pragma once
#include "CalculateButton.h"
#include "CalculateEdit.h"
#include "CalculateStatic.h"
#include "GdipButton.h" 
#include "ThemeData.h"


// ConvertBitTab 대화 상자

class ConvertBitTab : public CDialogEx
{
	DECLARE_DYNAMIC(ConvertBitTab)

public:
	ConvertBitTab(ThemeData* currentTheme, CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~ConvertBitTab();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TAB_BIT };
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
	CalculateButton m_btn_container;
	CComboBox m_combo_left;
	CalculateEdit m_edit_left_value;
	CalculateStatic m_stt_bit;
	CalculateStatic m_stt_byte;
	CalculateStatic m_stt_kbyte;
	CalculateStatic m_stt_mbyte;
	CalculateStatic m_stt_gbyte;
	CalculateStatic m_stt_tbyte;
	CalculateStatic m_stt_pbyte;
	CalculateStatic m_stt_ebyte;
	CalculateStatic m_stt_divide;

	CBrush m_backBrush;
	ThemeData* currentTheme;

	CFont comboFont;

	CRect drawBorderRect;
	CRect drawComboBorderRect;

	bool bComboShow;

	void ConvertBit();
	double ConvertLeftToMByte();
	void SetComboButtonText(CString strSymbol);
	void SetTestButtonText();
	void SetStaticValue(double dFirstValue);
	void CalcDrawLine(CPaintDC* dc, int nStartValue_y, int nStartMargin, int nDepth = 1);

public:
	afx_msg void OnBnClickedButtonCombo4();
	afx_msg void OnEnChangeEditLeftValue4();
	afx_msg void OnCbnSelchangeComboLeft4();
	afx_msg void OnCbnSelchangeComboRight4();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);

	afx_msg void OnPaint();
};
