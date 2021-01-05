﻿#pragma once
#include "CalculateStatic.h"
#include "CalculateButton.h"
#include "SortButtonList.h"
#include "AllButtonList.h"
#include "BOKOToolsDlg.h"
#include "DragDialog.h"

// SortIcon 대화 상자


class SortIcon : public CDialogEx
{
	DECLARE_DYNAMIC(SortIcon)

public:
	SortIcon(std::vector<std::vector<int>> ctlVector, ThemeData* currentTheme, CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~SortIcon();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_SORT_ICON };
#endif

private:

	CalculateStatic m_stt_sort_view;
	CalculateStatic m_stt_all_view;
	CalculateButton m_btn_sort_save;

	CWnd* pParent;
	ThemeData* currentTheme;
	std::vector<std::vector<int>> ctlVector;
	std::vector<CGdipButton*> sortButtonVector;

	CBOKOToolsDlg* parentDlg;
	DragDialog* dragDlg;

	int nButtonID;

public:

	CRect dragRect;
	SortButtonList* sortButtonList;
	AllButtonList* allButtonList;
	CalculateButton m_btn_sort_scroll_line;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnPaint();
	afx_msg void OnMove(int x, int y);
	afx_msg void OnBnClickedButtonSortScrollLine();
	afx_msg void OnBnClickedButtonSortSave();
};