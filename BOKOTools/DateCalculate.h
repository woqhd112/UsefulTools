﻿#pragma once
#include "CalculateButton.h"
#include "CalculateEdit.h"
#include "CalculateStatic.h"
#include "ThemeData.h"


// DateCalculate 대화 상자

class DateCalculate : public CDialogEx
{
	DECLARE_DYNAMIC(DateCalculate)

public:
	DateCalculate(ThemeData* currentTheme, CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~DateCalculate();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_DATE };
#endif

private:

	CWnd* pParent;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual void PostNcDestroy();
	afx_msg void OnClose();
private:
	CMonthCalCtrl m_cal_calendar;
	CalculateEdit m_edit_baseedit;
	CalculateEdit m_edit_afterdate;
	CalculateEdit m_edit_afterdate_result;
	CalculateEdit m_edit_limitdate_result;
	CalculateEdit m_edit_limitdate;
	CalculateButton m_btn_afterdate;
	CalculateButton m_btn_limitdate;
	CalculateButton m_btn_reset;
	CalculateStatic m_stt_group_limitdate;
	CButton m_btn_focus;

	ThemeData* currentTheme;

	bool bBaseEditMax;
	bool bLimitEditMax;

	void SetCalendar();
	bool IsDot(CString strText);

public:
	afx_msg void OnMcnSelchangeMonthcalendar(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnEnChangeEditBasedate();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);

	afx_msg void OnEnChangeEditLimitDate();
	afx_msg void OnBnClickedButtonAfterdate();
	afx_msg void OnBnClickedButtonLimitdate();

	afx_msg void OnBnClickedButtonAllreset();
};
