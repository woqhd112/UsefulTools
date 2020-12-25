#pragma once

// CalculateButton

class CalculateButton : public CMFCButton
{
	DECLARE_DYNAMIC(CalculateButton)

public:
	CalculateButton();
	virtual ~CalculateButton();

	void Initialize(COLORREF color, FlatStyle style, CString strFontName = _T("고딕"));
	void InsertImage(int nImageID);

	COLORREF m_defaultColor;
	COLORREF m_hoverColor;
	COLORREF m_downColor;
	bool m_bUseMouseEvent;

private:
	bool m_bTrackMouse = false;
	int nImageID;
	CFont font;
	int nID;

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnMouseHover(UINT nFlags, CPoint point);
	afx_msg void OnMouseLeave();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
};


