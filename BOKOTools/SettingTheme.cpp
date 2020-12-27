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

	cy = 0;
	m_nBasic = 64;	// 스크롤 위아래 버튼 클릭 시 스크롤 간격
	nViewHeight = 0;	// 스크롤 전체 출력 화면
	nScrollPos = 0;	// 현재 스크롤의 위치
	nPageSize = 0;	// 한페이지의 사이즈
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
	DDX_Control(pDX, IDC_BUTTON_THEME_NONE2, m_btn_theme_none2);
	DDX_Control(pDX, IDC_BUTTON_THEME_NONE3, m_btn_theme_none3);
	DDX_Control(pDX, IDC_BUTTON_THEME_NONE4, m_btn_theme_none4);
	DDX_Control(pDX, IDC_BUTTON_THEME_NONE5, m_btn_theme_none5);
	DDX_Control(pDX, IDC_BUTTON_THEME_NONE6, m_btn_theme_none6);
	DDX_Control(pDX, IDC_BUTTON_THEME_NONE7, m_btn_theme_none7);
}


BEGIN_MESSAGE_MAP(SettingTheme, CDialogEx)
	ON_WM_CTLCOLOR()
	ON_WM_SIZE()
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

	m_btn_theme_none2.LoadStdImage(currentTheme->GetCommingSoonIconID(), _T("PNG"), true);
	m_btn_theme_none2.LoadHovImage(currentTheme->GetCommingSoonIconID(), _T("PNG"), true);
	m_btn_theme_none2.LoadAltImage(currentTheme->GetCommingSoonIconID(), _T("PNG"), true);

	m_btn_theme_none3.LoadStdImage(currentTheme->GetCommingSoonIconID(), _T("PNG"), true);
	m_btn_theme_none3.LoadHovImage(currentTheme->GetCommingSoonIconID(), _T("PNG"), true);
	m_btn_theme_none3.LoadAltImage(currentTheme->GetCommingSoonIconID(), _T("PNG"), true);

	m_btn_theme_none4.LoadStdImage(currentTheme->GetCommingSoonIconID(), _T("PNG"), true);
	m_btn_theme_none4.LoadHovImage(currentTheme->GetCommingSoonIconID(), _T("PNG"), true);
	m_btn_theme_none4.LoadAltImage(currentTheme->GetCommingSoonIconID(), _T("PNG"), true);

	m_btn_theme_none5.LoadStdImage(currentTheme->GetCommingSoonIconID(), _T("PNG"), true);
	m_btn_theme_none5.LoadHovImage(currentTheme->GetCommingSoonIconID(), _T("PNG"), true);
	m_btn_theme_none5.LoadAltImage(currentTheme->GetCommingSoonIconID(), _T("PNG"), true);

	m_btn_theme_none6.LoadStdImage(currentTheme->GetCommingSoonIconID(), _T("PNG"), true);
	m_btn_theme_none6.LoadHovImage(currentTheme->GetCommingSoonIconID(), _T("PNG"), true);
	m_btn_theme_none6.LoadAltImage(currentTheme->GetCommingSoonIconID(), _T("PNG"), true);

	m_btn_theme_none7.LoadStdImage(currentTheme->GetCommingSoonIconID(), _T("PNG"), true);
	m_btn_theme_none7.LoadHovImage(currentTheme->GetCommingSoonIconID(), _T("PNG"), true);
	m_btn_theme_none7.LoadAltImage(currentTheme->GetCommingSoonIconID(), _T("PNG"), true);

	m_btn_theme_detective.ModifyStyle(0, WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 0);
	m_btn_theme_cloud.ModifyStyle(0, WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 0);

	m_btn_theme_detective.BringWindowToTop();
	m_btn_theme_cloud.BringWindowToTop();

	hoverTheme = currentTheme;

	SetCtlPos();

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void SettingTheme::SetCtlPos()
{
	const int PICTURE_WIDTH = 64;
	const int PICTURE_HEIGHT = 64;
	const int LEFT_MARGIN = 20;
	const int TOP_MARGIN = 30;
	const int PICTURE_TO_PICTURE_MARGIN_WIDTH = 20;
	const int PICTURE_TO_PICTURE_MARGIN_HEIGHT = 30;

	// 첫재줄
	nCtlPos_X = LEFT_MARGIN;
	nCtlPos_Y += TOP_MARGIN;
	m_btn_theme_detective.MoveWindow(nCtlPos_X, nCtlPos_Y, PICTURE_WIDTH, PICTURE_HEIGHT);

	nCtlPos_X += PICTURE_WIDTH + PICTURE_TO_PICTURE_MARGIN_WIDTH;
	m_btn_theme_cloud.MoveWindow(nCtlPos_X, nCtlPos_Y, PICTURE_WIDTH, PICTURE_HEIGHT);

	nCtlPos_X += PICTURE_WIDTH + PICTURE_TO_PICTURE_MARGIN_WIDTH;
	m_btn_theme_light.MoveWindow(nCtlPos_X, nCtlPos_Y, PICTURE_WIDTH, PICTURE_HEIGHT);

	// 두번째줄
	nCtlPos_X = LEFT_MARGIN;
	nCtlPos_Y += PICTURE_HEIGHT + PICTURE_TO_PICTURE_MARGIN_HEIGHT;
	m_btn_theme_none2.MoveWindow(nCtlPos_X, nCtlPos_Y, PICTURE_WIDTH, PICTURE_HEIGHT);

	nCtlPos_X += PICTURE_WIDTH + PICTURE_TO_PICTURE_MARGIN_WIDTH;
	m_btn_theme_none3.MoveWindow(nCtlPos_X, nCtlPos_Y, PICTURE_WIDTH, PICTURE_HEIGHT);

	nCtlPos_X += PICTURE_WIDTH + PICTURE_TO_PICTURE_MARGIN_WIDTH;
	m_btn_theme_none4.MoveWindow(nCtlPos_X, nCtlPos_Y, PICTURE_WIDTH, PICTURE_HEIGHT);

	// 세번째줄
	nCtlPos_X = LEFT_MARGIN;
	nCtlPos_Y += PICTURE_HEIGHT + PICTURE_TO_PICTURE_MARGIN_HEIGHT;
	m_btn_theme_none5.MoveWindow(nCtlPos_X, nCtlPos_Y, PICTURE_WIDTH, PICTURE_HEIGHT);

	nCtlPos_X += PICTURE_WIDTH + PICTURE_TO_PICTURE_MARGIN_WIDTH;
	m_btn_theme_none6.MoveWindow(nCtlPos_X, nCtlPos_Y, PICTURE_WIDTH, PICTURE_HEIGHT);

	nCtlPos_X += PICTURE_WIDTH + PICTURE_TO_PICTURE_MARGIN_WIDTH;
	m_btn_theme_none7.MoveWindow(nCtlPos_X, nCtlPos_Y, PICTURE_WIDTH, PICTURE_HEIGHT);

	CRect SystemRect;
	CPoint pos;
	GetClientRect(SystemRect);
	int nVector_Y = TOP_MARGIN * 4 + (PICTURE_HEIGHT + PICTURE_TO_PICTURE_MARGIN_HEIGHT) * 3;	
	pos.x = LONG(GetSystemMetrics(SM_CXSCREEN) / 2.0f - SystemRect.Width() / 2.0f);
	pos.y = LONG(GetSystemMetrics(SM_CYSCREEN) / 2.0f - SystemRect.Height() / 2.0f);

	this->MoveWindow(pos.x, pos.y, 300, 300);
	nViewHeight += nVector_Y;
	SetScrollSize(cy);
}


