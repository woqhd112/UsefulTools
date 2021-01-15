#pragma once
#include "GeneralUtil.h"

// CalculateButton

class CalculateButton : public CMFCButton
{
	DECLARE_DYNAMIC(CalculateButton)

public:
	CalculateButton();
	virtual ~CalculateButton();

	enum FontFlag
	{
		DEFAULT = 0,
		HOVER = 1,
		CLICK = 2,
		CLICKHOVER = 3
	};

	void Initialize(COLORREF color, FlatStyle style, CString strFontName = _T("고딕"), int nFontSize = 10, int nFontFlags = FW_NORMAL);
	void InsertImage(int nImageID);
	void SetFont(FontFlag flag);
	void SetAlignment(CMFCButton::AlignStyle style);

	COLORREF m_defaultColor;
	COLORREF m_hoverColor;
	COLORREF m_downColor;
	bool m_bUseMouseBkGroundColorEvent;
	bool m_bClick;
	bool m_bUseMouseTextItalicEvent;
	bool m_bUseMouseTextBoldEvent;


private:
	bool m_bTrackMouse = false;
	bool m_bDown;
	int nImageID;
	int nID;

	CFont defaultFont;
	CFont hoverFont;
	CFont clickFont;
	CFont clickHoverFont;


protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnMouseHover(UINT nFlags, CPoint point);
	afx_msg void OnMouseLeave();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
};


