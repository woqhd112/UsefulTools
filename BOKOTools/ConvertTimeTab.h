#pragma once
#include "ConvertButton.h"
#include "CalculateButton.h"
#include "CalculateEdit.h"
#include "CalculateStatic.h"
#include "GdipButton.h" 

// ConvertTimeTab 대화 상자

class ConvertTimeTab : public CDialogEx
{
	DECLARE_DYNAMIC(ConvertTimeTab)

public:
	ConvertTimeTab(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~ConvertTimeTab();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TAB_TIME };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
	virtual void OnOK();
public:
	virtual BOOL OnInitDialog();
private:
	CGdipButton m_btn_icon;
	ConvertButton m_btn_test1;
	ConvertButton m_btn_test2;
	ConvertButton m_btn_test3;
	ConvertButton m_btn_test4;
	CalculateButton m_btn_reset;
	CalculateEdit m_edit_date;
	CalculateEdit m_edit_hour;
	CalculateEdit m_edit_minute;
	CalculateEdit m_edit_second;
	CalculateStatic m_stt_dhms;
	CalculateStatic m_stt_hms;
	CalculateStatic m_stt_ms;
	CalculateStatic m_stt_s;
	CalculateStatic m_stt_divide;

	CBrush m_backBrush;

	void ConvertTime();
	void SetDHMS(CString strDate, CString strHour, CString strMinute, CString strSecond);
	void SetHMS(CString strDate, CString strHour, CString strMinute, CString strSecond);
	void SetMS(CString strDate, CString strHour, CString strMinute, CString strSecond);
	void SetS(CString strDate, CString strHour, CString strMinute, CString strSecond);
	void CalcDrawLine(CPaintDC* dc, int nStartValue_y, int nStartMargin, int nDepth = 1);

public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnEnChangeEditDate();
	afx_msg void OnEnChangeEditHour();
	afx_msg void OnEnChangeEditMinute();
	afx_msg void OnEnChangeEditSecond();
	afx_msg void OnBnClickedButtonResetTime();
	afx_msg void OnPaint();
};
