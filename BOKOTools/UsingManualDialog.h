#pragma once
#include "CustomScroll.h"
#include "CustomXml.h"
#include <vector>

// UsingManualDialog 대화 상자

class UsingManualDialog : public CDialogEx
{
	DECLARE_DYNAMIC(UsingManualDialog)

public:
	UsingManualDialog(int nParentID, std::vector<int> usingTypeManualVector, ThemeData* currentTheme, CWnd* pParent = nullptr);   // 표준 생성자입니다.
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

	CustomScroll scroll;
	std::vector<int> usingTypeManualVector;

	CButton m_btn_check_never_look_back;

	void SaveUsingManual();
	CString GetDialogName(int nID);

public:
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnClose();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
};
