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

	CString strFontName;
	int nFontSize;
private:

	CFont thisFont;

protected:
	DECLARE_MESSAGE_MAP()
};


