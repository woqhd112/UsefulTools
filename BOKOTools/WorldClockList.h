#pragma once
#include "ThemeData.h"
#include "GeneralUtil.h"
#include "CustomScroll.h"
#include "CalculateButton.h"
#include "CalculateStatic.h"
#include "CMarkup/Markup.h"
#include "CXml\Xml.h"
#include <vector>


// WorldClockList 대화 상자

class WorldClock;

class WorldClockList : public CDialogEx
{
	DECLARE_DYNAMIC(WorldClockList)

public:
	WorldClockList(ThemeData* currentTheme, CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~WorldClockList();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_WORLD_LIST };
#endif

private:

	ThemeData* currentTheme;
	CWnd* pParent;

	WorldClock* worldclock;

	int nBrightness;
	COLORREF bkBorderColor;
	CBrush m_backBrush;
	HANDLE m_fonthandle;

	CustomScroll scroll;
	int nWorldButtonID; 
	int nClockButtonPos_x;
	int nClockButtonPos_y;
	int nClockButtonWidth;
	int nClockButtonHeight;
	int nButtonCount;
	int nDetectHeight;

	std::vector<CalculateButton*> clockButtonVector;
	std::vector<CalculateStatic*> clockStaticVector;
	std::vector<double> clockDataVector;

	CWinThread* m_curtimeThread;
	bool bCurTimeThread;
	static UINT thrStartWorldTime(LPVOID method);
	void StartWorldTime();

	CString GetCurTime(double dErrorTimeValue);

	void LoadWorldClock();
	void CreateConfigClockFile(CString& strFullPath);
	bool CreateDefaultClockXml(CMarkup* markUp, CString strFilePath);
	void CreateDefaultDirectory(CString& strFullPath, CString strAppendPath);
	void SaveXml(CMarkup* markup, CString strSaveFullPath);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:

	bool AddClock(double dErrorTimeValue, CString strWorldClockName, CString strCityClockName);

	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnPaint();
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
};
