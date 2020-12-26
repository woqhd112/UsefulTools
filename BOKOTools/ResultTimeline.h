#pragma once
#include <vector>
#include "CalculateEdit.h"
#include "ThemeData.h"

// ResultTimeline 대화 상자

class ResultTimeline : public CDialogEx
{
	DECLARE_DYNAMIC(ResultTimeline)

public:
	ResultTimeline(ThemeData* currentTheme, CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~ResultTimeline();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_TIMELINE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();

	void AppendTimeline(CString strFormula, CString strResult);
	void DeleteTimeline();


private:

	int nStartEditPos;
	int nStaticEditID;
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

public:
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	virtual void OnOK();
};
