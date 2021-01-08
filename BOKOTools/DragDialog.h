#pragma once
#include "GdipButton.h"

// DragDialog 대화 상자

class DragDialog : public CDialogEx
{
	DECLARE_DYNAMIC(DragDialog)

public:
	DragDialog(CGdipButton* eventButton, CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~DragDialog();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_DRAG };
#endif

private:

	CWnd* pParent;
	CGdipButton* hoverButton;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CGdipButton* newButton;

	//void Initialize(ThemeData* currentTheme, CGdipButton* eventButton);

	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnMove(int x, int y);
};
