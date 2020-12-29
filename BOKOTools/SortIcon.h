#pragma once
#include "ThemeData.h"

// SortIcon 대화 상자

class SortIcon : public CDialogEx
{
	DECLARE_DYNAMIC(SortIcon)

public:
	SortIcon(ThemeData* currentTheme, CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~SortIcon();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_SORT_ICON };
#endif

private:

	CWnd* pParent;
	ThemeData* currentTheme;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
};
