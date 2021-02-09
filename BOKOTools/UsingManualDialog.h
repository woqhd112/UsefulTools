#pragma once
#include "CustomXml.h"
#include "GdipButton.h"
#include "ThemeData.h"
#include <vector>

// UsingManualDialog 대화 상자

class UsingManualDialog : public CDialogEx
{
	DECLARE_DYNAMIC(UsingManualDialog)

public:
	UsingManualDialog(bool bFuncPopUp, int nParentID, int nManualImageID, ThemeData* currentTheme, CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~UsingManualDialog();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_USING_MANUAL };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()

private:

	ThemeData* currentTheme;
	int nParentID;
	bool bFuncPopUp;
	int nManualImageID;
	std::vector<CGdipButton*> manualButtonVector;

	CButton m_btn_check_never_look_back;
	CGdipButton m_btn_manual_image;

	CFont checkFont;
	CRect checkPosRect;

	void SaveUsingManual();
	CString GetDialogName(int nID);

public:
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnClose();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnBnClickedCheckNeverLookBack();
};
