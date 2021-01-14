#pragma once
#include "ThemeData.h"
#include "CalculateStatic.h"
#include "CalculateButton.h"
#include "CalculateEdit.h"
#include "GeneralUtil.h"
#include "WorldSearchList.h"

// AnalogWatch 대화 상자
class WorldClock;

class AnalogWatch : public CDialogEx
{
	DECLARE_DYNAMIC(AnalogWatch)

public:
	AnalogWatch(ThemeData* currentTheme, CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~AnalogWatch();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_ANALOG_WATCH };
#endif

private:

	friend class WorldClock;
	friend class WorldSearchList;

	int nBrightness;
	COLORREF bkBorderColor;

	CWnd* pParent;
	WorldClock* worldclock;
	ThemeData* currentTheme;
	WorldSearchList* worldsearchlist;

	CBrush m_backBrush;
	CBrush m_digitalBrush;
	CRect thisRect, watchRect, watchBorderRect;
	CalculateStatic m_stt_analog_date;
	CalculateStatic m_stt_analog_worldname;
	CalculateButton m_btn_analog_submit;
	CalculateEdit m_edit_analog_search;
	CalculateEdit m_edit_digital_clock;

	int nClockIdx;
	bool bClockDataInit;

	enum TIME_ { TIME_SEC, TIME_MIN, TIME_HOUR };

	const double PI = 3.141592653589793238462643383279;
	const double WATCH_MINMARK = 10;
	const double WATCH_MARKWIDTH = 50;
	const int WATCH_HOURTEXT = 2;
	const int WATCH_LOGOTEXT = 1;
	const double WATCH_LOGODOWN = 2.5;

	const int WATCH_CENTERSIZE = 40;
	const double WATCH_SECLENGTH = 0.9;
	const double WATCH_MINLENGTH = 0.7;
	const double WATCH_HOURLENGTH = 0.5;
	const double WATCH_SECWIDTH = 250;
	const double WATCH_MINWIDTH = 70;
	const double WATCH_HOURWIDTH = 40;


	struct ClockData
	{
		WorldSearchList::GreenWichWorldClockData mainGWCD;
		WorldSearchList::GreenWichWorldClockData subGWCD;
		CString strWorldCityName;
		CTime curTimeVal;
	};


	CTime formatTime;
	bool bTimeSync;
	bool bInitWorldSearchList;

	ClockData* clockData;
	CPoint cpt;
	bool m_bInitSuccess;

	CRgn hourLine;
	CRgn minuteLine;
	CRgn secondLine;
	CPoint point[4];

	CPoint GetRotatedPos(const CPoint& anchorPt, double radius, double deg) const;
	void DrawTime(CDC& memDC);
	CPoint GetClockHandPos(AnalogWatch::TIME_ TIME, const CTime& time, const CPoint& anchorPt, double radius);
	void DrawClockData(CDC& memDC, CPoint selectPoint, const double selectWidth);
	void SetErrorTime();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:

	void Initialize(ClockData* clockData);
	void SetClockPriority(int nPriority);
	void InvalidClockRect(ClockData* clockData);

	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnPaint();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnEnChangeEditAnalogSearch();
	afx_msg void OnBnClickedButtonAnalogSubmit();
};