void SettingTheme::OnOK()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	//CDialogEx::OnOK();
}


BOOL SettingTheme::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	if (pMsg->message == WM_MOUSEMOVE)
	{
		if (pMsg->hwnd == m_btn_theme_detective.m_hWnd)
		{
			if (currentTheme->GetSettingThemeBkIconID() != IDB_BITMAP_CHOICE_BK_THEME_DETECTIVE)
			{
				if (!bButtonHover)
				{
					bButtonHover = true;
					InvalidateTheme(IDB_BITMAP_CHOICE_BK_THEME_DETECTIVE, themeList.at(0));
				}
			}
		}
		else if (pMsg->hwnd == m_btn_theme_cloud.m_hWnd)
		{
			if (currentTheme->GetSettingThemeBkIconID() != IDB_BITMAP_CHOICE_BK_THEME_CLOUD)
			{
				if (!bButtonHover)
				{
					bButtonHover = true;
					InvalidateTheme(IDB_BITMAP_CHOICE_BK_THEME_CLOUD, themeList.at(1));
				}
			}
		}
		else if (pMsg->hwnd == m_btn_theme_light.m_hWnd)
		{
			if (currentTheme->GetSettingThemeBkIconID() != IDB_BITMAP_CHOICE_BK_THEME_LIGHT)
			{
				if (!bButtonHover)
				{
					bButtonHover = true;
					InvalidateTheme(IDB_BITMAP_CHOICE_BK_THEME_LIGHT, themeList.at(2));
				}
			}
		}
		else
		{
			if (bButtonHover)
			{
				bButtonHover = false;
				InvalidateTheme(currentTheme->GetSettingThemeBkIconID(), currentTheme);
			}
		}
	}
	else if (pMsg->message == WM_LBUTTONUP)
	{
		if (pMsg->hwnd == m_btn_theme_detective.m_hWnd)
		{
			ExecuteSelectTheme(THEME_DETECTIVE);
		}
		else if (pMsg->hwnd == m_btn_theme_cloud.m_hWnd)
		{
			ExecuteSelectTheme(THEME_CLOUD);
		}
		else if (pMsg->hwnd == m_btn_theme_light.m_hWnd)
		{
			ExecuteSelectTheme(THEME_LIGHT);
		}
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}

