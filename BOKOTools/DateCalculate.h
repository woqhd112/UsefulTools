#pragma once
#include "CalculateButton.h"
#include "CalculateEdit.h"
#include "CalculateStatic.h"
#include "UsingManualDialog.h"


// DateCalculate 대화 상자

class DateCalculate : public CDialogEx
{
	DECLARE_DYNAMIC(DateCalculate)

public:
	DateCalculate(int nManualImageID, bool bUsingManual, ThemeData* currentTheme, CWnd* pParent = nullptr);   // 표준 생성자입니다.
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
	CButton m_btn_focus;
	CalculateStatic m_stt_limitdate_view;
	CalculateStatic m_stt_limitdate_divide_view;
	CalculateStatic m_stt_limitdate;
	CalculateStatic m_stt_base_date;
	CalculateStatic m_stt_first_official;
	CalculateStatic m_stt_last_official;

	ThemeData* currentTheme;
	UsingManualDialog* usingManual;
	bool bUsingManual;

	CRect drawBorderRect1;
	CRect drawBorderRect2;

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
	afx_msg void OnPaint();
};
