#pragma once


// CalculateEdit

class CalculateEdit : public CEdit
{
	DECLARE_DYNAMIC(CalculateEdit)

public:
	CalculateEdit();
	virtual ~CalculateEdit();

	void Initialize(int nFontSize, CString strFontName);

	bool m_bExampleText;

private:

	CFont thisFont;

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};


