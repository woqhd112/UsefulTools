#include "pch.h"
#pragma warning (disable : 4819)
#include "Resource.h"
#include "ThemeData.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

ThemeData::ThemeData(int nThemeFlags)
{
	if (nThemeFlags == THEME_DETECTIVE)
	{
		strThemeName = _T("사건 테마");
		this->nThemeFlags = nThemeFlags;
		themeButtonIcon = { IDB_PNG_CHANGE_NOMAL_THEME_DETECTIVE, IDB_PNG_CHANGE_HOVER_THEME_DETECTIVE, IDB_PNG_CHANGE_CLICK_THEME_DETECTIVE };
		baseIcon = { IDB_PNG_BASE_NOMAL_THEME_DETECTIVE, IDB_PNG_BASE_HOVER_THEME_DETECTIVE, IDB_PNG_BASE_CLICK_THEME_DETECTIVE };
		engineeringIcon = { IDB_PNG_ENGINEERING_NOMAL_THEME_DETECTIVE, IDB_PNG_ENGINEERING_HOVER_THEME_DETECTIVE, IDB_PNG_ENGINEERING_CLICK_THEME_DETECTIVE };
		stopwatchIcon = { IDB_PNG_STOPWATCH_NOMAL_THEME_DETECTIVE, IDB_PNG_STOPWATCH_HOVER_THEME_DETECTIVE, IDB_PNG_STOPWATCH_CLICK_THEME_DETECTIVE };
		converterIcon = { IDB_PNG_CONVERTER_NOMAL_THEME_DETECTIVE, IDB_PNG_CONVERTER_HOVER_THEME_DETECTIVE, IDB_PNG_CONVERTER_CLICK_THEME_DETECTIVE };
		datecalIcon = { IDB_PNG_DATECAL_NOMAL_THEME_DETECTIVE, IDB_PNG_DATECAL_HOVER_THEME_DETECTIVE, IDB_PNG_DATECAL_CLICK_THEME_DETECTIVE };
		worktimerIcon = { IDB_PNG_WORKTIMER_NOMAL_THEME_DETECTIVE, IDB_PNG_WORKTIMER_HOVER_THEME_DETECTIVE, IDB_PNG_WORKTIMER_CLICK_THEME_DETECTIVE };
		notepadIcon = { IDB_PNG_NOTEPAD_NOMAL_THEME_DETECTIVE, IDB_PNG_NOTEPAD_HOVER_THEME_DETECTIVE, IDB_PNG_NOTEPAD_CLICK_THEME_DETECTIVE };
		basetimerIcon = { IDB_PNG_BASETIMER_NOMAL_THEME_DETECTIVE, IDB_PNG_BASETIMER_HOVER_THEME_DETECTIVE, IDB_PNG_BASETIMER_CLICK_THEME_DETECTIVE };
		worldclockIcon = { IDB_PNG_WORLDCLOCK_NOMAL_THEME_DETECTIVE, IDB_PNG_WORLDCLOCK_HOVER_THEME_DETECTIVE, IDB_PNG_WORLDCLOCK_CLICK_THEME_DETECTIVE };
		scrollIcon = { IDB_PNG_SCROLL_NONSIGNAL_THEME_DETECTIVE, IDB_PNG_SCROLL_SIGNAL_THEME_DETECTIVE, IDB_PNG_SCROLL_NONSIGNAL_THEME_DETECTIVE };
		commingSoonIcon = { IDB_PNG_COMINGSOON_THEME_DETECTIVE, IDB_PNG_COMINGSOON_THEME_DETECTIVE, IDB_PNG_COMINGSOON_THEME_DETECTIVE };
		textColor = RGB(255, 255, 255);
		functionTextColor = RGB(0, 0, 0);
		functionBkColor = RGB(0, 0, 0);//RGB(49, 20, 6);
		functionSubColor = RGB(255, 255, 255);//RGB(77, 32, 11);
		rectBorderColor = RGB(255, 255, 255);
		functionRectBorderColor = RGB(0, 0, 0);
		buttonColor = RGB(50, 50, 50);
		nSettingThemeBkIconID = IDB_BITMAP_CHOICE_BK_THEME_DETECTIVE;
		nMainBkIconID = IDB_BITMAP_MAIN_BK_THEME_DETECTIVE;
		nMainTimePosMargin = THEME_MAIN_TIME_POS_UP;
	}
	else if (nThemeFlags == THEME_CLOUD)
	{
		strThemeName = _T("구름 테마");
		this->nThemeFlags = nThemeFlags;
		themeButtonIcon = { IDB_PNG_CHANGE_NOMAL_THEME_CLOUD, IDB_PNG_CHANGE_HOVER_THEME_CLOUD, IDB_PNG_CHANGE_CLICK_THEME_CLOUD };
		baseIcon = { IDB_PNG_BASE_NOMAL_THEME_CLOUD, IDB_PNG_BASE_HOVER_THEME_CLOUD, IDB_PNG_BASE_CLICK_THEME_CLOUD };
		engineeringIcon = { IDB_PNG_ENGINEERING_NOMAL_THEME_CLOUD, IDB_PNG_ENGINEERING_HOVER_THEME_CLOUD, IDB_PNG_ENGINEERING_CLICK_THEME_CLOUD };
		stopwatchIcon = { IDB_PNG_STOPWATCH_NOMAL_THEME_CLOUD, IDB_PNG_STOPWATCH_HOVER_THEME_CLOUD, IDB_PNG_STOPWATCH_CLICK_THEME_CLOUD };
		converterIcon = { IDB_PNG_CONVERTER_NOMAL_THEME_CLOUD, IDB_PNG_CONVERTER_HOVER_THEME_CLOUD, IDB_PNG_CONVERTER_CLICK_THEME_CLOUD };
		datecalIcon = { IDB_PNG_DATECAL_NOMAL_THEME_CLOUD, IDB_PNG_DATECAL_HOVER_THEME_CLOUD, IDB_PNG_DATECAL_CLICK_THEME_CLOUD };
		worktimerIcon = { IDB_PNG_WORKTIMER_NOMAL_THEME_CLOUD, IDB_PNG_WORKTIMER_HOVER_THEME_CLOUD, IDB_PNG_WORKTIMER_CLICK_THEME_CLOUD };
		notepadIcon = { IDB_PNG_NOTEPAD_NOMAL_THEME_CLOUD, IDB_PNG_NOTEPAD_HOVER_THEME_CLOUD, IDB_PNG_NOTEPAD_CLICK_THEME_CLOUD };
		basetimerIcon = { IDB_PNG_BASETIMER_NOMAL_THEME_CLOUD, IDB_PNG_BASETIMER_HOVER_THEME_CLOUD, IDB_PNG_BASETIMER_CLICK_THEME_CLOUD };
		worldclockIcon = { IDB_PNG_WORLDCLOCK_NOMAL_THEME_CLOUD, IDB_PNG_WORLDCLOCK_HOVER_THEME_CLOUD, IDB_PNG_WORLDCLOCK_CLICK_THEME_CLOUD };
		scrollIcon = { IDB_PNG_SCROLL_NONSIGNAL_THEME_CLOUD, IDB_PNG_SCROLL_SIGNAL_THEME_CLOUD, IDB_PNG_SCROLL_NONSIGNAL_THEME_CLOUD };
		commingSoonIcon = { IDB_PNG_COMINGSOON_THEME_CLOUD, IDB_PNG_COMINGSOON_THEME_CLOUD, IDB_PNG_COMINGSOON_THEME_CLOUD };
		textColor = RGB(44, 51, 61);
		functionTextColor = RGB(81, 153, 177);
		functionBkColor = RGB(99, 177, 198);
		functionSubColor = RGB(255, 255, 255);
		rectBorderColor = RGB(255, 255, 255);
		functionRectBorderColor = RGB(99, 177, 198);
		buttonColor = RGB(147, 212, 227);
		nSettingThemeBkIconID = IDB_BITMAP_CHOICE_BK_THEME_CLOUD;
		nMainBkIconID = IDB_BITMAP_MAIN_BK_THEME_CLOUD;
		nMainTimePosMargin = THEME_MAIN_TIME_POS_UP;
	}
	else if (nThemeFlags == THEME_LIGHT)
	{
		strThemeName = _T("조명 테마");
		this->nThemeFlags = nThemeFlags;
		themeButtonIcon = { IDB_PNG_CHANGE_NOMAL_THEME_LIGHT, IDB_PNG_CHANGE_HOVER_THEME_LIGHT, IDB_PNG_CHANGE_CLICK_THEME_LIGHT };
		baseIcon = { IDB_PNG_BASE_NOMAL_THEME_LIGHT, IDB_PNG_BASE_HOVER_THEME_LIGHT, IDB_PNG_BASE_CLICK_THEME_LIGHT };
		engineeringIcon = { IDB_PNG_ENGINEERING_NOMAL_THEME_LIGHT, IDB_PNG_ENGINEERING_HOVER_THEME_LIGHT, IDB_PNG_ENGINEERING_CLICK_THEME_LIGHT };
		stopwatchIcon = { IDB_PNG_STOPWATCH_NOMAL_THEME_LIGHT, IDB_PNG_STOPWATCH_HOVER_THEME_LIGHT, IDB_PNG_STOPWATCH_CLICK_THEME_LIGHT };
		converterIcon = { IDB_PNG_CONVERTER_NOMAL_THEME_LIGHT, IDB_PNG_CONVERTER_HOVER_THEME_LIGHT, IDB_PNG_CONVERTER_CLICK_THEME_LIGHT };
		datecalIcon = { IDB_PNG_DATECAL_NOMAL_THEME_LIGHT, IDB_PNG_DATECAL_HOVER_THEME_LIGHT, IDB_PNG_DATECAL_CLICK_THEME_LIGHT };
		worktimerIcon = { IDB_PNG_WORKTIMER_NOMAL_THEME_LIGHT, IDB_PNG_WORKTIMER_HOVER_THEME_LIGHT, IDB_PNG_WORKTIMER_CLICK_THEME_LIGHT };
		notepadIcon = { IDB_PNG_NOTEPAD_NOMAL_THEME_LIGHT, IDB_PNG_NOTEPAD_HOVER_THEME_LIGHT, IDB_PNG_NOTEPAD_CLICK_THEME_LIGHT };
		basetimerIcon = { IDB_PNG_BASETIMER_NOMAL_THEME_LIGHT, IDB_PNG_BASETIMER_HOVER_THEME_LIGHT, IDB_PNG_BASETIMER_CLICK_THEME_LIGHT };
		worldclockIcon = { IDB_PNG_WORLDCLOCK_NOMAL_THEME_LIGHT, IDB_PNG_WORLDCLOCK_HOVER_THEME_LIGHT, IDB_PNG_WORLDCLOCK_CLICK_THEME_LIGHT };
		scrollIcon = { IDB_PNG_SCROLL_NONSIGNAL_THEME_LIGHT, IDB_PNG_SCROLL_SIGNAL_THEME_LIGHT, IDB_PNG_SCROLL_NONSIGNAL_THEME_LIGHT };
		commingSoonIcon = { IDB_PNG_COMINGSOON_THEME_LIGHT, IDB_PNG_COMINGSOON_THEME_LIGHT, IDB_PNG_COMINGSOON_THEME_LIGHT };
		textColor = RGB(217, 183, 130);
		functionTextColor = RGB(21, 20, 20);
		functionBkColor = RGB(21, 20, 20); 
		functionSubColor = RGB(77, 40, 30); 
		rectBorderColor = RGB(77, 40, 30);
		functionRectBorderColor = RGB(21, 20, 20);
		buttonColor = RGB(80, 59, 43);	//130, 109, 93
		nSettingThemeBkIconID = IDB_BITMAP_CHOICE_BK_THEME_LIGHT;
		nMainBkIconID = IDB_BITMAP_MAIN_BK_THEME_LIGHT;
		nMainTimePosMargin = THEME_MAIN_TIME_POS_DOWN;
	}
	else if (nThemeFlags == THEME_MAGNIFIER)
	{
		strThemeName = _T("돋보기 테마");
		this->nThemeFlags = nThemeFlags;
		themeButtonIcon = { IDB_PNG_CHANGE_NOMAL_THEME_MAGNIFIER, IDB_PNG_CHANGE_HOVER_THEME_MAGNIFIER, IDB_PNG_CHANGE_CLICK_THEME_MAGNIFIER };
		baseIcon = { IDB_PNG_BASE_NOMAL_THEME_MAGNIFIER, IDB_PNG_BASE_HOVER_THEME_MAGNIFIER, IDB_PNG_BASE_CLICK_THEME_MAGNIFIER };
		engineeringIcon = { IDB_PNG_ENGINEERING_NOMAL_THEME_MAGNIFIER, IDB_PNG_ENGINEERING_HOVER_THEME_MAGNIFIER, IDB_PNG_ENGINEERING_CLICK_THEME_MAGNIFIER };
		stopwatchIcon = { IDB_PNG_STOPWATCH_NOMAL_THEME_MAGNIFIER, IDB_PNG_STOPWATCH_HOVER_THEME_MAGNIFIER, IDB_PNG_STOPWATCH_CLICK_THEME_MAGNIFIER };
		converterIcon = { IDB_PNG_CONVERTER_NOMAL_THEME_MAGNIFIER, IDB_PNG_CONVERTER_HOVER_THEME_MAGNIFIER, IDB_PNG_CONVERTER_CLICK_THEME_MAGNIFIER };
		datecalIcon = { IDB_PNG_DATECAL_NOMAL_THEME_MAGNIFIER, IDB_PNG_DATECAL_HOVER_THEME_MAGNIFIER, IDB_PNG_DATECAL_CLICK_THEME_MAGNIFIER };
		worktimerIcon = { IDB_PNG_WORKTIMER_NOMAL_THEME_MAGNIFIER, IDB_PNG_WORKTIMER_HOVER_THEME_MAGNIFIER, IDB_PNG_WORKTIMER_CLICK_THEME_MAGNIFIER };
		notepadIcon = { IDB_PNG_NOTEPAD_NOMAL_THEME_MAGNIFIER, IDB_PNG_NOTEPAD_HOVER_THEME_MAGNIFIER, IDB_PNG_NOTEPAD_CLICK_THEME_MAGNIFIER };
		basetimerIcon = { IDB_PNG_BASETIMER_NOMAL_THEME_MAGNIFIER, IDB_PNG_BASETIMER_HOVER_THEME_MAGNIFIER, IDB_PNG_BASETIMER_CLICK_THEME_MAGNIFIER };
		worldclockIcon = { IDB_PNG_WORLDCLOCK_NOMAL_THEME_MAGNIFIER, IDB_PNG_WORLDCLOCK_HOVER_THEME_MAGNIFIER, IDB_PNG_WORLDCLOCK_CLICK_THEME_MAGNIFIER };
		scrollIcon = { IDB_PNG_SCROLL_NONSIGNAL_THEME_MAGNIFIER, IDB_PNG_SCROLL_SIGNAL_THEME_MAGNIFIER, IDB_PNG_SCROLL_NONSIGNAL_THEME_MAGNIFIER };
		commingSoonIcon = { IDB_PNG_COMINGSOON_THEME_MAGNIFIER, IDB_PNG_COMINGSOON_THEME_MAGNIFIER, IDB_PNG_COMINGSOON_THEME_MAGNIFIER };
		textColor = RGB(3, 3, 3);
		functionTextColor = RGB(255, 255, 255);
		functionBkColor = RGB(133, 118, 102);
		functionSubColor = RGB(3, 3, 3);
		rectBorderColor = RGB(3, 3, 3);
		functionRectBorderColor = RGB(255, 255, 255);
		buttonColor = RGB(134, 120, 104);
		nSettingThemeBkIconID = IDB_BITMAP_CHOICE_BK_THEME_MAGNIFIER;
		nMainBkIconID = IDB_BITMAP_MAIN_BK_THEME_MAGNIFIER;
		nMainTimePosMargin = THEME_MAIN_TIME_POS_DOWN;
	}
	else if (nThemeFlags == THEME_INK)
	{
		strThemeName = _T("수묵 테마");
		this->nThemeFlags = nThemeFlags;
		themeButtonIcon = { IDB_PNG_CHANGE_NOMAL_THEME_INK, IDB_PNG_CHANGE_HOVER_THEME_INK, IDB_PNG_CHANGE_CLICK_THEME_INK };
		baseIcon = { IDB_PNG_BASE_NOMAL_THEME_INK, IDB_PNG_BASE_HOVER_THEME_INK, IDB_PNG_BASE_CLICK_THEME_INK };
		engineeringIcon = { IDB_PNG_ENGINEERING_NOMAL_THEME_INK, IDB_PNG_ENGINEERING_HOVER_THEME_INK, IDB_PNG_ENGINEERING_CLICK_THEME_INK };
		stopwatchIcon = { IDB_PNG_STOPWATCH_NOMAL_THEME_INK, IDB_PNG_STOPWATCH_HOVER_THEME_INK, IDB_PNG_STOPWATCH_CLICK_THEME_INK };
		converterIcon = { IDB_PNG_CONVERTER_NOMAL_THEME_INK, IDB_PNG_CONVERTER_HOVER_THEME_INK, IDB_PNG_CONVERTER_CLICK_THEME_INK };
		datecalIcon = { IDB_PNG_DATECAL_NOMAL_THEME_INK, IDB_PNG_DATECAL_HOVER_THEME_INK, IDB_PNG_DATECAL_CLICK_THEME_INK };
		worktimerIcon = { IDB_PNG_WORKTIMER_NOMAL_THEME_INK, IDB_PNG_WORKTIMER_HOVER_THEME_INK, IDB_PNG_WORKTIMER_CLICK_THEME_INK };
		notepadIcon = { IDB_PNG_NOTEPAD_NOMAL_THEME_INK, IDB_PNG_NOTEPAD_HOVER_THEME_INK, IDB_PNG_NOTEPAD_CLICK_THEME_INK };
		basetimerIcon = { IDB_PNG_BASETIMER_NOMAL_THEME_INK, IDB_PNG_BASETIMER_HOVER_THEME_INK, IDB_PNG_BASETIMER_CLICK_THEME_INK };
		worldclockIcon = { IDB_PNG_WORLDCLOCK_NOMAL_THEME_INK, IDB_PNG_WORLDCLOCK_HOVER_THEME_INK, IDB_PNG_WORLDCLOCK_CLICK_THEME_INK };
		scrollIcon = { IDB_PNG_SCROLL_NONSIGNAL_THEME_INK, IDB_PNG_SCROLL_SIGNAL_THEME_INK, IDB_PNG_SCROLL_NONSIGNAL_THEME_INK };
		commingSoonIcon = { IDB_PNG_COMINGSOON_THEME_INK, IDB_PNG_COMINGSOON_THEME_INK, IDB_PNG_COMINGSOON_THEME_INK };
		textColor = RGB(17, 17, 17);
		functionTextColor = RGB(238, 238, 238);
		functionBkColor = RGB(238, 238, 238);
		functionSubColor = RGB(17, 17, 17);
		rectBorderColor = RGB(17, 17, 17);
		functionRectBorderColor = RGB(238, 238, 238);
		buttonColor = RGB(115, 115, 115);
		nSettingThemeBkIconID = IDB_BITMAP_CHOICE_BK_THEME_INK;
		nMainBkIconID = IDB_BITMAP_MAIN_BK_THEME_INK;
		nMainTimePosMargin = THEME_MAIN_TIME_POS_UP;
	}
	else if (nThemeFlags == THEME_WATERDROP)
	{
		strThemeName = _T("물방울 테마");
		this->nThemeFlags = nThemeFlags;
		themeButtonIcon = { IDB_PNG_CHANGE_NOMAL_THEME_WATERDROP, IDB_PNG_CHANGE_HOVER_THEME_WATERDROP, IDB_PNG_CHANGE_CLICK_THEME_WATERDROP };
		baseIcon = { IDB_PNG_BASE_NOMAL_THEME_WATERDROP, IDB_PNG_BASE_HOVER_THEME_WATERDROP, IDB_PNG_BASE_CLICK_THEME_WATERDROP };
		engineeringIcon = { IDB_PNG_ENGINEERING_NOMAL_THEME_WATERDROP, IDB_PNG_ENGINEERING_HOVER_THEME_WATERDROP, IDB_PNG_ENGINEERING_CLICK_THEME_WATERDROP };
		stopwatchIcon = { IDB_PNG_STOPWATCH_NOMAL_THEME_WATERDROP, IDB_PNG_STOPWATCH_HOVER_THEME_WATERDROP, IDB_PNG_STOPWATCH_CLICK_THEME_WATERDROP };
		converterIcon = { IDB_PNG_CONVERTER_NOMAL_THEME_WATERDROP, IDB_PNG_CONVERTER_HOVER_THEME_WATERDROP, IDB_PNG_CONVERTER_CLICK_THEME_WATERDROP };
		datecalIcon = { IDB_PNG_DATECAL_NOMAL_THEME_WATERDROP, IDB_PNG_DATECAL_HOVER_THEME_WATERDROP, IDB_PNG_DATECAL_CLICK_THEME_WATERDROP };
		worktimerIcon = { IDB_PNG_WORKTIMER_NOMAL_THEME_WATERDROP, IDB_PNG_WORKTIMER_HOVER_THEME_WATERDROP, IDB_PNG_WORKTIMER_CLICK_THEME_WATERDROP };
		notepadIcon = { IDB_PNG_NOTEPAD_NOMAL_THEME_WATERDROP, IDB_PNG_NOTEPAD_HOVER_THEME_WATERDROP, IDB_PNG_NOTEPAD_CLICK_THEME_WATERDROP };
		basetimerIcon = { IDB_PNG_BASETIMER_NOMAL_THEME_WATERDROP, IDB_PNG_BASETIMER_HOVER_THEME_WATERDROP, IDB_PNG_BASETIMER_CLICK_THEME_WATERDROP };
		worldclockIcon = { IDB_PNG_WORLDCLOCK_NOMAL_THEME_WATERDROP, IDB_PNG_WORLDCLOCK_HOVER_THEME_WATERDROP, IDB_PNG_WORLDCLOCK_CLICK_THEME_WATERDROP };
		scrollIcon = { IDB_PNG_SCROLL_NONSIGNAL_THEME_WATERDROP, IDB_PNG_SCROLL_SIGNAL_THEME_WATERDROP, IDB_PNG_SCROLL_NONSIGNAL_THEME_WATERDROP };
		commingSoonIcon = { IDB_PNG_COMINGSOON_THEME_WATERDROP, IDB_PNG_COMINGSOON_THEME_WATERDROP, IDB_PNG_COMINGSOON_THEME_WATERDROP };
		textColor = RGB(44, 14, 26);
		functionTextColor = RGB(71, 111, 134);
		functionBkColor = RGB(95, 183, 206);
		functionSubColor = RGB(242, 155, 136);
		rectBorderColor = RGB(254, 249, 229);
		functionRectBorderColor = RGB(44, 14, 26);
		buttonColor = RGB(115, 115, 115);
		nSettingThemeBkIconID = IDB_BITMAP_CHOICE_BK_THEME_WATERDROP;
		nMainBkIconID = IDB_BITMAP_MAIN_BK_THEME_WATERDROP;
		nMainTimePosMargin = THEME_MAIN_TIME_POS_DOWN;
	}
	else if (nThemeFlags == THEME_PLANET)
	{
		strThemeName = _T("행성 테마");
		this->nThemeFlags = nThemeFlags;
		themeButtonIcon = { IDB_PNG_CHANGE_NOMAL_THEME_PLANET, IDB_PNG_CHANGE_HOVER_THEME_PLANET, IDB_PNG_CHANGE_CLICK_THEME_PLANET };
		baseIcon = { IDB_PNG_BASE_NOMAL_THEME_PLANET, IDB_PNG_BASE_HOVER_THEME_PLANET, IDB_PNG_BASE_CLICK_THEME_PLANET };
		engineeringIcon = { IDB_PNG_ENGINEERING_NOMAL_THEME_PLANET, IDB_PNG_ENGINEERING_HOVER_THEME_PLANET, IDB_PNG_ENGINEERING_CLICK_THEME_PLANET };
		stopwatchIcon = { IDB_PNG_STOPWATCH_NOMAL_THEME_PLANET, IDB_PNG_STOPWATCH_HOVER_THEME_PLANET, IDB_PNG_STOPWATCH_CLICK_THEME_PLANET };
		converterIcon = { IDB_PNG_CONVERTER_NOMAL_THEME_PLANET, IDB_PNG_CONVERTER_HOVER_THEME_PLANET, IDB_PNG_CONVERTER_CLICK_THEME_PLANET };
		datecalIcon = { IDB_PNG_DATECAL_NOMAL_THEME_PLANET, IDB_PNG_DATECAL_HOVER_THEME_PLANET, IDB_PNG_DATECAL_CLICK_THEME_PLANET };
		worktimerIcon = { IDB_PNG_WORKTIMER_NOMAL_THEME_PLANET, IDB_PNG_WORKTIMER_HOVER_THEME_PLANET, IDB_PNG_WORKTIMER_CLICK_THEME_PLANET };
		notepadIcon = { IDB_PNG_NOTEPAD_NOMAL_THEME_PLANET, IDB_PNG_NOTEPAD_HOVER_THEME_PLANET, IDB_PNG_NOTEPAD_CLICK_THEME_PLANET };
		basetimerIcon = { IDB_PNG_BASETIMER_NOMAL_THEME_PLANET, IDB_PNG_BASETIMER_HOVER_THEME_PLANET, IDB_PNG_BASETIMER_CLICK_THEME_PLANET };
		worldclockIcon = { IDB_PNG_WORLDCLOCK_NOMAL_THEME_PLANET, IDB_PNG_WORLDCLOCK_HOVER_THEME_PLANET, IDB_PNG_WORLDCLOCK_CLICK_THEME_PLANET };
		scrollIcon = { IDB_PNG_SCROLL_NONSIGNAL_THEME_PLANET, IDB_PNG_SCROLL_SIGNAL_THEME_PLANET, IDB_PNG_SCROLL_NONSIGNAL_THEME_PLANET };
		commingSoonIcon = { IDB_PNG_COMINGSOON_THEME_PLANET, IDB_PNG_COMINGSOON_THEME_PLANET, IDB_PNG_COMINGSOON_THEME_PLANET };
		textColor = RGB(251, 246, 227);
		functionTextColor = RGB(0, 0, 0);
		functionBkColor = RGB(0, 0, 0);
		functionSubColor = RGB(90, 1, 1);
		rectBorderColor = RGB(159, 24, 1);
		functionRectBorderColor = RGB(251, 246, 227);
		buttonColor = RGB(180, 2, 2);
		nSettingThemeBkIconID = IDB_BITMAP_CHOICE_BK_THEME_PLANET;
		nMainBkIconID = IDB_BITMAP_MAIN_BK_THEME_PLANET;
		nMainTimePosMargin = THEME_MAIN_TIME_POS_UP;
	}
	else if (nThemeFlags == THEME_NEONSIGN)
	{
		strThemeName = _T("네온 테마");
		this->nThemeFlags = nThemeFlags;
		themeButtonIcon = { IDB_PNG_CHANGE_NOMAL_THEME_NEONSIGN, IDB_PNG_CHANGE_HOVER_THEME_NEONSIGN, IDB_PNG_CHANGE_CLICK_THEME_NEONSIGN };
		baseIcon = { IDB_PNG_BASE_NOMAL_THEME_NEONSIGN, IDB_PNG_BASE_HOVER_THEME_NEONSIGN, IDB_PNG_BASE_CLICK_THEME_NEONSIGN };
		engineeringIcon = { IDB_PNG_ENGINEERING_NOMAL_THEME_NEONSIGN, IDB_PNG_ENGINEERING_HOVER_THEME_NEONSIGN, IDB_PNG_ENGINEERING_CLICK_THEME_NEONSIGN };
		stopwatchIcon = { IDB_PNG_STOPWATCH_NOMAL_THEME_NEONSIGN, IDB_PNG_STOPWATCH_HOVER_THEME_NEONSIGN, IDB_PNG_STOPWATCH_CLICK_THEME_NEONSIGN };
		converterIcon = { IDB_PNG_CONVERTER_NOMAL_THEME_NEONSIGN, IDB_PNG_CONVERTER_HOVER_THEME_NEONSIGN, IDB_PNG_CONVERTER_CLICK_THEME_NEONSIGN };
		datecalIcon = { IDB_PNG_DATECAL_NOMAL_THEME_NEONSIGN, IDB_PNG_DATECAL_HOVER_THEME_NEONSIGN, IDB_PNG_DATECAL_CLICK_THEME_NEONSIGN };
		worktimerIcon = { IDB_PNG_WORKTIMER_NOMAL_THEME_NEONSIGN, IDB_PNG_WORKTIMER_HOVER_THEME_NEONSIGN, IDB_PNG_WORKTIMER_CLICK_THEME_NEONSIGN };
		notepadIcon = { IDB_PNG_NOTEPAD_NOMAL_THEME_NEONSIGN, IDB_PNG_NOTEPAD_HOVER_THEME_NEONSIGN, IDB_PNG_NOTEPAD_CLICK_THEME_NEONSIGN };
		basetimerIcon = { IDB_PNG_BASETIMER_NOMAL_THEME_NEONSIGN, IDB_PNG_BASETIMER_HOVER_THEME_NEONSIGN, IDB_PNG_BASETIMER_CLICK_THEME_NEONSIGN };
		worldclockIcon = { IDB_PNG_WORLDCLOCK_NOMAL_THEME_NEONSIGN, IDB_PNG_WORLDCLOCK_HOVER_THEME_NEONSIGN, IDB_PNG_WORLDCLOCK_CLICK_THEME_NEONSIGN };
		scrollIcon = { IDB_PNG_SCROLL_NONSIGNAL_THEME_NEONSIGN, IDB_PNG_SCROLL_SIGNAL_THEME_NEONSIGN, IDB_PNG_SCROLL_NONSIGNAL_THEME_NEONSIGN };
		commingSoonIcon = { IDB_PNG_COMINGSOON_THEME_NEONSIGN, IDB_PNG_COMINGSOON_THEME_NEONSIGN, IDB_PNG_COMINGSOON_THEME_NEONSIGN };
		textColor = RGB(154, 232, 215);
		functionTextColor = RGB(255, 255, 255);
		functionBkColor = RGB(1, 3, 2);
		functionSubColor = RGB(5, 37, 26);
		rectBorderColor = RGB(159, 24, 1);
		functionRectBorderColor = RGB(154, 232, 215);
		buttonColor = RGB(159, 24, 1);
		nSettingThemeBkIconID = IDB_BITMAP_CHOICE_BK_THEME_NEONSIGN;
		nMainBkIconID = IDB_BITMAP_MAIN_BK_THEME_NEONSIGN;
		nMainTimePosMargin = THEME_MAIN_TIME_POS_UP;
	}
}

