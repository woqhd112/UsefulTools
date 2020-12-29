#pragma once
#include "GdipButton.h"
#include "ThemeData.h"
#include <vector>

class CustomScroll
{
public:

	CustomScroll();
	~CustomScroll();

	enum CustomScrollType
	{
		CUSTOM_SCROLL_TYPE_DEFAULT	= 0,
		CUSTOM_SCROLL_TYPE_BUTTON	= 1
	};


	struct CustomScrollInfo
	{
		CustomScrollType cst;
		int nKindOfScrollFlags;
		int nWheelValue;
		int nAllPageSize;
		int nOnePageSize;
		int nScrollPos;
	};

	void Create(CWnd* pDialogCtl);
	void Initialize(CustomScrollInfo csi);
	void LineEnd();
	void LoadScroll(int nThisHeight);
	void ExecuteScrollPos(ThemeData* currentTheme);

	void ThemeChange(ThemeData* changeTheme);

	bool OperateScroll(int nSBCode, int nPos);
	UINT OperateWheel(short zDelta);

private:

	ThemeData* currentTheme;
	CustomScrollInfo csi;
	CWnd* thisCtlDialog;
	int nLineCount;
	int nCurrentLinePos;

	std::vector<CGdipButton*> buttonVector;
	std::vector<CRect> buttonRect;
};

