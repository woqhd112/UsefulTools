#pragma once
#include "ThemeData.h"
#include "CalculateStatic.h"
#include "CalculateButton.h"
#include "CalculateEdit.h"
#include "GeneralUtil.h"
#include "WorldClockList.h"
#include "WorldSearchList.h"

// AnalogWatch 대화 상자

class AnalogWatch : public CDialogEx
{
	DECLARE_DYNAMIC(AnalogWatch)

public:
	AnalogWatch(ThemeData* currentTheme, CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~AnalogWatch();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_ANALOG_WATCh };
#endif

private:

	friend class WorldClock;
	friend class WorldSearchList;

	int nBrightness;
	COLORREF bkBorderColor;

	CWnd* pParent;
	ThemeData* currentTheme;
	WorldSearchList* worldsearchlist;

	CBrush m_backBrush;
	CRect thisRect, watchRect;
	CalculateStatic m_stt_analog_date;
	CalculateButton m_btn_analog_submit;
	CalculateEdit m_edit_analog_search;

	bool bMainClock;

	enum TIME_ { TIME_SEC, TIME_MIN, TIME_HOUR };

	const double PI = 3.141592653589793238462643383279;
	const double WATCH_MINMARK = 10;
	const double WATCH_MARKWIDTH = 50;
	const int WATCH_HOURTEXT = 2;
	const int WATCH_LOGOTEXT = 10;
	const double WATCH_LOGODOWN = 2.5;

	const int WATCH_CENTERSIZE = 40;
	const double WATCH_SECLENGTH = 0.9;
	const double WATCH_MINLENGTH = 0.8;
	const double WATCH_HOURLENGTH = 0.6;
	const double WATCH_SECWIDTH = 300;
	const double WATCH_MINWIDTH = 100;
	const double WATCH_HOURWIDTH = 50;

	struct ClockData
	{
		double dErrorMainGMPValue;
		double dErrorSubGMPValue;
		CString strWorldName;
		CString strCityName;
		int nHour;
		int nMinute;
		int nSecond;
	};

	ClockData* clockData;

	CPoint GetRotatedPos(const CPoint& anchorPt, double radius, double deg) const;
	void DrawTime(CDC& memDC);
	CPoint GetClockHandPos(AnalogWatch::TIME_ TIME, const CTime& time, const CPoint& anchorPt, double radius);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:

	void Initialize();
	void InvalidClockRect();

	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnPaint();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnEnChangeEditAnalogSearch();
	afx_msg void OnBnClickedButtonAnalogSubmit();
};
