#pragma once
#include "GeneralUtil.h"
#include "CalculateButton.h"
#include "CustomScroll.h"

// WorldSearchList 대화 상자

//class WorldClock;
class AnalogWatch;

class WorldSearchList : public CDialogEx
{
	DECLARE_DYNAMIC(WorldSearchList)

public:
	WorldSearchList(CRect buttonPosRect, ThemeData* currentTheme, CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~WorldSearchList();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_SEARCH_LIST };
#endif

private:

	//friend class WorldClockList;
	friend class AnalogWatch;
	friend class WorldClock;

	enum GreenWichWorldClockData
	{
		USA_LOSANGELES = -8005,
		USA_LASVEGAS = -8004,
		USA_SEATTLE = -8003,
		USA_SANFRANCISCO = -8002,
		CANADA_VANCOUVER = -8001,
		COSTARICA_SANJOSE = -6002,
		MEXICO_MEXICOCITY = -6001,
		USA_VIRGINIA = -5008,
		USA_NEWYORK = -5007,
		USA_ATLANTA = -5006,
		USA_MIAMI = -5005,
		CANADA_TORONTO = -5004,
		COLUMBIA_SANTAFEDEBOGOTA = -5003,
		USA_WASHINGTONDC = -5002,
		CANADA_OTTAWA = -5001,
		BRAZIL_SAOPAULO = -3003,
		CHILE_SANTIAGO = -3002,
		BRAZIL_BRASILIA = -3001,
		WORLD_CLOCK_NONE = 0,
		ENGLAND_LONDON = 1,
		ISLAND_REYKJAVIK = 2,
		PORTUGAL_LISBON = 3,
		IRELAND_DUBLIN = 4,
		ENGLAND_OXFORD = 5,
		ENGLAND_GREENWICH = 6,
		ENGLAND_LIVERPOOL = 7,
		ENGLAND_MANCHESTER = 8,
		SLOVENIA_LJUBLJANA = 1001,
		SLOVAKIA_BRATISLAVA = 1002,
		POLAND_WARSZAWA = 1003,
		HUNGARY_BUDAPEST = 1004,
		CZECH_PRAGUE = 1005,
		ITALY_ROME = 1006,
		LUXEMBOURG_LUXEMBOURG = 1007,
		NETHERLANDS_AMSTERDAM = 1008,
		AUSTRIA_WIEN = 1009,
		SWISS_BERN = 1010,
		SWEDEN_STOCKHOLM = 1011,
		GERMANY_BERLIN = 1012,
		BELGIUM_BRUSSELS = 1013,
		FRANCE_PARIS = 1014,
		SPAIN_MADRID = 1015,
		NORWAY_OSLO = 1016,
		DENMARK_COPENHAGEN = 1017,
		ITALIA_PISA = 1018,
		ITALIA_NEAPOLITAN = 1019,
		ITALIA_VENETIAN = 1020,
		ITALIA_MILAN = 1021,
		SPAIN_BARCELONA = 1022,
		FRANCE_MARSEILLE = 1023,
		GERMANY_MUNICH = 1024,
		SWISS_ZURICH = 1025,
		LITHUANIA_VILNIUS = 2001,
		REPUBLICOFSOUTHAFRICA_PRETORIA = 2002,
		LATVIA_RIGA = 2003,
		ESTONIA_TALLINN = 2004,
		ISRAEL_JERUSALEM = 2005,
		FINLAND_HELSINKI = 2006,
		GREECE_ATHENS = 2007,
		RUSIA_MOSKVA = 3001,
		TURKEY_ANKARA = 3002,
		UAE_DUBAI = 4001,
		NEWZEALAND_WELLINGTON = 5001,
		INDIA_NEWDELHI = 5501,
		AUSTRALIA_CANBERRA = 7001,
		INDONESIA_JAKARTA = 7002,
		AUSTRALIA_SYDNEY = 7003,
		CHINA_BEIJING = 8001,
		PHILIPPINES_MANILA = 8002,
		TAIWAN_TAIPEI = 8003,
		NORTHKOREA_PYONGYANG = 9001,
		SOUTHKOREA_SEOUL = 9002,
		JAPAN_TOKYO = 9003,

	};

