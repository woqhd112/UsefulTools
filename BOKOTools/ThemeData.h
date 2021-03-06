#pragma once
#include "atlstr.h"

#define THEME_MAIN_TIME_POS_UP	0
#define THEME_MAIN_TIME_POS_DOWN	370

#define THEME_BASIC		0
#define THEME_DETECTIVE	1
#define THEME_CLOUD		2
#define THEME_LIGHT		3
#define THEME_MAGNIFIER 4
#define THEME_INK		5
#define THEME_WATERDROP	6
#define THEME_PLANET	7
#define THEME_NEONSIGN	8
#define THEME_UTIL		9


class ThemeData
{
public:

	ThemeData(int nThemeFlags);
	~ThemeData();


private:

	friend class SortIcon;

	struct FunctionIcon
	{
		int nNormalID;
		int nHoverID;
		int nClickID;
	};

	CString strThemeName;
	CString strThemeFontName;
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
	COLORREF rectBorderColor;
	COLORREF functionRectBorderColor;
	COLORREF buttonColor;
	int nMainBkIconID;
	int nSettingThemeBkIconID;
	int nThemeFlags;
	int nMainTimePosMargin;

public:

	int GetThemeFlags() const;
	CString GetThemeName() const;
	CString GetThemeFontName() const;
	FunctionIcon GetThemeButtonIcon() const;
	FunctionIcon GetBaseIcon() const;
	FunctionIcon GetEngineeringIcon() const;
	FunctionIcon GetStopWatchIcon() const;
	FunctionIcon GetConverterIcon() const;
	FunctionIcon GetDateCalIcon() const;
	FunctionIcon GetWorkTimerIcon() const;
	FunctionIcon GetNotePadIcon() const;
	FunctionIcon GetBaseTimerIcon() const;
	FunctionIcon GetWorldClockIcon() const;
	FunctionIcon GetScrollIcon() const;
	FunctionIcon GetCommingSoonIcon() const;
	COLORREF GetTextColor() const;
	COLORREF GetFunctionTextColor() const;
	COLORREF GetFunctionBkColor() const;
	COLORREF GetFunctionSubColor() const;
	COLORREF GetRectBorderColor() const;
	COLORREF GetFunctionRectBorderColor() const;
	COLORREF GetButtonColor() const;
	int GetSettingThemeBkIconID() const;
	int GetMainBkIconID() const;
	int GetMainTimePosMargin() const;
};

