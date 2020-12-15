#pragma once
#include "ConvertButton.h"
#include "CalculateEdit.h"
#include "CalculateStatic.h"


// ConvertBitTab 대화 상자

class ConvertBitTab : public CDialogEx
{
	DECLARE_DYNAMIC(ConvertBitTab)

public:
	ConvertBitTab(CWnd* pParent = nullptr);   // 표준 생성자입니다.
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
	ConvertButton m_btn_icon;
	ConvertButton m_btn_combo;
	ConvertButton m_btn_reverse;
	ConvertButton m_btn_container;
	CComboBox m_combo_left;
	CComboBox m_combo_right;
	CalculateEdit m_edit_left_value;
	CalculateEdit m_edit_right_value;
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

	bool bComboShow;

	void ConvertBit();
	double ConvertLeftToMByte();
	double ConvertMByteToRight(double dFirstResult, CString& strSymbol);
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
	afx_msg void OnBnClickedButtonReverse4();

	afx_msg void OnPaint();
};
