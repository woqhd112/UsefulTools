#pragma once
#include "ThemeData.h"
#include "GeneralUtil.h"
#include "CalculateButton.h"
#include "CustomScroll.h"
#include <vector>

// WorldSearchList 대화 상자


class WorldSearchList : public CDialogEx
{
	DECLARE_DYNAMIC(WorldSearchList)

public:
	WorldSearchList(ThemeData* currentTheme, CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~WorldSearchList();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_SEARCH_LIST };
#endif

private:


	/*
	주요도시
	-호주 시드니
	-아랍에미리트 두바이
	-이탈리아 밀라노,베네치아,나폴리,피사
	-미국 뉴욕,로스엔젤레스,라스베이거스,애틀란타,시애틀,샌프란시스코,마이애미
	-캐나다 밴쿠버,토론토
	-브라질 상파울루
	-영국 옥스포드,리버풀,맨체스터
	-스페인 발렌시아,바르셀로나
	-프랑스 마르세유
	-독일 뮌헨
	-스위스 취리히
	*/
	enum GreenWichWorldClockData
	{
		COSTARICA_SANJOSE = -6602,				//
		MEXICO_MEXICOCITY = -6601,				//
		COLUMBIA_SANTAFEDEBOGOTA = -5503,		//
		USA_WASHINGTONDC = -5502,				//
		CANADA_OTTAWA = -5501,					//
		CHILE_SANTIAGO = -4401,					//
		BRAZIL_BRASILIA = -3001,				//
		IRELAND_DUBLIN = -1003,					//
		PORTUGAL_LISBON = -1002,				//
		ISLAND_REYKJAVIK = -1001,				//
		ENGLAND_LONDON = 1,						//
		DENMARK_COPENHAGEN = 2,					//
		NORWAY_OSLO = 3,						//
		SPAIN_MADRID = 4,						//
		FRANCE_PARIS = 5,						//
		BELGIUM_BRUSSELS = 6,					//
		GERMANY_BERLIN = 7,						//
		SWEDEN_STOCKHOLM = 8,					//
		SWISS_BERN = 9,							//
		AUSTRIA_WIEN = 10,						//
		NETHERLANDS_AMSTERDAM = 11,				//
		LUXEMBOURG_LUXEMBOURG = 12,				//
		ITALY_ROME = 13,						//
		CZECH_PRAGUE = 14,						//
		HUNGARY_BUDAPEST = 15,					//
		POLAND_WARSZAWA = 16,					//
		SLOVAKIA_BRATISLAVA = 17,				//
		SLOVENIA_LJUBLJANA = 18,				//
		GREECE_ATHENS = 1001,					//
		FINLAND_HELSINKI = 1002,				//
		ISRAEL_JERUSALEM = 1003,				//
		ESTONIA_TALLINN = 1004,					//
		LATVIA_RIGA = 1005,						//
		LITHUANIA_VILNIUS = 1006,				//
		REPUBLICOFSOUTHAFRICA_PRETORIA = 1007,	//
		TURKEY_ANKARA = 2001,					//
		RUSIA_MOSKVA = 2002,					//
		NEWZEALAND_WELLINGTON = 4001,			//
		INDIA_NEWDELHI = 5501,					//
		AUSTRALIA_CANBERRA = 6001,				//
		CHINA_BEIJING = 7002,					//
		TAIWAN_TAIPEI = 7003,					//
		PHILIPPINES_MANILA = 7004,				//
		INDONESIA_JAKARTA = 7005,				//
		NORTHKOREA_PYONGYANG = 8001,			//
		SOUTHKOREA_SEOUL = 8002,				//
		JAPAN_TOKYO = 8003,						//

	};

