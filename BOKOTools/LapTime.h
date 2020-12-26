#pragma once
#include <vector>
#include "CalculateEdit.h"
#include "ThemeData.h"

// LapTime 대화 상자

class LapTime : public CDialogEx
{
	DECLARE_DYNAMIC(LapTime)

public:
	LapTime(ThemeData* currentTheme, CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~LapTime();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_LAPTIME };
#endif

public:

	void AppendLapTime(CString strM, CString strS, CString strMils);
	void DeleteLapTime();

private:

	int nStartEditPos;
	int nStaticEditID;
	int nStaticLapTimeCount;
	CRect thisRect;
	CBrush m_backBrush;

	ThemeData* currentTheme;

	std::vector<CalculateEdit*> editVector;

	int nViewHeight;
	int nScrollPos;
	int nPageSize;
	int m_nBasic;
	int cy;

	void SetScrollSize(int nThisHeight);
	void ResetGValue();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	virtual void OnOK();
};
