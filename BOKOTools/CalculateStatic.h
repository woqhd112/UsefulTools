#pragma once


// CalculateStatic

class CalculateStatic : public CStatic
{
	DECLARE_DYNAMIC(CalculateStatic)

public:
	CalculateStatic();
	virtual ~CalculateStatic();

	void Initialize(int nFontSize, CString strFontName);
	void InvalidFont(CString strFontName);

private:

	CFont thisFont;
	CString strFontName;
	int nFontSize;

protected:
	DECLARE_MESSAGE_MAP()
};


