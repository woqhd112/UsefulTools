#pragma once


// ConvertButton

class ConvertButton : public CMFCButton
{
	DECLARE_DYNAMIC(ConvertButton)

public:
	ConvertButton();
	virtual ~ConvertButton();

	enum FontFlag
	{
		DEFAULT		= 0,
		HOVER		= 1,
		CLICK		= 2,
		CLICKHOVER	= 3
	};

	void Initialize(COLORREF color, FlatStyle style, CString strFontName = _T("고딕"), int nFontSize = 14);
	void InsertImage(int nImageID);
	void SetFont(FontFlag flag);
	void SetAlignment(CMFCButton::AlignStyle style);

	bool m_bClick = false;
	bool m_bUseMouseEvent = true;

private:
	bool m_bTrackMouse = false;
	bool m_bDown = false;

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


