#pragma once
#include "atlstr.h"

/* 완료한 국가
아시아
-우즈베키스탄
-파키스탄
-카자흐스탄
-인도
-미얀마
-몽골
-중국
-대만
-필리핀
-인도네시아
-북한
-대한민국
-일본
유럽
-러시아
*/
enum GreenWichWorldClockData
{
	RUSIA_MOSKVA = 201,
	UZBEKISTAN_TASHKENT = 401,	
	PAKISTAN_ISLAMABAD = 402,
	KAZAKHSTAN_NURSULTAN = 501,
	INDIA_NEWDELHI = 551,
	MYANMAR_NAEPIDO = 651,
	MONGOLIA_ULAANBAATAR = 701,
	CHINA_BEIJING = 702,
	TAIWAN_TAIPEI = 703,
	PHILIPPINES_MANILA = 704,
	INDONESIA_JAKARTA = 705,
	NORTH_KOREA_PYONGYANG = 801,
	SOUTH_KOREA_SEOUL = 802,
	JAPAN_TOKYO = 803,
};

CString GetWorldCityName(GreenWichWorldClockData cwcd)
{
	CString strReturnCityName = _T("");
	if		(cwcd == UZBEKISTAN_TASHKENT) strReturnCityName = _T("우즈베키스탄 타슈켄트");
	else if (cwcd == PAKISTAN_ISLAMABAD) strReturnCityName = _T("파키스탄 이슬라마바드");
	else if (cwcd == KAZAKHSTAN_NURSULTAN) strReturnCityName = _T("카자흐스탄 누르술탄");
	else if (cwcd == INDIA_NEWDELHI) strReturnCityName = _T("인도 뉴델리");
	else if (cwcd == MYANMAR_NAEPIDO) strReturnCityName = _T("미얀마 네피도");
	else if (cwcd == MONGOLIA_ULAANBAATAR) strReturnCityName = _T("몽골 울란바토르");
	else if (cwcd == CHINA_BEIJING) strReturnCityName = _T("중국 베이징");
	else if (cwcd == TAIWAN_TAIPEI) strReturnCityName = _T("대만 타이베이");
	else if (cwcd == PHILIPPINES_MANILA) strReturnCityName = _T("필리핀 마닐라");
	else if (cwcd == INDONESIA_JAKARTA) strReturnCityName = _T("인도네시아 자카르타");
	else if (cwcd == NORTH_KOREA_PYONGYANG) strReturnCityName = _T("북한 평양");
	else if (cwcd == SOUTH_KOREA_SEOUL) strReturnCityName = _T("대한민국 서울");
	else if (cwcd == JAPAN_TOKYO) strReturnCityName = _T("일본 도쿄");
	else if (cwcd == RUSIA_MOSKVA) strReturnCityName = _T("러시아 모스크바");
}