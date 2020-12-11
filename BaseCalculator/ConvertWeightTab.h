#pragma once
#include "ConvertButton.h"
#include "CalculateEdit.h"
#include "CalculateStatic.h"

// ConvertWeightTab 대화 상자

class ConvertWeightTab : public CDialogEx
{
	DECLARE_DYNAMIC(ConvertWeightTab)

public:
	ConvertWeightTab(CWnd* pParent = nullptr);   // 표준 생성자입니다.
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
	ConvertButton m_btn_icon;
	ConvertButton m_btn_combo;
	ConvertButton m_btn_test;
	CalculateEdit m_edit_left_value;
	CalculateEdit m_edit_right_value;
	CComboBox m_combo_left;
	CComboBox m_combo_right;
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

	CBrush m_backBrush;

	bool bComboShow;

	void ConvertLength();
	double ConvertLeftToKGram();
	double ConvertKGramToRight(double dFirstResult, CString& strSymbol);
	void SetComboButtonText(CString strSymbol);
	void SetTestButtonText();
	void SetStaticValue(double dFirstValue);

public:
	afx_msg void OnBnClickedButtonCombo3();
	afx_msg void OnCbnSelchangeComboLeft3();
	afx_msg void OnCbnSelchangeComboRight3();
	afx_msg void OnEnChangeEditLeftValue3();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
