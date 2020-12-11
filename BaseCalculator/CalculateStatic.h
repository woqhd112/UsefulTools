#pragma once


// CalculateStatic

class CalculateStatic : public CStatic
{
	DECLARE_DYNAMIC(CalculateStatic)

public:
	CalculateStatic();
	virtual ~CalculateStatic();

	void Initialize(int nFontSize, CString strFontName);

private:

	CFont thisFont;

protected:
	DECLARE_MESSAGE_MAP()
};


