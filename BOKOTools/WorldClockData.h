#pragma once
#include "atlstr.h"

/*
OECD 가입국 수도만 처리
-캐나다
-영국
-덴마크
-아이슬랜드
-노르웨이
-터키
-스페인
-포르투갈
-프랑스
-아일랜드
-벨기에
-독일
-스웨덴
-스위스
-오스트리아
-네덜란드
-룩셈부르크
-이탈리아
-일본
-핀란드
-호주
-뉴질랜드
-멕시코
-체코
-헝가리
-폴란드
-대한민국
-슬로바키아
-칠레
-슬로베니아
-이스라엘
-에스토니아
-라트비아
-리투아니아
-콜롬비아
-코스타리카
-러시아
-남아공
-브라질
-인도
-인도네시아
-중국

미가입국 일부
-대만
-필리핀
-북한

*/

enum GreenWichWorldClockData
{
	CANADA = 0,
	USA = 1,
	ENGLAND = 2,
	DENMARK  = 3,
	ISLAND = 4,
	NORWAY = 5,
	TURKEY = 6,
	SPAIN = 7,
	PORTUGAL = 8,
	FRANCE = 9,
	IRELAND = 10,
	BELGIUM = 11,
	GERMANY = 12,
	GREECE = 13,
	SWEDEN = 14,
	SWISS = 15,
	AUSTRIA = 16,
	NETHERLANDS = 17,
	LUXEMBOURG = 18,
	ITALY = 19,
	FINLAND = 21,
	AUSTRALIA = 22,
	NEWZEALAND = 23,
	MEXICO = 24,
	CZECH = 25,
	HUNGARY = 26,
	POLAND = 27,
	SLOVAKIA = 29,
	CHILE = 30,
	CLOVENIAN = 31,
	ISRAEL = 32,
	ESTONIA = 33,
	LATVIA = 34,
	LITHUANIA = 35,
	COLUMBIA = 36,
	COSTARICA = 37,
	SOUTHAFRICA = 39,
	BRAZIL = 40,
	RUSIA_MOSKVA = 201,
	INDIA_NEWDELHI = 551,
	CHINA_BEIJING = 702,
	TAIWAN_TAIPEI = 703,
	PHILIPPINES_MANILA = 704,
	INDONESIA_JAKARTA = 705,
	NORTHKOREA_PYONGYANG = 801,
	SOUTHKOREA_SEOUL = 802,
	JAPAN_TOKYO = 803,

};

CString GetWorldCityName(GreenWichWorldClockData cwcd)
{
	CString strReturnCityName = _T("");
	
	if (cwcd == INDIA_NEWDELHI) strReturnCityName = _T("인도 뉴델리");
	else if (cwcd == CHINA_BEIJING) strReturnCityName = _T("중국 베이징");
	else if (cwcd == TAIWAN_TAIPEI) strReturnCityName = _T("대만 타이베이");
	else if (cwcd == PHILIPPINES_MANILA) strReturnCityName = _T("필리핀 마닐라");
	else if (cwcd == INDONESIA_JAKARTA) strReturnCityName = _T("인도네시아 자카르타");
	else if (cwcd == NORTHKOREA_PYONGYANG) strReturnCityName = _T("북한 평양");
	else if (cwcd == SOUTHKOREA_SEOUL) strReturnCityName = _T("대한민국 서울");
	else if (cwcd == JAPAN_TOKYO) strReturnCityName = _T("일본 도쿄");
	else if (cwcd == RUSIA_MOSKVA) strReturnCityName = _T("러시아 모스크바");
}