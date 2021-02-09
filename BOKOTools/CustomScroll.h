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

	enum CustomScrollFlags
	{
		CUSTOM_SCROLL_FLAGS_VERTICAL	= SB_VERT,
		CUSTOM_SCROLL_FLAGS_HORIZON		= SB_HORZ
	};

	struct CustomScrollInfo
	{
		CustomScrollType cst;
		CustomScrollFlags csf;
		int nWheelValue;
		int nAllPageSize;
		int nOnePageSize;
		int nScrollPos;
		bool bLikeButtonEvent = true;
	};

	void Create(CWnd* pDialogCtl);
	void Destroy();
	void Initialize(CustomScrollInfo csi);
	void LineEnd();
	void LineDelete();
	void LoadScroll(int nThisHeight);
	void ExecuteScrollPos(ThemeData* currentTheme);

	void ThemeChange(ThemeData* changeTheme);

	bool OperateScroll(int nSBCode, int nPos);
	UINT OperateWheel(short zDelta);

	int GetLineCount();
	int GetCurrentLinePos();

	void IncreaseScroll();

	CustomScrollInfo csi;

private:

	ThemeData* currentTheme;
	CWnd* thisCtlDialog;
	int nButtonID;
	int nLineCount;
	int nCurrentLinePos;

	bool bOneButtonLight;

	std::vector<CGdipButton*> buttonVector;
	std::vector<CRect> buttonRect;
};

