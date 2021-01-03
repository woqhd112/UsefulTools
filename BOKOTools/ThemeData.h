#pragma once
#include "atlstr.h"

#define THEME_MAIN_TIME_POS_UP	0
#define THEME_MAIN_TIME_POS_DOWN	370
#define THEME_DETECTIVE	0
#define THEME_CLOUD 1
#define THEME_LIGHT 2
#define THEME_MAGNIFIER 3
#define THEME_INK	4

class ThemeData
{
public:

	ThemeData(int nThemeFlags);
	~ThemeData();


private:

	friend class AllButtonList;
	friend class SortButtonList;

	struct FunctionIcon
	{
		int nNormalID;
		int nHoverID;
		int nClickID;
	};

	CString strThemeName;
	CString strButtonSoundPath;
	FunctionIcon themeButtonIcon;
	FunctionIcon baseIcon;
	FunctionIcon engineeringIcon;
	FunctionIcon stopwatchIcon;
	FunctionIcon converterIcon;
	FunctionIcon datecalIcon;
	FunctionIcon worktimerIcon;
	FunctionIcon notepadIcon;
	FunctionIcon basetimerIcon;
	FunctionIcon worldclockIcon;
	FunctionIcon scrollIcon;
	FunctionIcon commingSoonIcon;
	COLORREF textColor;
	COLORREF functionTextColor;
	COLORREF functionBkColor;
	COLORREF functionSubColor;
	COLORREF functionSubSubColor;
	COLORREF rectBorderColor;
	COLORREF functionRectBorderColor;
	COLORREF buttonColor;
	int nMainBkIconID;
	int nSettingThemeBkIconID;
	int nThemeFlags;
	int nMainTimePosMargin;

public:

	int GetThemeFlags();
	CString GetThemeName();
	CString GetButtonSoundPath();
	FunctionIcon GetThemeButtonIcon();
	FunctionIcon GetBaseIcon();
	FunctionIcon GetEngineeringIcon();
	FunctionIcon GetStopWatchIcon();
	FunctionIcon GetConverterIcon();
	FunctionIcon GetDateCalIcon();
	FunctionIcon GetWorkTimerIcon();
	FunctionIcon GetNotePadIcon();
	FunctionIcon GetBaseTimerIcon();
	FunctionIcon GetWorldClockIcon();
	FunctionIcon GetScrollIcon();
	FunctionIcon GetCommingSoonIcon();
	COLORREF GetTextColor();
	COLORREF GetFunctionTextColor();
	COLORREF GetFunctionBkColor();
	COLORREF GetFunctionSubColor();
	COLORREF GetFunctionSubSubColor();
	COLORREF GetRectBorderColor();
	COLORREF GetFunctionRectBorderColor();
	COLORREF GetButtonColor();
	int GetSettingThemeBkIconID();
	int GetMainBkIconID();
	int GetMainTimePosMargin();
};

