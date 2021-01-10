#pragma once
#include "CalculateButton.h"
#include "CalculateEdit.h"
#include "CalculateStatic.h"
#include "GdipButton.h" 
#include "ThemeData.h"

// ConvertWeightTab 대화 상자

class ConvertWeightTab : public CDialogEx
{
	DECLARE_DYNAMIC(ConvertWeightTab)

public:
	ConvertWeightTab(ThemeData* currentTheme, CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~ConvertWeightTab();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TAB_WEIGHT };
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
	CalculateButton m_btn_test1;
	CalculateEdit m_edit_left_value;
	CComboBox m_combo_left;
	CalculateStatic m_stt_mg;
	CalculateStatic m_stt_g;
	CalculateStatic m_stt_kg;
	CalculateStatic m_stt_t;
	CalculateStatic m_stt_kt;
	CalculateStatic m_stt_gr;
	CalculateStatic m_stt_oz;
	CalculateStatic m_stt_lb;
	CalculateStatic m_stt_don;
	CalculateStatic m_stt_nyang;
	CalculateStatic m_stt_geun;
	CalculateStatic m_stt_guan;
	CalculateStatic m_stt_divide;

	CBrush m_backBrush;
	ThemeData* currentTheme;

	CRect drawBorderRect;
	CRect drawComboBorderRect;

	bool bComboShow;

	void ConvertWeight();
	double ConvertLeftToKGram();
	void SetComboButtonText(CString strSymbol);
	void SetTestButtonText();
	void SetStaticValue(double dFirstValue);
	void CalcDrawLine(CPaintDC* dc, int nStartValue_y, int nStartMargin, int nDepth = 1);

public:
	afx_msg void OnBnClickedButtonCombo3();
	afx_msg void OnCbnSelchangeComboLeft3();
	afx_msg void OnCbnSelchangeComboRight3();
	afx_msg void OnEnChangeEditLeftValue3();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	
	afx_msg void OnPaint();
};
