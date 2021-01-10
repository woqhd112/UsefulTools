// SettingTheme.cpp: 구현 파일
//

#include "pch.h"
#include "BOKOTools.h"
#include "BOKOToolsDlg.h"
#include "SettingTheme.h"
#include "afxdialogex.h"


// SettingTheme 대화 상자

IMPLEMENT_DYNAMIC(SettingTheme, CDialogEx)

SettingTheme::SettingTheme(std::vector<ThemeData*> themeList, ThemeData* currentTheme, CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_SETTING_THEME, pParent)
{
	this->themeList = themeList;
	this->currentTheme = currentTheme;
	this->pParent = pParent;

}

SettingTheme::~SettingTheme()
{
}

void SettingTheme::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON_THEME_DETECTIVE, m_btn_theme_detective);
	DDX_Control(pDX, IDC_BUTTON_THEME_CLOUD, m_btn_theme_cloud);
	DDX_Control(pDX, IDC_BUTTON_THEME_LIGHT, m_btn_theme_light);
	DDX_Control(pDX, IDC_BUTTON_THEME_MAGNIFIER, m_btn_theme_magnifier);
	DDX_Control(pDX, IDC_BUTTON_THEME_INK, m_btn_theme_ink);
	DDX_Control(pDX, IDC_BUTTON_THEME_WATERDROP, m_btn_theme_waterdrop);
	DDX_Control(pDX, IDC_BUTTON_THEME_PLANET, m_btn_theme_planet);
	DDX_Control(pDX, IDC_BUTTON_THEME_NEONSIGN, m_btn_theme_neonsign);
}


BEGIN_MESSAGE_MAP(SettingTheme, CDialogEx)
	ON_WM_CTLCOLOR()
	ON_WM_VSCROLL()
	ON_WM_MOUSEWHEEL()
END_MESSAGE_MAP()


// SettingTheme 메시지 처리기


BOOL SettingTheme::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	this->SetBackgroundImage(currentTheme->GetSettingThemeBkIconID());
	
	m_btn_theme_detective.LoadStdImage(IDB_PNG_CHANGE_NOMAL_THEME_DETECTIVE, _T("PNG"), true);
	m_btn_theme_detective.LoadHovImage(IDB_PNG_CHANGE_HOVER_THEME_DETECTIVE, _T("PNG"), true);
	m_btn_theme_detective.LoadAltImage(IDB_PNG_CHANGE_CLICK_THEME_DETECTIVE, _T("PNG"), true);

	m_btn_theme_cloud.LoadStdImage(IDB_PNG_CHANGE_NOMAL_THEME_CLOUD, _T("PNG"), true);
	m_btn_theme_cloud.LoadHovImage(IDB_PNG_CHANGE_HOVER_THEME_CLOUD, _T("PNG"), true);
	m_btn_theme_cloud.LoadAltImage(IDB_PNG_CHANGE_CLICK_THEME_CLOUD, _T("PNG"), true);

	m_btn_theme_light.LoadStdImage(IDB_PNG_CHANGE_NOMAL_THEME_LIGHT, _T("PNG"), true);
	m_btn_theme_light.LoadHovImage(IDB_PNG_CHANGE_HOVER_THEME_LIGHT, _T("PNG"), true);
	m_btn_theme_light.LoadAltImage(IDB_PNG_CHANGE_CLICK_THEME_LIGHT, _T("PNG"), true);

	m_btn_theme_magnifier.LoadStdImage(IDB_PNG_CHANGE_NOMAL_THEME_MAGNIFIER, _T("PNG"), true);
	m_btn_theme_magnifier.LoadHovImage(IDB_PNG_CHANGE_HOVER_THEME_MAGNIFIER, _T("PNG"), true);
	m_btn_theme_magnifier.LoadAltImage(IDB_PNG_CHANGE_CLICK_THEME_MAGNIFIER, _T("PNG"), true);

	m_btn_theme_ink.LoadStdImage(IDB_PNG_CHANGE_NOMAL_THEME_INK, _T("PNG"), true);
	m_btn_theme_ink.LoadHovImage(IDB_PNG_CHANGE_HOVER_THEME_INK, _T("PNG"), true);
	m_btn_theme_ink.LoadAltImage(IDB_PNG_CHANGE_CLICK_THEME_INK, _T("PNG"), true);

	m_btn_theme_waterdrop.LoadStdImage(IDB_PNG_CHANGE_NOMAL_THEME_WATERDROP, _T("PNG"), true);
	m_btn_theme_waterdrop.LoadHovImage(IDB_PNG_CHANGE_HOVER_THEME_WATERDROP, _T("PNG"), true);
	m_btn_theme_waterdrop.LoadAltImage(IDB_PNG_CHANGE_CLICK_THEME_WATERDROP, _T("PNG"), true);

	m_btn_theme_planet.LoadStdImage(IDB_PNG_CHANGE_NOMAL_THEME_PLANET, _T("PNG"), true);
	m_btn_theme_planet.LoadHovImage(IDB_PNG_CHANGE_HOVER_THEME_PLANET, _T("PNG"), true);
	m_btn_theme_planet.LoadAltImage(IDB_PNG_CHANGE_CLICK_THEME_PLANET, _T("PNG"), true);

	m_btn_theme_neonsign.LoadStdImage(IDB_PNG_CHANGE_NOMAL_THEME_NEONSIGN, _T("PNG"), true);
	m_btn_theme_neonsign.LoadHovImage(IDB_PNG_CHANGE_HOVER_THEME_NEONSIGN, _T("PNG"), true);
	m_btn_theme_neonsign.LoadAltImage(IDB_PNG_CHANGE_CLICK_THEME_NEONSIGN, _T("PNG"), true);

	SetCtlPos();

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void SettingTheme::SetButtonPos(int nFirstButtonID, int nSecondButtonID, int nThirdButtonID, int nIdx)
{
	if (nFirstButtonID != 0)
	{
		nCtlPos_X = LEFT_MARGIN + 10;
		nCtlPos_Y = TOP_MARGIN + (PICTURE_HEIGHT + PICTURE_TO_PICTURE_MARGIN_HEIGHT) * nIdx;
		GetDlgItem(nFirstButtonID)->MoveWindow(nCtlPos_X, nCtlPos_Y, PICTURE_WIDTH, PICTURE_HEIGHT);
	}

	if (nSecondButtonID != 0)
	{
		nCtlPos_X += PICTURE_WIDTH + PICTURE_TO_PICTURE_MARGIN_WIDTH;
		GetDlgItem(nSecondButtonID)->MoveWindow(nCtlPos_X, nCtlPos_Y, PICTURE_WIDTH, PICTURE_HEIGHT);
	}

	if (nThirdButtonID != 0)
	{
		nCtlPos_X += PICTURE_WIDTH + PICTURE_TO_PICTURE_MARGIN_WIDTH;
		GetDlgItem(nThirdButtonID)->MoveWindow(nCtlPos_X, nCtlPos_Y, PICTURE_WIDTH, PICTURE_HEIGHT);
	}
}