	inline CString GetWorldCityName(GreenWichWorldClockData cwcd)
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
		else if (cwcd == AUSTRALIA_CANBERRA) strReturnCityName = _T("호주 캔버라");
		else if (cwcd == NEWZEALAND_WELLINGTON) strReturnCityName = _T("뉴질랜드 웰링턴");
		else if (cwcd == TURKEY_ANKARA) strReturnCityName = _T("터키 앙카라");
		else if (cwcd == REPUBLICOFSOUTHAFRICA_PRETORIA) strReturnCityName = _T("남아프리카공화국 프리토리아");
		else if (cwcd == LITHUANIA_VILNIUS) strReturnCityName = _T("리투아니아 빌뉴스");
		else if (cwcd == LATVIA_RIGA) strReturnCityName = _T("라트비아 리가");
		else if (cwcd == ESTONIA_TALLINN) strReturnCityName = _T("에스토니아 탈린");
		else if (cwcd == ISRAEL_JERUSALEM) strReturnCityName = _T("이스라엘 예루살렘");
		else if (cwcd == FINLAND_HELSINKI) strReturnCityName = _T("핀란드 헬싱키");
		else if (cwcd == GREECE_ATHENS) strReturnCityName = _T("그리스 아테네");
		else if (cwcd == SLOVENIA_LJUBLJANA) strReturnCityName = _T("슬로베니아 류블랴나");
		else if (cwcd == SLOVAKIA_BRATISLAVA) strReturnCityName = _T("슬로바키아 브라티슬라바");
		else if (cwcd == POLAND_WARSZAWA) strReturnCityName = _T("폴란드 바르샤바");
		else if (cwcd == HUNGARY_BUDAPEST) strReturnCityName = _T("헝가리 부다페스트");
		else if (cwcd == CZECH_PRAGUE) strReturnCityName = _T("체코 프라하");
		else if (cwcd == ITALY_ROME) strReturnCityName = _T("이탈리아 로마");
		else if (cwcd == LUXEMBOURG_LUXEMBOURG) strReturnCityName = _T("룩셈부르크 룩셈부르크");
		else if (cwcd == NETHERLANDS_AMSTERDAM) strReturnCityName = _T("네덜란드 암스테르담");
		else if (cwcd == AUSTRIA_WIEN) strReturnCityName = _T("오스트리아 빈");
		else if (cwcd == COSTARICA_SANJOSE) strReturnCityName = _T("코스타리카 산호세");
		else if (cwcd == MEXICO_MEXICOCITY) strReturnCityName = _T("멕시코 멕시코시티");
		else if (cwcd == COLUMBIA_SANTAFEDEBOGOTA) strReturnCityName = _T("콜롬비아 산타데보고타");
		else if (cwcd == USA_WASHINGTONDC) strReturnCityName = _T("미국 워싱턴");
		else if (cwcd == CANADA_OTTAWA) strReturnCityName = _T("캐나다 오타와");
		else if (cwcd == CHILE_SANTIAGO) strReturnCityName = _T("칠레 산티아고");
		else if (cwcd == BRAZIL_BRASILIA) strReturnCityName = _T("브라질 브라질리아");
		else if (cwcd == IRELAND_DUBLIN) strReturnCityName = _T("아일랜드 더블린");
		else if (cwcd == PORTUGAL_LISBON) strReturnCityName = _T("포르투갈 리스본");
		else if (cwcd == ISLAND_REYKJAVIK) strReturnCityName = _T("아이슬란드 레이캬비크");
		else if (cwcd == ENGLAND_LONDON) strReturnCityName = _T("영국 런던");
		else if (cwcd == DENMARK_COPENHAGEN) strReturnCityName = _T("덴마크 코펜하겐");
		else if (cwcd == NORWAY_OSLO) strReturnCityName = _T("노르웨이 오슬로");
		else if (cwcd == SPAIN_MADRID) strReturnCityName = _T("스페인 마드리드");
		else if (cwcd == FRANCE_PARIS) strReturnCityName = _T("프랑스 파리");
		else if (cwcd == BELGIUM_BRUSSELS) strReturnCityName = _T("벨기에 브뤼셀");
		else if (cwcd == GERMANY_BERLIN) strReturnCityName = _T("독일 베를린");
		else if (cwcd == SWEDEN_STOCKHOLM) strReturnCityName = _T("스웨덴 스톡홀름");
		else if (cwcd == SWISS_BERN) strReturnCityName = _T("스위스 베른");

		return strReturnCityName;
	}

	inline double GetGMPCalcValue(GreenWichWorldClockData cwcd) {  return static_cast<double>(static_cast<int>(cwcd / 100)) / 10.0; }


private:

	struct WorldClockData
	{
		CString strWorldName;
		GreenWichWorldClockData gwcd;
		double dGMPValue;
	};

	ThemeData* currentTheme;
	CWnd* pParent;

	int nBrightness;
	COLORREF bkBorderColor;
	CustomScroll scroll;

	int nWorldButtonID;

	std::vector<WorldClockData> worldVector;
	std::vector<CalculateButton*> worldDataButtonVector;

	int nSearchButtonPos_x;
	int nSearchButtonPos_y;
	int nSearchButtonWidth;
	int nSearchButtonHeight;
	int nButtonCount;

	inline WorldClockData GetGreenWichWorldClockData(GreenWichWorldClockData cwcd)
	{
		WorldClockData worldclock = { GetWorldCityName(cwcd), cwcd, GetGMPCalcValue(cwcd) };
		return worldclock;
	}
	void LoadWorldClockList();
	void CreateWorldDataButton(WorldClockData wcd);
	void DeleteButtonVector();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:

	bool SearchClockListFromInputText(CString strInputText);

	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnPaint();
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
};
