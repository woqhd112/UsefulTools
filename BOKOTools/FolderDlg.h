#pragma once
#include "ThemeData.h"
#include "NotePad.h"


// FolderDlg 대화 상자
#define FOLDER_CREATE	0
#define FOLDER_UPDATE	1

class FolderDlg : public CDialogEx
{
	DECLARE_DYNAMIC(FolderDlg)

public:
	FolderDlg(int nFolderMode, ThemeData* currentTheme, COLORREF* tagColor, CString* strFolderName, CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~FolderDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_CREATE_FOLDER };
#endif

private:

	ThemeData* currentTheme;
	CWnd* pParent;
	int nFolderMode;
	COLORREF* tagColor;
	COLORREF selectColor;
	CString* strFolderName;

	CalculateButton m_btn_colorindex_1;
	CalculateButton m_btn_colorindex_2;
	CalculateButton m_btn_colorindex_3;
	CalculateButton m_btn_colorindex_4;
	CalculateButton m_btn_colorindex_5;
	CalculateButton m_btn_colorindex_6;
	CalculateButton m_btn_colorindex_7;
	CalculateButton m_btn_save;
	CEdit m_edit_foldername;
	CalculateStatic m_stt_colorindex;
	CalculateStatic m_stt_folder_name;
	CFont editFont;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnClose();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnBnClickedButtonNotepadColorindex1();
	afx_msg void OnBnClickedButtonNotepadColorindex2();
	afx_msg void OnBnClickedButtonNotepadColorindex3();
	afx_msg void OnBnClickedButtonNotepadColorindex4();
	afx_msg void OnBnClickedButtonNotepadColorindex5();
	afx_msg void OnBnClickedButtonNotepadColorindex6();
	afx_msg void OnBnClickedButtonNotepadColorindex7();
	afx_msg void OnBnClickedButtonNotepadFolderSave();
};
