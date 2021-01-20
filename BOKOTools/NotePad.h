#pragma once
#include "CalculateButton.h"
#include "CalculateStatic.h"
#include "NotePadList.h"
#include "UsingManualDialog.h"

// NotePad 대화 상자

class NotePad : public CDialogEx
{
	DECLARE_DYNAMIC(NotePad)

public:
	NotePad(bool bUsingManual, ThemeData* currentTheme, CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~NotePad();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_NOTEPAD };
#endif

private:

	CalculateButton m_btn_edit_bold;
	CalculateButton m_btn_edit_italic;
	CalculateButton m_btn_edit_underline;
	CalculateButton m_btn_report;
	CalculateStatic m_stt_notepad_list;
	CRichEditCtrl m_richedit_note;

	CFont thisFont;

	CWnd* pParent;
	ThemeData* currentTheme;
	UsingManualDialog* usingManual;
	bool bUsingManual;

	NotePadList* notepadlist;


protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
	virtual void OnOK();
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	virtual void PostNcDestroy();
	afx_msg void OnClose();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonEditBold();
	afx_msg void OnBnClickedButtonEditItalic();
	afx_msg void OnBnClickedButtonEditUnderline();
	afx_msg void OnBnClickedButtonNotepadReport();
};
