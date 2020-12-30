#pragma once
#include "GdipButton.h"
#include "ThemeData.h"

// DragDialog 대화 상자

class DragDialog : public CDialogEx
{
	DECLARE_DYNAMIC(DragDialog)

public:
	DragDialog(ThemeData* currentTheme, CGdipButton* eventButton, CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~DragDialog();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_DRAG };
#endif

private:

	CWnd* pParent;
	CGdipButton* hoverButton;
	CGdipButton* newButton;
	ThemeData* currentTheme;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:

	void Initialize(ThemeData* currentTheme, CGdipButton* eventButton);

	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
