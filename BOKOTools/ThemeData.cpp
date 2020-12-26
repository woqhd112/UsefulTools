#include "pch.h"
#include "Resource.h"
#include "ThemeData.h"

ThemeData::ThemeData(int nThemeFlags)
{
	if (nThemeFlags == THEME_DETECTIVE)
	{
		strThemeName = _T("사건 테마");
		baseIcon = { IDB_PNG_BASE_NOMAL_THEME_DETECTIVE, IDB_PNG_BASE_HOVER_THEME_DETECTIVE, IDB_PNG_BASE_CLICK_THEME_DETECTIVE };
		engineeringIcon = { IDB_PNG_ENGINEERING_NOMAL_THEME_DETECTIVE, IDB_PNG_ENGINEERING_HOVER_THEME_DETECTIVE, IDB_PNG_ENGINEERING_CLICK_THEME_DETECTIVE };
		stopwatchIcon = { IDB_PNG_STOPWATCH_NOMAL_THEME_DETECTIVE, IDB_PNG_STOPWATCH_HOVER_THEME_DETECTIVE, IDB_PNG_STOPWATCH_CLICK_THEME_DETECTIVE };
		converterIcon = { IDB_PNG_CONVERTER_NOMAL_THEME_DETECTIVE, IDB_PNG_CONVERTER_HOVER_THEME_DETECTIVE, IDB_PNG_CONVERTER_CLICK_THEME_DETECTIVE };
		datecalIcon = { IDB_PNG_DATECAL_NOMAL_THEME_DETECTIVE, IDB_PNG_DATECAL_HOVER_THEME_DETECTIVE, IDB_PNG_DATECAL_CLICK_THEME_DETECTIVE };
		worktimerIcon = { IDB_PNG_WORKTIMER_NOMAL_THEME_DETECTIVE, IDB_PNG_WORKTIMER_HOVER_THEME_DETECTIVE, IDB_PNG_WORKTIMER_CLICK_THEME_DETECTIVE };
		notepadIcon = { IDB_PNG_NOTEPAD_NOMAL_THEME_DETECTIVE, IDB_PNG_NOTEPAD_HOVER_THEME_DETECTIVE, IDB_PNG_NOTEPAD_CLICK_THEME_DETECTIVE };
		basetimerIcon = { IDB_PNG_BASETIMER_NOMAL_THEME_DETECTIVE, IDB_PNG_BASETIMER_HOVER_THEME_DETECTIVE, IDB_PNG_BASETIMER_CLICK_THEME_DETECTIVE };
		worldclockIcon = { IDB_PNG_WORLDCLOCK_NOMAL_THEME_DETECTIVE, IDB_PNG_WORLDCLOCK_HOVER_THEME_DETECTIVE, IDB_PNG_WORLDCLOCK_CLICK_THEME_DETECTIVE };
		textColor = RGB(255, 255, 255);
		functionBkColor = RGB(28, 11, 4);
		functionSubColor = RGB(48, 31, 24);
		functionSubSubColor = RGB(68, 51, 44);
		functionRectBorderColor = RGB(255, 255, 255);
		buttonColor = RGB(50, 50, 50);
		nCommingSoonIconID = IDB_PNG_COMINGSOON_THEME_DETECTIVE;
		nMainBkIconID = IDB_BITMAP_MAIN_BK_THEME_DETECTIVE;
	}
	else if (nThemeFlags == THEME_CLOUD)
	{
		strThemeName = _T("구름 테마");
		baseIcon = { IDB_PNG_BASE_NOMAL_THEME_CLOUD, IDB_PNG_BASE_HOVER_THEME_CLOUD, IDB_PNG_BASE_CLICK_THEME_CLOUD };
		engineeringIcon = { IDB_PNG_ENGINEERING_NOMAL_THEME_CLOUD, IDB_PNG_ENGINEERING_HOVER_THEME_CLOUD, IDB_PNG_ENGINEERING_CLICK_THEME_CLOUD };
		stopwatchIcon = { IDB_PNG_STOPWATCH_NOMAL_THEME_CLOUD, IDB_PNG_STOPWATCH_HOVER_THEME_CLOUD, IDB_PNG_STOPWATCH_CLICK_THEME_CLOUD };
		converterIcon = { IDB_PNG_CONVERTER_NOMAL_THEME_CLOUD, IDB_PNG_CONVERTER_HOVER_THEME_CLOUD, IDB_PNG_CONVERTER_CLICK_THEME_CLOUD };
		datecalIcon = { IDB_PNG_DATECAL_NOMAL_THEME_CLOUD, IDB_PNG_DATECAL_HOVER_THEME_CLOUD, IDB_PNG_DATECAL_CLICK_THEME_CLOUD };
		worktimerIcon = { IDB_PNG_WORKTIMER_NOMAL_THEME_CLOUD, IDB_PNG_WORKTIMER_HOVER_THEME_CLOUD, IDB_PNG_WORKTIMER_CLICK_THEME_CLOUD };
		notepadIcon = { IDB_PNG_NOTEPAD_NOMAL_THEME_CLOUD, IDB_PNG_NOTEPAD_HOVER_THEME_CLOUD, IDB_PNG_NOTEPAD_CLICK_THEME_CLOUD };
		basetimerIcon = { IDB_PNG_BASETIMER_NOMAL_THEME_CLOUD, IDB_PNG_BASETIMER_HOVER_THEME_CLOUD, IDB_PNG_BASETIMER_CLICK_THEME_CLOUD };
		worldclockIcon = { IDB_PNG_WORLDCLOCK_NOMAL_THEME_CLOUD, IDB_PNG_WORLDCLOCK_HOVER_THEME_CLOUD, IDB_PNG_WORLDCLOCK_CLICK_THEME_CLOUD };
		textColor = RGB(20, 27, 37);
		functionBkColor = RGB(99, 177, 198);
		functionSubColor = RGB(118, 189, 207);
		functionSubSubColor = RGB(137, 202, 217);
		functionRectBorderColor = RGB(255, 255, 255);
		buttonColor = RGB(147, 212, 227);
		nCommingSoonIconID = IDB_PNG_COMINGSOON_THEME_CLOUD;
		nMainBkIconID = IDB_BITMAP_MAIN_BK_THEME_CLOUD;
	}
}