	inline CString GetWorldCityName(GreenWichWorldClockData cwcd)
	{
		CString strReturnCityName = _T("");

		if (cwcd == INDIA_NEWDELHI) strReturnCityName = _T("인도 - 뉴델리");
		else if (cwcd == CHINA_BEIJING) strReturnCityName = _T("중국 - 베이징");
		else if (cwcd == TAIWAN_TAIPEI) strReturnCityName = _T("대만 - 타이베이");
		else if (cwcd == PHILIPPINES_MANILA) strReturnCityName = _T("필리핀 - 마닐라");
		else if (cwcd == INDONESIA_JAKARTA) strReturnCityName = _T("인도네시아 - 자카르타");
		else if (cwcd == NORTHKOREA_PYONGYANG) strReturnCityName = _T("북한 - 평양");
		else if (cwcd == SOUTHKOREA_SEOUL) strReturnCityName = _T("대한민국 - 서울");
		else if (cwcd == JAPAN_TOKYO) strReturnCityName = _T("일본 - 도쿄");
		else if (cwcd == RUSIA_MOSKVA) strReturnCityName = _T("러시아 - 모스크바");
		else if (cwcd == AUSTRALIA_CANBERRA) strReturnCityName = _T("호주 - 캔버라");
		else if (cwcd == NEWZEALAND_WELLINGTON) strReturnCityName = _T("뉴질랜드 - 웰링턴");
		else if (cwcd == TURKEY_ANKARA) strReturnCityName = _T("터키 - 앙카라");
		else if (cwcd == REPUBLICOFSOUTHAFRICA_PRETORIA) strReturnCityName = _T("남아프리카공화국 - 프리토리아");
		else if (cwcd == LITHUANIA_VILNIUS) strReturnCityName = _T("리투아니아 - 빌뉴스");
		else if (cwcd == LATVIA_RIGA) strReturnCityName = _T("라트비아 - 리가");
		else if (cwcd == ESTONIA_TALLINN) strReturnCityName = _T("에스토니아 - 탈린");
		else if (cwcd == ISRAEL_JERUSALEM) strReturnCityName = _T("이스라엘 - 예루살렘");
		else if (cwcd == FINLAND_HELSINKI) strReturnCityName = _T("핀란드 - 헬싱키");
		else if (cwcd == GREECE_ATHENS) strReturnCityName = _T("그리스 - 아테네");
		else if (cwcd == SLOVENIA_LJUBLJANA) strReturnCityName = _T("슬로베니아 - 류블랴나");
		else if (cwcd == SLOVAKIA_BRATISLAVA) strReturnCityName = _T("슬로바키아 - 브라티슬라바");
		else if (cwcd == POLAND_WARSZAWA) strReturnCityName = _T("폴란드 - 바르샤바");
		else if (cwcd == HUNGARY_BUDAPEST) strReturnCityName = _T("헝가리 - 부다페스트");
		else if (cwcd == CZECH_PRAGUE) strReturnCityName = _T("체코 - 프라하");
		else if (cwcd == ITALY_ROME) strReturnCityName = _T("이탈리아 - 로마");
		else if (cwcd == LUXEMBOURG_LUXEMBOURG) strReturnCityName = _T("룩셈부르크 - 룩셈부르크");
		else if (cwcd == NETHERLANDS_AMSTERDAM) strReturnCityName = _T("네덜란드 - 암스테르담");
		else if (cwcd == AUSTRIA_WIEN) strReturnCityName = _T("오스트리아 - 빈");
		else if (cwcd == COSTARICA_SANJOSE) strReturnCityName = _T("코스타리카 - 산호세");
		else if (cwcd == MEXICO_MEXICOCITY) strReturnCityName = _T("멕시코 - 멕시코시티");
		else if (cwcd == COLUMBIA_SANTAFEDEBOGOTA) strReturnCityName = _T("콜롬비아 - 산타데보고타");
		else if (cwcd == USA_WASHINGTONDC) strReturnCityName = _T("미국 - 워싱턴");
		else if (cwcd == CANADA_OTTAWA) strReturnCityName = _T("캐나다 - 오타와");
		else if (cwcd == CHILE_SANTIAGO) strReturnCityName = _T("칠레 - 산티아고");
		else if (cwcd == BRAZIL_BRASILIA) strReturnCityName = _T("브라질 - 브라질리아");
		else if (cwcd == IRELAND_DUBLIN) strReturnCityName = _T("아일랜드 - 더블린");
		else if (cwcd == PORTUGAL_LISBON) strReturnCityName = _T("포르투갈 - 리스본");
		else if (cwcd == ISLAND_REYKJAVIK) strReturnCityName = _T("아이슬란드 - 레이캬비크");
		else if (cwcd == ENGLAND_LONDON) strReturnCityName = _T("영국 - 런던");
		else if (cwcd == DENMARK_COPENHAGEN) strReturnCityName = _T("덴마크 - 코펜하겐");
		else if (cwcd == NORWAY_OSLO) strReturnCityName = _T("노르웨이 - 오슬로");
		else if (cwcd == SPAIN_MADRID) strReturnCityName = _T("스페인 - 마드리드");
		else if (cwcd == FRANCE_PARIS) strReturnCityName = _T("프랑스 - 파리");
		else if (cwcd == BELGIUM_BRUSSELS) strReturnCityName = _T("벨기에 - 브뤼셀");
		else if (cwcd == GERMANY_BERLIN) strReturnCityName = _T("독일 - 베를린");
		else if (cwcd == SWEDEN_STOCKHOLM) strReturnCityName = _T("스웨덴 - 스톡홀름");
		else if (cwcd == SWISS_BERN) strReturnCityName = _T("스위스 - 베른");
		else if (cwcd == AUSTRALIA_SYDNEY) strReturnCityName = _T("호주 - 시드니");
		else if (cwcd == UAE_DUBAI) strReturnCityName = _T("아랍에미리트 - 두바이");
		else if (cwcd == SWISS_ZURICH) strReturnCityName = _T("스위스 - 취리히");
		else if (cwcd == GERMANY_MUNICH) strReturnCityName = _T("독일 - 뮌헨");
		else if (cwcd == FRANCE_MARSEILLE) strReturnCityName = _T("프랑스 - 마르세유");
		else if (cwcd == SPAIN_BARCELONA) strReturnCityName = _T("스페인 - 바르셀로나");
		else if (cwcd == ITALIA_MILAN) strReturnCityName = _T("이탈리아 - 밀라노");
		else if (cwcd == ITALIA_VENETIAN) strReturnCityName = _T("이탈리아 - 베네치아");
		else if (cwcd == ITALIA_NEAPOLITAN) strReturnCityName = _T("이탈리아 - 나폴리");
		else if (cwcd == ITALIA_PISA) strReturnCityName = _T("이탈리아 - 피사");
		else if (cwcd == USA_VIRGINIA) strReturnCityName = _T("미국 - 버지니아");
		else if (cwcd == USA_NEWYORK) strReturnCityName = _T("미국 - 뉴욕");
		else if (cwcd == USA_LOSANGELES) strReturnCityName = _T("미국 - 로스앤젤레스");
		else if (cwcd == USA_LASVEGAS) strReturnCityName = _T("미국 - 라스베이거스");
		else if (cwcd == USA_ATLANTA) strReturnCityName = _T("미국 - 애틀란타");
		else if (cwcd == USA_SEATTLE) strReturnCityName = _T("미국 - 시애틀");
		else if (cwcd == USA_SANFRANCISCO) strReturnCityName = _T("미국 - 샌프란시스코");
		else if (cwcd == USA_MIAMI) strReturnCityName = _T("미국 - 마이애미");
		else if (cwcd == CANADA_VANCOUVER) strReturnCityName = _T("캐나다 - 밴쿠버");
		else if (cwcd == CANADA_TORONTO) strReturnCityName = _T("캐나다 - 토론토");
		else if (cwcd == BRAZIL_SAOPAULO) strReturnCityName = _T("브라질 - 상파울루");
		else if (cwcd == ENGLAND_MANCHESTER) strReturnCityName = _T("영국 - 맨체스터");
		else if (cwcd == ENGLAND_LIVERPOOL) strReturnCityName = _T("영국 - 리버풀");
		else if (cwcd == ENGLAND_GREENWICH) strReturnCityName = _T("영국 - 그리니치");
		else if (cwcd == ENGLAND_OXFORD) strReturnCityName = _T("영국 - 옥스포드");


		return strReturnCityName;
	}

