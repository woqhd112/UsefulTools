#pragma once
#include "GdipButton.h"
#include "CalculateStatic.h"
#pragma warning(disable:4819)
#include "Resource.h"

// DragDialog 대화 상자

class DragDialog : public CDialogEx
{
	DECLARE_DYNAMIC(DragDialog)

public:
	
	DragDialog(CGdipButton* eventButton, CalculateStatic* eventStatic, int nButtonWidth, int nButtonHeight, CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~DragDialog();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_DIALOG_DRAG }; 

private:

	CWnd* pParent;
	CGdipButton* hoverButton;
	CalculateStatic* hoverStatic;
	int nButtonWidth;
	int nButtonHeight;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CGdipButton* newButton;
	CalculateStatic* newStatic;

	//void Initialize(ThemeData* currentTheme, CGdipButton* eventButton);

	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnMove(int x, int y);
};