void SettingTheme::SetCtlPos()
{
	scroll.Create(this);
	CustomScroll::CustomScrollInfo csi;
	csi.cst = CustomScroll::CUSTOM_SCROLL_TYPE_BUTTON;
	csi.nAllPageSize = 0;
	csi.nKindOfScrollFlags = SB_VERT;
	csi.nOnePageSize = 400 - 30 + 9;
	csi.nScrollPos = 0;
	scroll.Initialize(csi);

	// 첫번째 페이지, 페이지당 4줄
	{
		// 첫재줄
		SetButtonPos(m_btn_theme_detective.GetDlgCtrlID(), m_btn_theme_cloud.GetDlgCtrlID(), m_btn_theme_light.GetDlgCtrlID(), 0);

		// 두번째줄
		SetButtonPos(m_btn_theme_magnifier.GetDlgCtrlID(), m_btn_theme_ink.GetDlgCtrlID(), m_btn_theme_waterdrop.GetDlgCtrlID(), 1);

		// 세번째줄
		SetButtonPos(m_btn_theme_planet.GetDlgCtrlID(), m_btn_theme_neonsign.GetDlgCtrlID(), 0, 2);

	}
	scroll.LineEnd();


	this->SetWindowPos(NULL, 0, 0, MARGIN_X(300), MARGIN_Y(400), SWP_NOMOVE);

	scroll.ExecuteScrollPos(currentTheme);
}

void SettingTheme::OnOK()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	//CDialogEx::OnOK();
}


