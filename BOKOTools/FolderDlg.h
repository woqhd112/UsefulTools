#pragma once
#include "ThemeData.h"
#include "NotePad.h"


// FolderDlg 대화 상자

class FolderDlg : public CDialogEx
{
	DECLARE_DYNAMIC(FolderDlg)

public:
	FolderDlg(ThemeData* currentTheme, CWnd* pParent = nullptr, COLORREF tagColor = TAG_COLOR_5);   // 표준 생성자입니다.
	virtual ~FolderDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_CREATE_FOLDER };
#endif

private:

	ThemeData* currentTheme;
	CWnd* pParent;
	COLORREF tagColor;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnClose();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	CMFCButton m_btn_colorindex_1;
	CMFCButton m_btn_colorindex_2;
	CMFCButton m_btn_colorindex_3;
	CMFCButton m_btn_colorindex_4;
	CMFCButton m_btn_colorindex_5;
	CMFCButton m_btn_colorindex_6;
	CMFCButton m_btn_colorindex_7;
	CEdit m_edit_foldername;
};
