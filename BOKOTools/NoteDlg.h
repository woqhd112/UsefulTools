#pragma once
#include "ThemeData.h"
#include "NotePad.h"

// NoteDlg 대화 상자
#define NOTE_CREATE	0
#define NOTE_UPDATE	1

class NoteDlg : public CDialogEx
{
	DECLARE_DYNAMIC(NoteDlg)

public:
	NoteDlg(int nFolderMode, ThemeData* currentTheme, CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~NoteDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_CREATE_NOTE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()

private:

	CalculateButton m_btn_bold;
	CalculateButton m_btn_italic;
	CalculateButton m_btn_underline;
	CGdipButton m_btn_lock;
	CGdipButton m_btn_report;
	CRichEditCtrl m_richedit_notepad;


	ThemeData* currentTheme;
	CWnd* pParent;
	int nFolderMode;

	CBrush m_topBrush;
	CBrush m_bottomBrush;
	CRect wrapBorderRect;
	CRect wrapCenterRect;
	CFont thisFont;

public:
	
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnClose();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnPaint();
};