BOOL SettingTheme::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	if (pMsg->message == WM_LBUTTONUP)
	{
		if (pMsg->hwnd == m_btn_theme_detective.m_hWnd)
		{
			ExecuteSelectTheme(THEME_DETECTIVE);
			InvalidateTheme(IDB_BITMAP_CHOICE_BK_THEME_DETECTIVE, themeList.at(0));
		}
		else if (pMsg->hwnd == m_btn_theme_cloud.m_hWnd)
		{
			ExecuteSelectTheme(THEME_CLOUD);
			InvalidateTheme(IDB_BITMAP_CHOICE_BK_THEME_CLOUD, themeList.at(1));
		}
		else if (pMsg->hwnd == m_btn_theme_light.m_hWnd)
		{
			ExecuteSelectTheme(THEME_LIGHT);
			InvalidateTheme(IDB_BITMAP_CHOICE_BK_THEME_LIGHT, themeList.at(2));
		}
		else if (pMsg->hwnd == m_btn_theme_magnifier.m_hWnd)
		{
			ExecuteSelectTheme(THEME_MAGNIFIER);
			InvalidateTheme(IDB_BITMAP_CHOICE_BK_THEME_MAGNIFIER, themeList.at(3));
		}
		else if (pMsg->hwnd == m_btn_theme_ink.m_hWnd)
		{
			ExecuteSelectTheme(THEME_INK);
			InvalidateTheme(IDB_BITMAP_CHOICE_BK_THEME_INK, themeList.at(4));
		}
		else if (pMsg->hwnd == m_btn_theme_waterdrop.m_hWnd)
		{
			ExecuteSelectTheme(THEME_WATERDROP);
			InvalidateTheme(IDB_BITMAP_CHOICE_BK_THEME_WATERDROP, themeList.at(5));
		}
		else if (pMsg->hwnd == m_btn_theme_planet.m_hWnd)
		{
			ExecuteSelectTheme(THEME_PLANET);
			InvalidateTheme(IDB_BITMAP_CHOICE_BK_THEME_PLANET, themeList.at(5));
		}
		else if (pMsg->hwnd == m_btn_theme_neonsign.m_hWnd)
		{
			ExecuteSelectTheme(THEME_NEONSIGN);
			InvalidateTheme(IDB_BITMAP_CHOICE_BK_THEME_NEONSIGN, themeList.at(6));
		}
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}

void SettingTheme::InvalidateTheme(int nSettingThemeBkIconID, ThemeData* hoverTheme)
{
	this->SetBackgroundImage(nSettingThemeBkIconID);
	scroll.ThemeChange(hoverTheme);
	Invalidate();
	m_btn_theme_detective.DisConnect();
	m_btn_theme_cloud.DisConnect();
	m_btn_theme_light.DisConnect();
	m_btn_theme_magnifier.DisConnect();
	m_btn_theme_ink.DisConnect();
	m_btn_theme_waterdrop.DisConnect();
	m_btn_theme_planet.DisConnect();
	m_btn_theme_neonsign.DisConnect();
}

void SettingTheme::ExecuteSelectTheme(int nThemeFlags)
{
	if (currentTheme->GetThemeFlags() == nThemeFlags) return;

	for (int i = 0; i < (int)themeList.size(); i++)
	{
		if (themeList.at(i)->GetThemeFlags() == nThemeFlags)
		{
			currentTheme = themeList.at(i);	// 현재 테마를 설정한 테마로 바꾼다.
		}
	}
	scroll.ThemeChange(currentTheme);
	SaveCurrnetTheme();	// 테마 config 파일에 설정한 테마로 저장한다.
	CBOKOToolsDlg* parent = (CBOKOToolsDlg*)pParent;
	parent->ExecuteSelectTheme(currentTheme);	// 변경된 테마를 메인다이얼로그에 보낸다.
}

void SettingTheme::SaveCurrnetTheme()
{
	bool bSavedXml = false;
	CMarkup markUp;
	CString strFullPath = _T("Config\\Theme\\ThemeSetting.conf");
	if (markUp.Load(strFullPath))
	{
		markUp.FindElem(_T("Theme"));
		markUp.IntoElem();
		if (markUp.FindElem(_T("class")))
		{
			markUp.SetAttrib(_T("value"), currentTheme->GetThemeFlags());
		}
	}
	SaveXml(&markUp, strFullPath);
}

void SettingTheme::SaveXml(CMarkup* markup, CString strSaveFullPath)
{
	CString strXML = markup->GetDoc();

	HRESULT hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);
	JWXml::CXml saveXML;
	saveXML.LoadXml((LPCTSTR)strXML);
	saveXML.SaveWithFormatted(strSaveFullPath);
	saveXML.Close();
	CoUninitialize();
}

HBRUSH SettingTheme::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  여기서 DC의 특성을 변경합니다.
	if (nCtlColor == CTLCOLOR_SCROLLBAR)
	{
		pDC->SetBkColor(RGB(30, 30, 30));
	}

	// TODO:  기본값이 적당하지 않으면 다른 브러시를 반환합니다.
	return hbr;
}


void SettingTheme::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (scroll.OperateScroll(nSBCode, nPos))
	{
		InvalidateTheme(currentTheme->GetSettingThemeBkIconID(), currentTheme);
	}
	//CDialogEx::OnVScroll(nSBCode, nPos, pScrollBar);
}


BOOL SettingTheme::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (scroll.GetLineCount() > 1)
	{
		UINT nFlag = scroll.OperateWheel(zDelta);
		if (nFlag == SB_PAGEUP && scroll.GetCurrentLinePos() == 1) {}
		else if (nFlag == SB_PAGEDOWN && scroll.GetCurrentLinePos() == scroll.GetLineCount()) {}
		else { OnVScroll(nFlag, 0, GetScrollBarCtrl(SB_VERT)); }
	}
	return CDialogEx::OnMouseWheel(nFlags, zDelta, pt);
}
