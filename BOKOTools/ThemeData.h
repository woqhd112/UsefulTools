#pragma once
#include "atlstr.h"

#define THEME_DETECTIVE	0

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
	FunctionIcon baseIcon;
	FunctionIcon engineeringIcon;
	FunctionIcon stopwatchIcon;
	FunctionIcon converterIcon;
	FunctionIcon datecalIcon;
	FunctionIcon worktimerIcon;
	FunctionIcon notepadIcon;
	FunctionIcon basetimerIcon;
	FunctionIcon worldclockIcon;
	COLORREF textColor;
	COLORREF functionBkColor;
	COLORREF functionSubColor;
	COLORREF functionSubSubColor;
	COLORREF functionRectBorderColor;
	COLORREF buttonColor;
	int nCommingSoonIconID;
	int nMainBkIconID;

public:

	CString GetThemeName();
	FunctionIcon GetBaseIcon();
	FunctionIcon GetEngineeringIcon();
	FunctionIcon GetStopWatchIcon();
	FunctionIcon GetConverterIcon();
	FunctionIcon GetDateCalIcon();
	FunctionIcon GetWorkTimerIcon();
	FunctionIcon GetNotePadIcon();
	FunctionIcon GetBaseTimerIcon();
	FunctionIcon GetWorldClockIcon();
	COLORREF GetTextColor();
	COLORREF GetFunctionBkColor();
	COLORREF GetFunctionSubColor();
	COLORREF GetFunctionSubSubColor();
	COLORREF GetFunctionRectBorderColor();
	COLORREF GetButtonColor();
	int GetCommingSoonIconID();
	int GetMainBkIconID();

};