ThemeData::~ThemeData()
{

}

int ThemeData::GetThemeFlags() const
{
	return nThemeFlags;
}

CString ThemeData::GetThemeName() const
{
	return strThemeName;
}

ThemeData::FunctionIcon ThemeData::GetThemeButtonIcon() const
{
	return themeButtonIcon;
}

ThemeData::FunctionIcon ThemeData::GetBaseIcon() const
{
	return baseIcon;
}

ThemeData::FunctionIcon ThemeData::GetEngineeringIcon() const
{
	return engineeringIcon;
}

ThemeData::FunctionIcon ThemeData::GetStopWatchIcon() const
{
	return stopwatchIcon;
}

ThemeData::FunctionIcon ThemeData::GetConverterIcon() const
{
	return converterIcon;
}

ThemeData::FunctionIcon ThemeData::GetDateCalIcon() const
{
	return datecalIcon;
}

ThemeData::FunctionIcon ThemeData::GetWorkTimerIcon() const
{
	return worktimerIcon;
}

ThemeData::FunctionIcon ThemeData::GetNotePadIcon() const
{
	return notepadIcon;
}

ThemeData::FunctionIcon ThemeData::GetBaseTimerIcon() const
{
	return basetimerIcon;
}

ThemeData::FunctionIcon ThemeData::GetWorldClockIcon() const
{
	return worldclockIcon;
}

ThemeData::FunctionIcon ThemeData::GetScrollIcon() const
{
	return scrollIcon;
}

COLORREF ThemeData::GetTextColor() const
{
	return textColor;
}

COLORREF ThemeData::GetFunctionTextColor() const
{
	return functionTextColor;
}

COLORREF ThemeData::GetFunctionBkColor() const
{
	return functionBkColor;
}

COLORREF ThemeData::GetFunctionSubColor() const
{
	return functionSubColor;
}

COLORREF ThemeData::GetRectBorderColor() const
{
	return rectBorderColor;
}

COLORREF ThemeData::GetFunctionRectBorderColor() const
{
	return functionRectBorderColor;
}

COLORREF ThemeData::GetButtonColor() const
{
	return buttonColor;
}

ThemeData::FunctionIcon ThemeData::GetCommingSoonIcon() const
{
	return commingSoonIcon;
}
 
int ThemeData::GetSettingThemeBkIconID() const
{
	return nSettingThemeBkIconID;
}

int ThemeData::GetMainBkIconID() const
{
	return nMainBkIconID;
}

int ThemeData::GetMainTimePosMargin() const
{
	return nMainTimePosMargin;
}
