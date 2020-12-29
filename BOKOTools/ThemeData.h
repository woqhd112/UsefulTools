#pragma once
#include "atlstr.h"

#define THEME_DETECTIVE	0
#define THEME_CLOUD 1
#define THEME_LIGHT 2
#define THEME_MAGNIFIER 3

class ThemeData
{
public:

	ThemeData(int nThemeFlags);
	~ThemeData();


private:

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
	COLORREF textColor;
	COLORREF functionBkColor;
	COLORREF functionSubColor;
	COLORREF functionSubSubColor;
	COLORREF functionRectBorderColor;
	COLORREF buttonColor;
	int nCommingSoonIconID;
	int nMainBkIconID;
	int nSettingThemeBkIconID;
	int nThemeFlags;

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
	COLORREF GetTextColor();
	COLORREF GetFunctionBkColor();
	COLORREF GetFunctionSubColor();
	COLORREF GetFunctionSubSubColor();
	COLORREF GetFunctionRectBorderColor();
	COLORREF GetButtonColor();
	int GetCommingSoonIconID();
	int GetSettingThemeBkIconID();
	int GetMainBkIconID();

};