void SettingTheme::InvalidateTheme(int nSettingThemeBkIconID, ThemeData* hoverTheme)
{
	this->SetBackgroundImage(nSettingThemeBkIconID);
	this->hoverTheme = hoverTheme;
	Invalidate();
	m_btn_theme_detective.DisConnect();
	m_btn_theme_cloud.DisConnect();
	m_btn_theme_light.DisConnect();
	m_btn_theme_none2.DisConnect();
	m_btn_theme_none3.DisConnect();
	m_btn_theme_none4.DisConnect();
	m_btn_theme_none5.DisConnect();
	m_btn_theme_none6.DisConnect();
	m_btn_theme_none7.DisConnect();
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


void SettingTheme::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);
	this->cy = cy;
	SetScrollSize(cy);

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
}

void SettingTheme::SetScrollSize(int nThisHeight)
{
	//nViewHeight = nStartEditSize;// rect.Height() + 120;
	int nScrollMax = 0;
	if (nThisHeight < nViewHeight)
	{
		nScrollMax = nViewHeight - 1;
		nPageSize = nThisHeight;
		nScrollPos = min(nScrollPos, nViewHeight - nPageSize - 1);
	}


	SCROLLINFO si;
	si.fMask = SIF_RANGE | SIF_PAGE | SIF_POS;
	si.nMin = 0;
	si.nMax = nScrollMax;
	si.nPos = nScrollPos;
	si.nPage = nPageSize;
	SetScrollInfo(SB_VERT, &si, TRUE);
}

void SettingTheme::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	int delta = 0;
	switch (nSBCode)
	{
	case SB_LINEUP:
		delta = -m_nBasic;
		break;
	case SB_PAGEUP:
		delta = -nPageSize;
		break;
	case SB_THUMBTRACK:
		delta = static_cast<int>(nPos) - nScrollPos;
		break;
	case SB_PAGEDOWN:
		delta = nPageSize;
		break;
	case SB_LINEDOWN:
		delta = m_nBasic;
		break;
	default:
		return;
	}
	int scrollpos = nScrollPos + delta;
	int nMaxPos = nViewHeight - nPageSize;

	if (scrollpos < 0)
	{
		delta = -nScrollPos;
	}
	else
	{
		if (scrollpos > nMaxPos)
		{
			delta = nMaxPos - nScrollPos;
		}
	}

	if (delta != 0)
	{
		nScrollPos += delta;
		SetScrollPos(SB_VERT, nScrollPos, TRUE);
		ScrollWindow(0, -delta);
		InvalidateTheme(hoverTheme->GetSettingThemeBkIconID(), hoverTheme);
	}
	//CDialogEx::OnVScroll(nSBCode, nPos, pScrollBar);
}


BOOL SettingTheme::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	UINT nFlag;
	if (zDelta > 0)	// 위스크롤
	{
		nFlag = SB_LINEUP;
	}
	else // 아래스크롤
	{
		nFlag = SB_LINEDOWN;
	}

	OnVScroll(nFlag, 0, GetScrollBarCtrl(SB_VERT));
	return CDialogEx::OnMouseWheel(nFlags, zDelta, pt);
}