	inline GreenWichWorldClockData GetWorldClockData(CString strWorldName)
	{
		GreenWichWorldClockData cwcd = WORLD_CLOCK_NONE;

		if (strWorldName == _T("인도 - 뉴델리")) cwcd = INDIA_NEWDELHI;
		else if (strWorldName == _T("중국 - 베이징")) cwcd = CHINA_BEIJING;
		else if (strWorldName == _T("대만 - 타이베이")) cwcd = TAIWAN_TAIPEI;
		else if (strWorldName == _T("필리핀 - 마닐라")) cwcd = PHILIPPINES_MANILA;
		else if (strWorldName == _T("인도네시아 - 자카르타")) cwcd = INDONESIA_JAKARTA;
		else if (strWorldName == _T("북한 - 평양")) cwcd = NORTHKOREA_PYONGYANG;
		else if (strWorldName == _T("대한민국 - 서울")) cwcd = SOUTHKOREA_SEOUL;
		else if (strWorldName == _T("일본 - 도쿄")) cwcd = JAPAN_TOKYO;
		else if (strWorldName == _T("러시아 - 모스크바")) cwcd = RUSIA_MOSKVA;
		else if (strWorldName == _T("호주 - 캔버라")) cwcd = AUSTRALIA_CANBERRA;
		else if (strWorldName == _T("뉴질랜드 - 웰링턴")) cwcd = NEWZEALAND_WELLINGTON;
		else if (strWorldName == _T("터키 - 앙카라")) cwcd = TURKEY_ANKARA;
		else if (strWorldName == _T("남아프리카공화국 - 프리토리아")) cwcd = REPUBLICOFSOUTHAFRICA_PRETORIA;
		else if (strWorldName == _T("리투아니아 - 빌뉴스")) cwcd = LITHUANIA_VILNIUS;
		else if (strWorldName == _T("라트비아 - 리가")) cwcd = LATVIA_RIGA;
		else if (strWorldName == _T("에스토니아 - 탈린")) cwcd = ESTONIA_TALLINN;
		else if (strWorldName == _T("이스라엘 - 예루살렘")) cwcd = ISRAEL_JERUSALEM;
		else if (strWorldName == _T("핀란드 - 헬싱키")) cwcd = FINLAND_HELSINKI;
		else if (strWorldName == _T("그리스 - 아테네")) cwcd = GREECE_ATHENS;
		else if (strWorldName == _T("슬로베니아 - 류블랴나")) cwcd = SLOVENIA_LJUBLJANA;
		else if (strWorldName == _T("슬로바키아 - 브라티슬라바")) cwcd = SLOVAKIA_BRATISLAVA;
		else if (strWorldName == _T("폴란드 - 바르샤바")) cwcd = POLAND_WARSZAWA;
		else if (strWorldName == _T("헝가리 - 부다페스트")) cwcd = HUNGARY_BUDAPEST;
		else if (strWorldName == _T("체코 - 프라하")) cwcd = CZECH_PRAGUE;
		else if (strWorldName == _T("이탈리아 - 로마")) cwcd = ITALY_ROME;
		else if (strWorldName == _T("룩셈부르크 - 룩셈부르크")) cwcd = LUXEMBOURG_LUXEMBOURG;
		else if (strWorldName == _T("네덜란드 - 암스테르담")) cwcd = NETHERLANDS_AMSTERDAM;
		else if (strWorldName == _T("오스트리아 - 빈")) cwcd = AUSTRIA_WIEN;
		else if (strWorldName == _T("코스타리카 - 산호세")) cwcd = COSTARICA_SANJOSE;
		else if (strWorldName == _T("멕시코 - 멕시코시티")) cwcd = MEXICO_MEXICOCITY;
		else if (strWorldName == _T("콜롬비아 - 산타데보고타")) cwcd = COLUMBIA_SANTAFEDEBOGOTA;
		else if (strWorldName == _T("미국 - 워싱턴")) cwcd = USA_WASHINGTONDC;
		else if (strWorldName == _T("캐나다 - 오타와")) cwcd = CANADA_OTTAWA;
		else if (strWorldName == _T("칠레 - 산티아고")) cwcd = CHILE_SANTIAGO;
		else if (strWorldName == _T("브라질 - 브라질리아")) cwcd = BRAZIL_BRASILIA;
		else if (strWorldName == _T("아일랜드 - 더블린")) cwcd = IRELAND_DUBLIN;
		else if (strWorldName == _T("포르투갈 - 리스본")) cwcd = PORTUGAL_LISBON;
		else if (strWorldName == _T("아이슬란드 - 레이캬비크")) cwcd = ISLAND_REYKJAVIK;
		else if (strWorldName == _T("영국 - 런던")) cwcd = ENGLAND_LONDON;
		else if (strWorldName == _T("덴마크 - 코펜하겐")) cwcd = DENMARK_COPENHAGEN;
		else if (strWorldName == _T("노르웨이 - 오슬로")) cwcd = NORWAY_OSLO;
		else if (strWorldName == _T("스페인 - 마드리드")) cwcd = SPAIN_MADRID;
		else if (strWorldName == _T("프랑스 - 파리")) cwcd = FRANCE_PARIS;
		else if (strWorldName == _T("벨기에 - 브뤼셀")) cwcd = BELGIUM_BRUSSELS;
		else if (strWorldName == _T("독일 - 베를린")) cwcd = GERMANY_BERLIN;
		else if (strWorldName == _T("스웨덴 - 스톡홀름")) cwcd = SWEDEN_STOCKHOLM;
		else if (strWorldName == _T("스위스 - 베른")) cwcd = SWISS_BERN;
		else if (strWorldName == _T("호주 - 시드니")) cwcd = AUSTRALIA_SYDNEY;
		else if (strWorldName == _T("아랍에미리트 - 두바이")) cwcd = UAE_DUBAI;
		else if (strWorldName == _T("스위스 - 취리히")) cwcd = SWISS_ZURICH;
		else if (strWorldName == _T("독일 - 뮌헨")) cwcd = GERMANY_MUNICH;
		else if (strWorldName == _T("프랑스 - 마르세유")) cwcd = FRANCE_MARSEILLE;
		else if (strWorldName == _T("스페인 - 바르셀로나")) cwcd = SPAIN_BARCELONA;
		else if (strWorldName == _T("이탈리아 - 밀라노")) cwcd = ITALIA_MILAN;
		else if (strWorldName == _T("이탈리아 - 베네치아")) cwcd = ITALIA_VENETIAN;
		else if (strWorldName == _T("이탈리아 - 나폴리")) cwcd = ITALIA_NEAPOLITAN;
		else if (strWorldName == _T("이탈리아 - 피사")) cwcd = ITALIA_PISA;
		else if (strWorldName == _T("미국 - 버지니아")) cwcd = USA_VIRGINIA;
		else if (strWorldName == _T("미국 - 뉴욕")) cwcd = USA_NEWYORK;
		else if (strWorldName == _T("미국 - 로스앤젤레스")) cwcd = USA_LOSANGELES;
		else if (strWorldName == _T("미국 - 라스베이거스")) cwcd = USA_LASVEGAS;
		else if (strWorldName == _T("미국 - 애틀란타")) cwcd = USA_ATLANTA;
		else if (strWorldName == _T("미국 - 시애틀")) cwcd = USA_SEATTLE;
		else if (strWorldName == _T("미국 - 샌프란시스코")) cwcd = USA_SANFRANCISCO;
		else if (strWorldName == _T("미국 - 마이애미")) cwcd = USA_MIAMI;
		else if (strWorldName == _T("캐나다 - 밴쿠버")) cwcd = CANADA_VANCOUVER;
		else if (strWorldName == _T("캐나다 - 토론토")) cwcd = CANADA_TORONTO;
		else if (strWorldName == _T("브라질 - 상파울루")) cwcd = BRAZIL_SAOPAULO;
		else if (strWorldName == _T("영국 - 맨체스터")) cwcd = ENGLAND_MANCHESTER;
		else if (strWorldName == _T("영국 - 리버풀")) cwcd = ENGLAND_LIVERPOOL;
		else if (strWorldName == _T("영국 - 그리니치")) cwcd = ENGLAND_GREENWICH;
		else if (strWorldName == _T("영국 - 옥스포드")) cwcd = ENGLAND_OXFORD;

		return cwcd;
	}

