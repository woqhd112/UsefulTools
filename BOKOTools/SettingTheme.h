#pragma once
#include "ThemeData.h"
#include "GdipButton.h"
#include "CalculateStatic.h"
#include "CMarkup/Markup.h"
#include "CXml\Xml.h"
#include "CustomScroll.h"
#include <vector>

// SettingTheme 대화 상자

class SettingTheme : public CDialogEx
{
	DECLARE_DYNAMIC(SettingTheme)

public:
	SettingTheme(std::vector<ThemeData*> themeList, ThemeData* currentTheme, CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~SettingTheme();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_SETTING_THEME };
#endif

private:

	CGdipButton m_btn_theme_detective;
	CGdipButton m_btn_theme_cloud;
	CGdipButton m_btn_theme_light;
	CGdipButton m_btn_theme_magnifier;
	CGdipButton m_btn_theme_ink;

	CWnd* pParent;
	std::vector<ThemeData*> themeList;
	ThemeData* currentTheme;
	ThemeData* hoverTheme;

	bool bButtonHover;

	int nCtlPos_X = 0;
	int nCtlPos_Y = 0;

	CustomScroll scroll;

	void SetCtlPos();
	void ExecuteSelectTheme(int nThemeFlags);
	void InvalidateTheme(int nSettingThemeBkIconID, ThemeData* hoverTheme);

	void SaveCurrnetTheme();
	void SaveXml(CMarkup* markup, CString strSaveFullPath);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
};