ThemeData::~ThemeData()
{

}

CString ThemeData::GetThemeName()
{
	return strThemeName;
}

ThemeData::FunctionIcon ThemeData::GetBaseIcon()
{
	return baseIcon;
}

ThemeData::FunctionIcon ThemeData::GetEngineeringIcon()
{
	return engineeringIcon;
}

ThemeData::FunctionIcon ThemeData::GetStopWatchIcon()
{
	return stopwatchIcon;
}

ThemeData::FunctionIcon ThemeData::GetConverterIcon()
{
	return converterIcon;
}

ThemeData::FunctionIcon ThemeData::GetDateCalIcon()
{
	return datecalIcon;
}

ThemeData::FunctionIcon ThemeData::GetWorkTimerIcon()
{
	return worktimerIcon;
}

ThemeData::FunctionIcon ThemeData::GetNotePadIcon()
{
	return notepadIcon;
}

ThemeData::FunctionIcon ThemeData::GetBaseTimerIcon()
{
	return basetimerIcon;
}

ThemeData::FunctionIcon ThemeData::GetWorldClockIcon()
{
	return worldclockIcon;
}

COLORREF ThemeData::GetTextColor()
{
	return textColor;
}

COLORREF ThemeData::GetFunctionBkColor()
{
	return functionBkColor;
}

COLORREF ThemeData::GetFunctionSubColor()
{
	return functionSubColor;
}

COLORREF ThemeData::GetFunctionSubSubColor()
{
	return functionSubSubColor;
}

COLORREF ThemeData::GetFunctionRectBorderColor()
{
	return functionRectBorderColor;
}

COLORREF ThemeData::GetButtonColor()
{
	return buttonColor;
}

int ThemeData::GetCommingSoonIconID()
{
	return nCommingSoonIconID;
}

int ThemeData::GetMainBkIconID()
{
	return nMainBkIconID;
}