	inline double GetGMPCalcValue(GreenWichWorldClockData cwcd) {  return static_cast<double>(static_cast<int>(cwcd / 100)) / 10.0; }


private:

	struct WorldClockData
	{
		CString strWorldName;
		GreenWichWorldClockData gwcd;
		double dGMPValue;
	};

	CRect buttonRect;
	ThemeData* currentTheme;
	//WorldClock* worldclock;
	AnalogWatch* analogwatch;
	CWnd* pParent;

	int nBrightness;
	COLORREF bkBorderColor;
	CustomScroll scroll;

	int nWorldButtonID;

	std::vector<WorldClockData> worldVector;
	std::vector<CalculateButton*> worldDataButtonVector;
	std::vector<CalculateButton*> cityDataButtonVector;
	std::vector<CalculateButton*> allDataButtonVector;

	int nSearchButtonPos_x;
	int nSearchButtonPos_y;
	int nSearchButtonWidth;
	int nSearchButtonHeight;

	inline WorldClockData GetGreenWichWorldClockData(GreenWichWorldClockData cwcd)
	{
		WorldClockData worldclock = { GetWorldCityName(cwcd), cwcd, GetGMPCalcValue(cwcd) };
		return worldclock;
	}
	void LoadWorldClockList();
	void CreateWorldDataButton(WorldClockData wcd);
	void CreateCityDataButton(WorldClockData wcd);
	void DeleteButtonVector();
	void SetApsorptionToButtonPos();

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
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
};
