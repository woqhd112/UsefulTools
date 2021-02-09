#pragma once
#include "FolderItem.h"

// FolderDlg 대화 상자

class FolderList;

class FolderDlg : public CDialogEx
{
	DECLARE_DYNAMIC(FolderDlg)


public:
	FolderDlg(FolderItem0* folder, ThemeData* currentTheme, CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~FolderDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_FOLDER };
#endif

private:


	ThemeData* currentTheme;
	CWnd* pParent;
	FolderItem0* folder;
	FolderList* folderlist;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnClose();
	virtual void OnOK();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
