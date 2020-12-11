#pragma once
#include "Formula.h"
#include "CalculateButton.h"
#include "CalculateStatic.h"
#include "ResultTimeline.h"
#include <vector>



// EngineeringCalculate 대화 상자

class EngineeringCalculate : public CDialogEx
{
	DECLARE_DYNAMIC(EngineeringCalculate)

public:
	EngineeringCalculate(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~EngineeringCalculate();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_ENGINEERING };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonClear();
	afx_msg void OnBnClickedButtonBack();
	afx_msg void OnBnClickedButtonDivide();
	afx_msg void OnBnClickedButtonMulti();
	afx_msg void OnBnClickedButtonSum();
	afx_msg void OnBnClickedButtonMin();
	afx_msg void OnBnClickedButtonResult();
	afx_msg void OnBnClickedButtonDot();
	afx_msg void OnBnClickedButton0();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton6();
	afx_msg void OnBnClickedButton7();
	afx_msg void OnBnClickedButton8();
	afx_msg void OnBnClickedButton9();
	afx_msg void OnBnClickedButtonOpenbracket();
	afx_msg void OnBnClickedButtonClosebracket();
	afx_msg void OnBnClickedButtonExponentiation();
	afx_msg void OnBnClickedButtonRemainer();
	afx_msg void OnBnClickedButtonRoot();
	afx_msg void OnBnClickedButtonFactorial();

private:
	void ClickEnd(CString strEnd);
	void InputToOperator(CString inputOperator);

private:
	CalculateEdit m_edit_calculate_view;
	CalculateEdit m_edit_result;
	CalculateButton m_btn_clear;
	CalculateButton m_btn_back;
	CalculateButton m_btn_divide;
	CalculateButton m_btn_multi;
	CalculateButton m_btn_sum;
	CalculateButton m_btn_min;
	CalculateButton m_btn_result;
	CalculateButton m_btn_dot;
	CalculateButton m_btn_openbracket;
	CalculateButton m_btn_closebracket;
	CalculateButton m_btn_0;
	CalculateButton m_btn_1;
	CalculateButton m_btn_2;
	CalculateButton m_btn_3;
	CalculateButton m_btn_4;
	CalculateButton m_btn_5;
	CalculateButton m_btn_6;
	CalculateButton m_btn_7;
	CalculateButton m_btn_8;
	CalculateButton m_btn_9;
	CalculateButton m_btn_exponentiation;
	CalculateButton m_btn_remainer;
	CalculateButton m_btn_root;
	CalculateButton m_btn_factorial;
	CalculateButton m_btn_report;
	CalculateButton m_btn_trash;
	CalculateStatic m_stt_calculate_view;

	CWnd* pParent;
	Calculate* calculate;
	//CFont resultEditFont;
	//CFont viewEditFont;
	CBrush m_backBrush;
	CRect thisRect;
	CRect childRect;
	CRect trashRect;
	ResultTimeline timeline;
	bool bTimeline;

	CScrollBar* viewScroll;

public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnClose();
	virtual void PostNcDestroy();
	virtual BOOL OnInitDialog();
	virtual void OnOK();

	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnBnClickedButtonReport();

	
	afx_msg void OnBnClickedButtonTrash();
	afx_msg void OnMove(int x, int y);
};
