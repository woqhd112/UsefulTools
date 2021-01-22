#pragma once
#include "CalculateEdit.h"
#include "WorldSearchList.h"
#include "AnalogWatch.h"
#include "CustomXml.h"
#include "UsingManualDialog.h"

// WorldClock 대화 상자

class WorldClock : public CDialogEx
{
	DECLARE_DYNAMIC(WorldClock)

public:
	WorldClock(int nManualImageID, bool bUsingManual, ThemeData* currentTheme, CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~WorldClock();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_WORLD_CLOCK };
#endif

private:

	CWnd* pParent;
	ThemeData* currentTheme;
	UsingManualDialog* usingManual;
	bool bUsingManual;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()

private:

	friend class AnalogWatch;

	CalculateButton m_btn_worldclock_localtime_sync;
	CalculateStatic m_stt_clock_offset;

	CBrush m_backBrush;
	CRect dynamicSearchRect;

	//AnalogWatch* analogwatch;
	std::vector<AnalogWatch*> analogWatchVector;
	std::vector<AnalogWatch::ClockData*> clockDataVector;

	bool bWillModify;

	int nErrorTimeHour;
	int nErrorTimeMinute;
	int nErrorTimeSecond;

	CWinThread* m_curtimeThread;
	bool bCurTimeThread;
	static UINT thrStartWorldClock(LPVOID method);
	void StartWorldClock();
	void FormatClockData(CString strInputTime, AnalogWatch::ClockData* inputTime);

	CString GetCurTime(double dErrorSubTimeValue);
	void ErrorTimeCalc(AnalogWatch::ClockData* inputTime);

	bool LoadWorldClockData();
	bool CreateDefaultClockXml(CMarkup* markUp, CString strFilePath);
	void SaveClockXml(int nClockIdx);

public:

	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnClose();
	virtual void PostNcDestroy();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnBnClickedButtonWorldclockSyncronize();
};
