
// BaseCalculatorDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "BOKOTools.h"
#include "BOKOToolsDlg.h"
#include "afxdialogex.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
public:
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CBaseCalculatorDlg 대화 상자



CBOKOToolsDlg::CBOKOToolsDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_BASECALCULATOR_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON1);
}

void CBOKOToolsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_ENGINEERING, m_stt_engineering);
	DDX_Control(pDX, IDC_STATIC_BASE, m_stt_base);
	DDX_Control(pDX, IDC_STATIC_CONVERTER, m_stt_converter);
	DDX_Control(pDX, IDC_STATIC_DATE, m_stt_date);
	DDX_Control(pDX, IDC_STATIC_STOPWATCH, m_stt_stopwatch);
	DDX_Control(pDX, IDC_STATIC_TIMER1, m_stt_worktimer);
	DDX_Control(pDX, IDC_BUTTON_BASE_GDI, m_btn_base_gdi);
	DDX_Control(pDX, IDC_BUTTON_CALCULATOR_GDI, m_btn_calculator_gdi);
	DDX_Control(pDX, IDC_BUTTON_STOPWATCH_GDI, m_btn_stopwatch_gdi);
	DDX_Control(pDX, IDC_BUTTON_CONVERTER_GDI, m_btn_converter_gdi);
	DDX_Control(pDX, IDC_BUTTON_DATE_GDI, m_btn_date_gdi);
	DDX_Control(pDX, IDC_BUTTON_TIMER_GDI, m_btn_worktimer_gdi);
	DDX_Control(pDX, IDC_BUTTON_NOTEPAD_GDI, m_btn_notepad_gdi);
	DDX_Control(pDX, IDC_STATIC_NOTEPAD, m_stt_notepad);
	DDX_Control(pDX, IDC_BUTTON_BASE_TIMER_GDI, m_btn_basetimer_gdi);
	DDX_Control(pDX, IDC_STATIC_BASE_TIMER, m_stt_basetimer);
	DDX_Control(pDX, IDC_STATIC_WORLD_CLOCK, m_stt_world_clock);
	DDX_Control(pDX, IDC_BUTTON_WORLD_CLOCK_GDI, m_btn_world_clock_gdi);
	DDX_Control(pDX, IDC_BUTTON_COMINGSOON_GDI1, m_btn_comingsoon_1);
	DDX_Control(pDX, IDC_BUTTON_COMINGSOON_GDI2, m_btn_comingsoon_2);
	DDX_Control(pDX, IDC_BUTTON_COMINGSOON_GDI3, m_btn_comingsoon_3);
}

BEGIN_MESSAGE_MAP(CBOKOToolsDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_BASE_GDI, &CBOKOToolsDlg::OnBnClickedButtonBaseGdi)
	ON_BN_CLICKED(IDC_BUTTON_CALCULATOR_GDI, &CBOKOToolsDlg::OnBnClickedButtonCalculatorGdi)
	ON_BN_CLICKED(IDC_BUTTON_STOPWATCH_GDI, &CBOKOToolsDlg::OnBnClickedButtonStopwatchGdi)
	ON_BN_CLICKED(IDC_BUTTON_CONVERTER_GDI, &CBOKOToolsDlg::OnBnClickedButtonConverterGdi)
	ON_BN_CLICKED(IDC_BUTTON_DATE_GDI, &CBOKOToolsDlg::OnBnClickedButtonDateGdi)
	ON_BN_CLICKED(IDC_BUTTON_TIMER_GDI, &CBOKOToolsDlg::OnBnClickedButtonTimerGdi)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BUTTON_NOTEPAD_GDI, &CBOKOToolsDlg::OnBnClickedButtonNotepadGdi)
	ON_BN_CLICKED(IDC_BUTTON_BASE_TIMER_GDI, &CBOKOToolsDlg::OnBnClickedButtonBaseTimerGdi)
	ON_BN_CLICKED(IDC_BUTTON_WORLD_CLOCK_GDI, &CBOKOToolsDlg::OnBnClickedButtonWorldClockGdi)
	ON_COMMAND(ID_MENU_SETTING_THEME, &CBOKOToolsDlg::OnMenuSettingTheme)
	ON_WM_RBUTTONDOWN()
	ON_COMMAND(ID_MENU_SORT_ICON, &CBOKOToolsDlg::OnMenuSortIcon)
	ON_WM_CLOSE()
	ON_WM_VSCROLL()
	ON_WM_MOUSEWHEEL()
END_MESSAGE_MAP()


// CBaseCalculatorDlg 메시지 처리기

BOOL CBOKOToolsDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.

	LoadTheme();


	bBase = false;
	bEngineering = false;
	bConverter = false;
	bDate = false;
	bStopWatch = false;
	bTimer = false;
	bNotepad = false;
	nPageCount = 0;
	nCtlItemCount = 0;

	//m_returnBrush.CreateSolidBrush(RGB(35, 35, 35));

	m_stt_engineering.Initialize(15, _T("고딕"));
	m_stt_base.Initialize(15, _T("고딕"));
	m_stt_converter.Initialize(15, _T("고딕"));
	m_stt_date.Initialize(15, _T("고딕"));
	m_stt_stopwatch.Initialize(15, _T("고딕"));
	m_stt_worktimer.Initialize(15, _T("고딕"));
	m_stt_notepad.Initialize(15, _T("고딕"));
	m_stt_basetimer.Initialize(15, _T("고딕"));
	m_stt_world_clock.Initialize(15, _T("고딕"));

	LoadUserInterface(currentTheme);
	
	m_btn_base_gdi.ModifyStyle(0, WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 0);
	m_stt_base.ModifyStyle(0, WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 0);
	m_btn_calculator_gdi.ModifyStyle(0, WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 0);
	m_stt_engineering.ModifyStyle(0, WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 0);
	m_btn_stopwatch_gdi.ModifyStyle(0, WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 0);
	m_stt_stopwatch.ModifyStyle(0, WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 0);
	m_btn_converter_gdi.ModifyStyle(0, WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 0);
	m_stt_converter.ModifyStyle(0, WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 0);
	m_btn_date_gdi.ModifyStyle(0, WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 0);
	m_stt_date.ModifyStyle(0, WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 0);
	m_btn_worktimer_gdi.ModifyStyle(0, WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 0);
	m_stt_worktimer.ModifyStyle(0, WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 0);
	m_btn_notepad_gdi.ModifyStyle(0, WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 0);
	m_stt_notepad.ModifyStyle(0, WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 0);
	m_btn_basetimer_gdi.ModifyStyle(0, WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 0);
	m_stt_basetimer.ModifyStyle(0, WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 0);
	m_btn_world_clock_gdi.ModifyStyle(0, WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 0);
	m_stt_world_clock.ModifyStyle(0, WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 0);

	m_btn_base_gdi.BringWindowToTop();
	m_btn_calculator_gdi.BringWindowToTop();
	m_btn_stopwatch_gdi.BringWindowToTop();
	m_btn_converter_gdi.BringWindowToTop();
	m_btn_date_gdi.BringWindowToTop();
	m_btn_worktimer_gdi.BringWindowToTop();
	m_stt_base.BringWindowToTop();
	m_stt_engineering.BringWindowToTop();
	m_stt_stopwatch.BringWindowToTop();
	m_stt_converter.BringWindowToTop();
	m_stt_date.BringWindowToTop();
	m_stt_worktimer.BringWindowToTop();
	m_stt_notepad.BringWindowToTop();
	m_stt_basetimer.BringWindowToTop();
	m_stt_world_clock.BringWindowToTop();

	//SetCtlPos();
	LoadButtonPos();

	AfxEnableControlContainer();
	AfxInitRichEdit2();
	
	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CBOKOToolsDlg::LoadButtonPos()
{
	// xml 미존재시 creat 존재시 load
	// setctlpos에서 lineend 설정 

	int nThemeFlags = 0;
	bool bSavedXml = false;
	CMarkup markUp;

	CString szRoot = _T("");
	CreateConfigPosFile(szRoot);

	CString strFullPath = szRoot + _T("\\ButtonPos.conf");

	std::vector<std::vector<int>> buttonCtlPosVector;

	if (markUp.Load(strFullPath))
	{
		markUp.FindElem(_T("Position"));
		markUp.IntoElem();
		while (markUp.FindElem(_T("button")))
		{
			int nButtonCtlID = _ttoi(markUp.GetAttrib(_T("bid")));
			int nStaticCtlID = _ttoi(markUp.GetAttrib(_T("sid")));
			int nButtonPos_x = _ttoi(markUp.GetAttrib(_T("posx")));
			int nButtonPos_y = _ttoi(markUp.GetAttrib(_T("posy")));

			std::vector<int> pos;
			pos.push_back(nButtonCtlID);
			pos.push_back(nStaticCtlID);
			pos.push_back(nButtonPos_x);
			pos.push_back(nButtonPos_y);
			buttonCtlPosVector.push_back(pos);
		}
	}
	else
	{
		CString szRoot = _T("");

		CreateConfigPosFile(szRoot);
		if (CreateDefaultPosXml(&markUp, szRoot, buttonCtlPosVector)) bSavedXml = true;
		if (bSavedXml)
		{
			SaveXml(&markUp, szRoot + _T("\\ButtonPos.conf"));
		}
	}

	SetCtlPos(buttonCtlPosVector);
}

void CBOKOToolsDlg::ResetScrollAndButton()
{
	scroll.Destroy();
	ctlItemVector.clear();
	nCtlItemCount = 0;
	nPageCount = 0;
}

void CBOKOToolsDlg::LoadUserInterface(ThemeData* currentTheme)
{
	this->SetBackgroundImage(currentTheme->GetMainBkIconID());

	ButtonCtlDisConnect();

	m_btn_base_gdi.SetClickSound(currentTheme->GetButtonSoundPath());
	m_btn_base_gdi.LoadStdImage(currentTheme->GetBaseIcon().nNormalID, _T("PNG"));
	m_btn_base_gdi.LoadHovImage(currentTheme->GetBaseIcon().nHoverID, _T("PNG"));
	m_btn_base_gdi.LoadAltImage(currentTheme->GetBaseIcon().nClickID, _T("PNG"));

	m_btn_calculator_gdi.SetClickSound(currentTheme->GetButtonSoundPath());
	m_btn_calculator_gdi.LoadStdImage(currentTheme->GetEngineeringIcon().nNormalID, _T("PNG"));
	m_btn_calculator_gdi.LoadHovImage(currentTheme->GetEngineeringIcon().nHoverID, _T("PNG"));
	m_btn_calculator_gdi.LoadAltImage(currentTheme->GetEngineeringIcon().nClickID, _T("PNG"));

	m_btn_stopwatch_gdi.SetClickSound(currentTheme->GetButtonSoundPath());
	m_btn_stopwatch_gdi.LoadStdImage(currentTheme->GetStopWatchIcon().nNormalID, _T("PNG"));
	m_btn_stopwatch_gdi.LoadHovImage(currentTheme->GetStopWatchIcon().nHoverID, _T("PNG"));
	m_btn_stopwatch_gdi.LoadAltImage(currentTheme->GetStopWatchIcon().nClickID, _T("PNG"));

	m_btn_converter_gdi.SetClickSound(currentTheme->GetButtonSoundPath());
	m_btn_converter_gdi.LoadStdImage(currentTheme->GetConverterIcon().nNormalID, _T("PNG"));
	m_btn_converter_gdi.LoadHovImage(currentTheme->GetConverterIcon().nHoverID, _T("PNG"));
	m_btn_converter_gdi.LoadAltImage(currentTheme->GetConverterIcon().nClickID, _T("PNG"));

	m_btn_date_gdi.SetClickSound(currentTheme->GetButtonSoundPath());
	m_btn_date_gdi.LoadStdImage(currentTheme->GetDateCalIcon().nNormalID, _T("PNG"));
	m_btn_date_gdi.LoadHovImage(currentTheme->GetDateCalIcon().nHoverID, _T("PNG"));
	m_btn_date_gdi.LoadAltImage(currentTheme->GetDateCalIcon().nClickID, _T("PNG"));

	m_btn_worktimer_gdi.SetClickSound(currentTheme->GetButtonSoundPath());
	m_btn_worktimer_gdi.LoadStdImage(currentTheme->GetWorkTimerIcon().nNormalID, _T("PNG"));
	m_btn_worktimer_gdi.LoadHovImage(currentTheme->GetWorkTimerIcon().nHoverID, _T("PNG"));
	m_btn_worktimer_gdi.LoadAltImage(currentTheme->GetWorkTimerIcon().nClickID, _T("PNG"));

	m_btn_notepad_gdi.SetClickSound(currentTheme->GetButtonSoundPath());
	m_btn_notepad_gdi.LoadStdImage(currentTheme->GetNotePadIcon().nNormalID, _T("PNG"));
	m_btn_notepad_gdi.LoadHovImage(currentTheme->GetNotePadIcon().nHoverID, _T("PNG"));
	m_btn_notepad_gdi.LoadAltImage(currentTheme->GetNotePadIcon().nClickID, _T("PNG"));

	m_btn_basetimer_gdi.SetClickSound(currentTheme->GetButtonSoundPath());
	m_btn_basetimer_gdi.LoadStdImage(currentTheme->GetBaseTimerIcon().nNormalID, _T("PNG"));
	m_btn_basetimer_gdi.LoadHovImage(currentTheme->GetBaseTimerIcon().nHoverID, _T("PNG"));
	m_btn_basetimer_gdi.LoadAltImage(currentTheme->GetBaseTimerIcon().nClickID, _T("PNG"));

	m_btn_world_clock_gdi.SetClickSound(currentTheme->GetButtonSoundPath());
	m_btn_world_clock_gdi.LoadStdImage(currentTheme->GetWorldClockIcon().nNormalID, _T("PNG"));
	m_btn_world_clock_gdi.LoadHovImage(currentTheme->GetWorldClockIcon().nHoverID, _T("PNG"));
	m_btn_world_clock_gdi.LoadAltImage(currentTheme->GetWorldClockIcon().nClickID, _T("PNG"));

	m_btn_comingsoon_1.LoadStdImage(currentTheme->GetCommingSoonIcon().nNormalID, _T("PNG"));
	m_btn_comingsoon_1.LoadHovImage(currentTheme->GetCommingSoonIcon().nNormalID, _T("PNG"));
	m_btn_comingsoon_1.LoadAltImage(currentTheme->GetCommingSoonIcon().nNormalID, _T("PNG"));

	m_btn_comingsoon_2.LoadStdImage(currentTheme->GetCommingSoonIcon().nNormalID, _T("PNG"));
	m_btn_comingsoon_2.LoadHovImage(currentTheme->GetCommingSoonIcon().nNormalID, _T("PNG"));
	m_btn_comingsoon_2.LoadAltImage(currentTheme->GetCommingSoonIcon().nNormalID, _T("PNG"));

	m_btn_comingsoon_3.LoadStdImage(currentTheme->GetCommingSoonIcon().nNormalID, _T("PNG"));
	m_btn_comingsoon_3.LoadHovImage(currentTheme->GetCommingSoonIcon().nNormalID, _T("PNG"));
	m_btn_comingsoon_3.LoadAltImage(currentTheme->GetCommingSoonIcon().nNormalID, _T("PNG"));
}

void CBOKOToolsDlg::LoadTheme()
{
	// 테마 추가되면 설정하기
	ThemeData* theme1 = new ThemeData(THEME_DETECTIVE);
	ThemeData* theme2 = new ThemeData(THEME_CLOUD);
	ThemeData* theme3 = new ThemeData(THEME_LIGHT);
	ThemeData* theme4 = new ThemeData(THEME_MAGNIFIER);
	ThemeData* theme5 = new ThemeData(THEME_INK);

	themeList.push_back(theme1);
	themeList.push_back(theme2);
	themeList.push_back(theme3);
	themeList.push_back(theme4);
	themeList.push_back(theme5);
	int nFlags = LoadCurrnetTheme();

	if (nFlags == THEME_DETECTIVE)
	{
		currentTheme = theme1;
	}
	else if (nFlags == THEME_CLOUD)
	{
		currentTheme = theme2;
	}
	else if (nFlags == THEME_LIGHT)
	{
		currentTheme = theme3;
	}
	else if (nFlags == THEME_MAGNIFIER)
	{
		currentTheme = theme4;
	}
	else if (nFlags == THEME_INK)
	{
		currentTheme = theme5;
	}
}

int CBOKOToolsDlg::LoadCurrnetTheme()
{
	int nThemeFlags = 0;
	bool bSavedXml = false;
	CMarkup markUp;
	CString strFullPath = _T("Config\\Theme\\ThemeSetting.conf");
	if (markUp.Load(strFullPath))
	{
		markUp.FindElem(_T("Theme"));
		markUp.IntoElem();
		if (markUp.FindElem(_T("class")))
		{
			CString strThemeFlags = markUp.GetAttrib(_T("value"));
			nThemeFlags = _ttoi(strThemeFlags);
		}
	}
	else
	{
		CString szRoot = _T("");

		CreateConfigThemeFile(szRoot);
		if (CreateDefaultThemeXml(&markUp, szRoot, nThemeFlags)) bSavedXml = true;
		if (bSavedXml)
		{
			SaveXml(&markUp, szRoot + _T("\\ThemeSetting.conf"));
		}
	}
	return nThemeFlags;
}

void CBOKOToolsDlg::SaveXml(CMarkup* markup, CString strSaveFullPath)
{
	CString strXML = markup->GetDoc();

	HRESULT hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);
	JWXml::CXml saveXML;
	saveXML.LoadXml((LPCTSTR)strXML);
	saveXML.SaveWithFormatted(strSaveFullPath);
	saveXML.Close();
	CoUninitialize();
}

void CBOKOToolsDlg::CreateConfigPosFile(CString& strFullPath)
{
	TCHAR chFilePath[256] = { 0, };
	GetModuleFileName(NULL, chFilePath, 256);
	strFullPath = (LPCTSTR)chFilePath;
	int nLen = strFullPath.ReverseFind('\\');

	if (nLen > 0)
	{
		strFullPath = strFullPath.Left(nLen);
	}

	CFileFind rootFind;
	if (rootFind.FindFile(strFullPath + _T("\\BOKOTools"))) {
		strFullPath += _T("\\BOKOTools");
	}
	rootFind.Close();

	CreateDefaultDirectory(strFullPath, _T("\\Config"));
	CreateDefaultDirectory(strFullPath, _T("\\ButtonPos"));
}

bool CBOKOToolsDlg::CreateDefaultPosXml(CMarkup* markUp, CString strFilePath, std::vector<std::vector<int>>& buttonCtlPosVector)
{
	bool bReturn = false;
	CFileFind xmlFind;
	strFilePath += _T("\\ButtonPos.conf");
	if (!xmlFind.FindFile(strFilePath))
	{
		markUp->AddElem(_T("Position"));
		markUp->IntoElem();
		markUp->AddElem(_T("button"));
		markUp->AddAttrib(_T("bid"), IDC_BUTTON_BASE_GDI);
		markUp->AddAttrib(_T("sid"), IDC_STATIC_BASE);
		markUp->AddAttrib(_T("posx"), 1);
		markUp->AddAttrib(_T("posy"), 1);
		markUp->AddElem(_T("button"));
		markUp->AddAttrib(_T("bid"), IDC_BUTTON_CALCULATOR_GDI);
		markUp->AddAttrib(_T("sid"), IDC_STATIC_ENGINEERING);
		markUp->AddAttrib(_T("posx"), 2);
		markUp->AddAttrib(_T("posy"), 1);
		markUp->AddElem(_T("button"));
		markUp->AddAttrib(_T("bid"), IDC_BUTTON_STOPWATCH_GDI);
		markUp->AddAttrib(_T("sid"), IDC_STATIC_STOPWATCH);
		markUp->AddAttrib(_T("posx"), 3);
		markUp->AddAttrib(_T("posy"), 1);
		markUp->AddElem(_T("button"));
		markUp->AddAttrib(_T("bid"), IDC_BUTTON_CONVERTER_GDI);
		markUp->AddAttrib(_T("sid"), IDC_STATIC_CONVERTER);
		markUp->AddAttrib(_T("posx"), 1);
		markUp->AddAttrib(_T("posy"), 2);
		markUp->AddElem(_T("button"));
		markUp->AddAttrib(_T("bid"), IDC_BUTTON_DATE_GDI);
		markUp->AddAttrib(_T("sid"), IDC_STATIC_DATE);
		markUp->AddAttrib(_T("posx"), 2);
		markUp->AddAttrib(_T("posy"), 2);
		markUp->AddElem(_T("button"));
		markUp->AddAttrib(_T("bid"), IDC_BUTTON_TIMER_GDI);
		markUp->AddAttrib(_T("sid"), IDC_STATIC_TIMER1);
		markUp->AddAttrib(_T("posx"), 3);
		markUp->AddAttrib(_T("posy"), 2);
		markUp->AddElem(_T("button"));
		markUp->AddAttrib(_T("bid"), IDC_BUTTON_NOTEPAD_GDI);
		markUp->AddAttrib(_T("sid"), IDC_STATIC_NOTEPAD);
		markUp->AddAttrib(_T("posx"), 1);
		markUp->AddAttrib(_T("posy"), 3);
		markUp->AddElem(_T("button"));
		markUp->AddAttrib(_T("bid"), IDC_BUTTON_BASE_TIMER_GDI);
		markUp->AddAttrib(_T("sid"), IDC_STATIC_BASE_TIMER);
		markUp->AddAttrib(_T("posx"), 2);
		markUp->AddAttrib(_T("posy"), 3);
		markUp->AddElem(_T("button"));
		markUp->AddAttrib(_T("bid"), IDC_BUTTON_WORLD_CLOCK_GDI);
		markUp->AddAttrib(_T("sid"), IDC_STATIC_WORLD_CLOCK);
		markUp->AddAttrib(_T("posx"), 3);
		markUp->AddAttrib(_T("posy"), 3);
		markUp->AddElem(_T("button"));
		markUp->AddAttrib(_T("bid"), IDC_BUTTON_COMINGSOON_GDI1);
		markUp->AddAttrib(_T("sid"), 0);
		markUp->AddAttrib(_T("posx"), 1);
		markUp->AddAttrib(_T("posy"), 4);
		markUp->AddElem(_T("button"));
		markUp->AddAttrib(_T("bid"), IDC_BUTTON_COMINGSOON_GDI2);
		markUp->AddAttrib(_T("sid"), 0);
		markUp->AddAttrib(_T("posx"), 2);
		markUp->AddAttrib(_T("posy"), 4);
		markUp->AddElem(_T("button"));
		markUp->AddAttrib(_T("bid"), IDC_BUTTON_COMINGSOON_GDI3);
		markUp->AddAttrib(_T("sid"), 0);
		markUp->AddAttrib(_T("posx"), 3);
		markUp->AddAttrib(_T("posy"), 4);

		buttonCtlPosVector.push_back({ IDC_BUTTON_BASE_GDI ,IDC_STATIC_BASE, 1, 1 });
		buttonCtlPosVector.push_back({ IDC_BUTTON_CALCULATOR_GDI ,IDC_STATIC_ENGINEERING, 2, 1 });
		buttonCtlPosVector.push_back({ IDC_BUTTON_STOPWATCH_GDI ,IDC_STATIC_STOPWATCH, 3, 1 });
		buttonCtlPosVector.push_back({ IDC_BUTTON_CONVERTER_GDI ,IDC_STATIC_CONVERTER, 1, 2 });
		buttonCtlPosVector.push_back({ IDC_BUTTON_DATE_GDI ,IDC_STATIC_DATE, 2, 2 });
		buttonCtlPosVector.push_back({ IDC_BUTTON_TIMER_GDI ,IDC_STATIC_TIMER1, 3, 2 });
		buttonCtlPosVector.push_back({ IDC_BUTTON_NOTEPAD_GDI ,IDC_STATIC_NOTEPAD, 1, 3 });
		buttonCtlPosVector.push_back({ IDC_BUTTON_BASE_TIMER_GDI ,IDC_STATIC_BASE_TIMER, 2, 3 });
		buttonCtlPosVector.push_back({ IDC_BUTTON_WORLD_CLOCK_GDI ,IDC_STATIC_WORLD_CLOCK, 3, 3 });
		buttonCtlPosVector.push_back({ IDC_BUTTON_COMINGSOON_GDI1 ,0, 1, 4 });
		buttonCtlPosVector.push_back({ IDC_BUTTON_COMINGSOON_GDI2 ,0, 2, 4 });
		buttonCtlPosVector.push_back({ IDC_BUTTON_COMINGSOON_GDI3 ,0, 3, 4 });

		bReturn = true;
	}
	xmlFind.Close();

	return bReturn;
}

void CBOKOToolsDlg::CreateConfigThemeFile(CString& strFullPath)
{
	TCHAR chFilePath[256] = { 0, };
	GetModuleFileName(NULL, chFilePath, 256);
	strFullPath = (LPCTSTR)chFilePath;
	int nLen = strFullPath.ReverseFind('\\');

	if (nLen > 0)
	{
		strFullPath = strFullPath.Left(nLen);
	}

	CFileFind rootFind;
	if (rootFind.FindFile(strFullPath + _T("\\BOKOTools"))) {
		strFullPath += _T("\\BOKOTools");
	}
	rootFind.Close();

	CreateDefaultDirectory(strFullPath, _T("\\Config"));
	CreateDefaultDirectory(strFullPath, _T("\\Theme"));
}

void CBOKOToolsDlg::CreateDefaultDirectory(CString& strFullPath, CString strAppendPath)
{
	CFileFind findPath;
	strFullPath += strAppendPath;
	if (!findPath.FindFile(strFullPath))
	{
		CreateDirectory(strFullPath, NULL);
	}
	findPath.Close();
}

bool CBOKOToolsDlg::CreateDefaultThemeXml(CMarkup* markUp, CString strFilePath, int& nThemeFlags)
{
	bool bReturn = false;
	CFileFind xmlFind;
	strFilePath += _T("\\ThemeSetting.conf");
	if (!xmlFind.FindFile(strFilePath))
	{
		markUp->AddElem(_T("Theme"));
		markUp->IntoElem();
		markUp->AddElem(_T("class"));
		markUp->AddAttrib(_T("value"), _T("0"));
		nThemeFlags = 0;
		bReturn = true;
	}
	xmlFind.Close();

	return bReturn;
}

void CBOKOToolsDlg::SetWhichSelectCtlItemPos(int nButtonCtlID, int nStaticCtlId, int nPos_x, int nPos_y)
{
	int nCtlPos_X = LEFT_MARGIN;
	int nCtlPos_Y = TOP_MARGIN;

	nCtlPos_X += (PICTURE_WIDTH + PICTURE_TO_PICTURE_MARGIN_WIDTH) * (nPos_x - 1);
	nCtlPos_Y += (PICTURE_HEIGHT + PICTURE_TO_PICTURE_MARGIN_HEIGHT) * (nPos_y - 1);

	if (nPageCount >= 9 && nPageCount < 12)
	{
		nCtlPos_Y -= (PICTURE_HEIGHT + PICTURE_TO_PICTURE_MARGIN_HEIGHT);
		nCtlPos_Y += (PICTURE_HEIGHT + PICTURE_TO_PICTURE_MARGIN_HEIGHT + 47 + 60 - 6);
	}

	if (nButtonCtlID != 0) this->GetDlgItem(nButtonCtlID)->MoveWindow(nCtlPos_X, nCtlPos_Y, PICTURE_WIDTH, PICTURE_HEIGHT);
	if (nStaticCtlId != 0) this->GetDlgItem(nStaticCtlId)->MoveWindow(nCtlPos_X, nCtlPos_Y + PICTURE_HEIGHT, PICTURE_WIDTH, STATIC_HEIGHT);
	
	if (nPageCount == 11) nPageCount = 2;

	nCtlItemCount++;
	nPageCount++;

	std::vector<int> ctlVector = { nButtonCtlID , nStaticCtlId , nCtlItemCount };
	ctlItemVector.push_back(ctlVector);
}

void CBOKOToolsDlg::SetCtlPos(std::vector<std::vector<int>> buttonCtlPosVector)
{
	ResetScrollAndButton();

	scroll.Create(this);
	CustomScroll::CustomScrollInfo csi;
	csi.cst = CustomScroll::CUSTOM_SCROLL_TYPE_BUTTON;
	csi.nAllPageSize = 0;
	csi.nKindOfScrollFlags = SB_VERT;
	csi.nOnePageSize = 597 - 30 + 9;
	csi.nScrollPos = 0;
	scroll.Initialize(csi);

	m_btn_base_gdi.ShowWindow(SW_HIDE);
	m_btn_calculator_gdi.ShowWindow(SW_HIDE);
	m_btn_stopwatch_gdi.ShowWindow(SW_HIDE);
	m_btn_converter_gdi.ShowWindow(SW_HIDE);
	m_btn_date_gdi.ShowWindow(SW_HIDE);
	m_btn_worktimer_gdi.ShowWindow(SW_HIDE);
	m_btn_notepad_gdi.ShowWindow(SW_HIDE);
	m_btn_basetimer_gdi.ShowWindow(SW_HIDE);
	m_btn_world_clock_gdi.ShowWindow(SW_HIDE);
	m_btn_comingsoon_1.ShowWindow(SW_HIDE);
	m_btn_comingsoon_2.ShowWindow(SW_HIDE);
	m_btn_comingsoon_3.ShowWindow(SW_HIDE);
	m_stt_engineering.ShowWindow(SW_HIDE);
	m_stt_base.ShowWindow(SW_HIDE);
	m_stt_converter.ShowWindow(SW_HIDE);
	m_stt_date.ShowWindow(SW_HIDE);
	m_stt_stopwatch.ShowWindow(SW_HIDE);
	m_stt_worktimer.ShowWindow(SW_HIDE);
	m_stt_notepad.ShowWindow(SW_HIDE);
	m_stt_basetimer.ShowWindow(SW_HIDE);
	m_stt_world_clock.ShowWindow(SW_HIDE);

	for (int i = 0; i < (int)buttonCtlPosVector.size(); i++)
	{
		SetWhichSelectCtlItemPos(buttonCtlPosVector.at(i).at(0), buttonCtlPosVector.at(i).at(1), buttonCtlPosVector.at(i).at(2), buttonCtlPosVector.at(i).at(3));

		if (buttonCtlPosVector.at(i).at(0) == IDC_BUTTON_BASE_GDI)
		{
			m_btn_base_gdi.ShowWindow(SW_SHOW);
			m_stt_base.ShowWindow(SW_SHOW);
		}
		else if (buttonCtlPosVector.at(i).at(0) == IDC_BUTTON_CALCULATOR_GDI)
		{
			m_btn_calculator_gdi.ShowWindow(SW_SHOW);
			m_stt_engineering.ShowWindow(SW_SHOW);
		}
		else if (buttonCtlPosVector.at(i).at(0) == IDC_BUTTON_STOPWATCH_GDI)
		{
			m_btn_stopwatch_gdi.ShowWindow(SW_SHOW);
			m_stt_stopwatch.ShowWindow(SW_SHOW);
		}
		else if (buttonCtlPosVector.at(i).at(0) == IDC_BUTTON_CONVERTER_GDI)
		{
			m_btn_converter_gdi.ShowWindow(SW_SHOW);
			m_stt_converter.ShowWindow(SW_SHOW);
		}
		else if (buttonCtlPosVector.at(i).at(0) == IDC_BUTTON_DATE_GDI)
		{
			m_btn_date_gdi.ShowWindow(SW_SHOW);
			m_stt_date.ShowWindow(SW_SHOW);
		}
		else if (buttonCtlPosVector.at(i).at(0) == IDC_BUTTON_DATE_GDI)
		{
			m_btn_date_gdi.ShowWindow(SW_SHOW);
			m_stt_date.ShowWindow(SW_SHOW);
		}
		else if (buttonCtlPosVector.at(i).at(0) == IDC_BUTTON_TIMER_GDI)
		{
			m_btn_worktimer_gdi.ShowWindow(SW_SHOW);
			m_stt_worktimer.ShowWindow(SW_SHOW);
		}
		else if (buttonCtlPosVector.at(i).at(0) == IDC_BUTTON_NOTEPAD_GDI)
		{
			m_btn_notepad_gdi.ShowWindow(SW_SHOW);
			m_stt_notepad.ShowWindow(SW_SHOW);
		}
		else if (buttonCtlPosVector.at(i).at(0) == IDC_BUTTON_BASE_TIMER_GDI)
		{
			m_btn_basetimer_gdi.ShowWindow(SW_SHOW);
			m_stt_basetimer.ShowWindow(SW_SHOW);
		}
		else if (buttonCtlPosVector.at(i).at(0) == IDC_BUTTON_WORLD_CLOCK_GDI)
		{
			m_btn_world_clock_gdi.ShowWindow(SW_SHOW);
			m_stt_world_clock.ShowWindow(SW_SHOW);
		}
		else if (buttonCtlPosVector.at(i).at(0) == IDC_BUTTON_COMINGSOON_GDI1)
		{
			m_btn_comingsoon_1.ShowWindow(SW_SHOW);
		}
		else if (buttonCtlPosVector.at(i).at(0) == IDC_BUTTON_COMINGSOON_GDI2)
		{
			m_btn_comingsoon_2.ShowWindow(SW_SHOW);
		}
		else if (buttonCtlPosVector.at(i).at(0) == IDC_BUTTON_COMINGSOON_GDI3)
		{
			m_btn_comingsoon_3.ShowWindow(SW_SHOW);
		}

		bool bEnd = true;
		if ((i + 1) % 9 == 0)
		{
			bEnd = false;
			scroll.LineEnd();
		}
		if (bEnd)
		{
			if (i == (int)buttonCtlPosVector.size() - 1)
			{
				scroll.LineEnd();
			}
		}
	}

	//// 첫번째 페이지
	//{
	//	// 첫재줄
	//	SetWhichSelectCtlItemPos(m_btn_base_gdi.GetDlgCtrlID(), m_stt_base.GetDlgCtrlID(), 1, 1);
	//	SetWhichSelectCtlItemPos(m_btn_calculator_gdi.GetDlgCtrlID(), m_stt_engineering.GetDlgCtrlID(), 2, 1);
	//	SetWhichSelectCtlItemPos(m_btn_stopwatch_gdi.GetDlgCtrlID(), m_stt_stopwatch.GetDlgCtrlID(), 3, 1);

	//	// 두번째줄
	//	SetWhichSelectCtlItemPos(m_btn_converter_gdi.GetDlgCtrlID(), m_stt_converter.GetDlgCtrlID(), 1, 2);
	//	SetWhichSelectCtlItemPos(m_btn_date_gdi.GetDlgCtrlID(), m_stt_date.GetDlgCtrlID(), 2, 2);
	//	SetWhichSelectCtlItemPos(m_btn_worktimer_gdi.GetDlgCtrlID(), m_stt_worktimer.GetDlgCtrlID(), 3, 2);

	//	// 셋째줄
	//	SetWhichSelectCtlItemPos(m_btn_notepad_gdi.GetDlgCtrlID(), m_stt_notepad.GetDlgCtrlID(), 1, 3);
	//	SetWhichSelectCtlItemPos(m_btn_basetimer_gdi.GetDlgCtrlID(), m_stt_basetimer.GetDlgCtrlID(), 2, 3);
	//	SetWhichSelectCtlItemPos(m_btn_world_clock_gdi.GetDlgCtrlID(), m_stt_world_clock.GetDlgCtrlID(), 3, 3);
	//}
	//scroll.LineEnd();

	//// 두번째 페이지
	//{
	//	SetWhichSelectCtlItemPos(m_btn_comingsoon_1.GetDlgCtrlID(), 0, 1, 4);
	//	SetWhichSelectCtlItemPos(m_btn_comingsoon_2.GetDlgCtrlID(), 0, 2, 4);
	//	SetWhichSelectCtlItemPos(m_btn_comingsoon_3.GetDlgCtrlID(), 0, 3, 4);
	//}
	//scroll.LineEnd();

	CRect SystemRect;
	CPoint pos;
	GetClientRect(SystemRect);
	pos.x = LONG(GetSystemMetrics(SM_CXSCREEN) / 2.0f - SystemRect.Width() / 2.0f);
	pos.y = LONG(GetSystemMetrics(SM_CYSCREEN) / 2.0f - SystemRect.Height() / 2.0f);

	// 윈도우의 다이얼로그 사이즈는 양옆 위아래로 9씩의 마진값과 상단 타이틀의 38의 마진값을 가진다.
	// 그래서 사이즈 조정시 넓이 + 18, 높이 + 47을 입력해야한다.
	//this->MoveWindow(pos.x, pos.y, nVector_X, nVector_Y);
	this->MoveWindow(pos.x, pos.y, MARGIN_X(730), MARGIN_Y(550));

	scroll.ExecuteScrollPos(currentTheme);
}

void CBOKOToolsDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CBOKOToolsDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}

}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CBOKOToolsDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CBOKOToolsDlg::OnOK()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	//CDialogEx::OnOK();
}

BOOL CBOKOToolsDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	if (pMsg->message == WM_MOUSEMOVE)
	{
		if (pMsg->hwnd == m_btn_base_gdi)
		{
			HCURSOR hCursor = AfxGetApp()->LoadStandardCursor(IDC_HAND);
			SetCursor(hCursor);
		}
		else if (pMsg->hwnd == m_btn_calculator_gdi)
		{
			HCURSOR hCursor = AfxGetApp()->LoadStandardCursor(IDC_HAND);
			SetCursor(hCursor);
		}
		else if (pMsg->hwnd == m_btn_stopwatch_gdi)
		{
			HCURSOR hCursor = AfxGetApp()->LoadStandardCursor(IDC_HAND);
			SetCursor(hCursor);
		}
		else if (pMsg->hwnd == m_btn_converter_gdi)
		{
			HCURSOR hCursor = AfxGetApp()->LoadStandardCursor(IDC_HAND);
			SetCursor(hCursor);
		}
		else if (pMsg->hwnd == m_btn_date_gdi)
		{
			HCURSOR hCursor = AfxGetApp()->LoadStandardCursor(IDC_HAND);
			SetCursor(hCursor);
		}
		else if (pMsg->hwnd == m_btn_worktimer_gdi)
		{
			HCURSOR hCursor = AfxGetApp()->LoadStandardCursor(IDC_HAND);
			SetCursor(hCursor);
		}
		else if (pMsg->hwnd == m_btn_notepad_gdi)
		{
			HCURSOR hCursor = AfxGetApp()->LoadStandardCursor(IDC_HAND);
			SetCursor(hCursor);
		}
		else if (pMsg->hwnd == m_btn_basetimer_gdi)
		{
			HCURSOR hCursor = AfxGetApp()->LoadStandardCursor(IDC_HAND);
			SetCursor(hCursor);
		}
		else if (pMsg->hwnd == m_btn_world_clock_gdi)
		{
			HCURSOR hCursor = AfxGetApp()->LoadStandardCursor(IDC_HAND);
			SetCursor(hCursor);
		}
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}



void CBOKOToolsDlg::OnBnClickedButtonBaseGdi()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (!bBase)
	{
		base = new BaseCalculate(currentTheme, this);
		base->Create(IDD_DIALOG_BASE, GetDesktopWindow());
		base->ShowWindow(SW_SHOW);
		bBase = true;
	}
}


void CBOKOToolsDlg::OnBnClickedButtonCalculatorGdi()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (!bEngineering)
	{
		engineering = new EngineeringCalculate(currentTheme, this);
		engineering->Create(IDD_DIALOG_ENGINEERING, GetDesktopWindow());
		engineering->ShowWindow(SW_SHOW);
		bEngineering = true;
	}
}


void CBOKOToolsDlg::OnBnClickedButtonStopwatchGdi()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (!bStopWatch)
	{
		stopwatch = new StopWatch(currentTheme, this);
		stopwatch->Create(IDD_DIALOG_STOPWATCH, GetDesktopWindow());
		stopwatch->ShowWindow(SW_SHOW);
		bStopWatch = true;
	}

}


void CBOKOToolsDlg::OnBnClickedButtonConverterGdi()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (!bConverter)
	{
		converter = new UnitConverter(currentTheme, this);
		converter->Create(IDD_DIALOG_CONVERTER, GetDesktopWindow());
		converter->ShowWindow(SW_SHOW);
		bConverter = true;
	}
}


void CBOKOToolsDlg::OnBnClickedButtonDateGdi()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (!bDate)
	{
		date = new DateCalculate(currentTheme, this);
		date->Create(IDD_DIALOG_DATE, GetDesktopWindow());
		date->ShowWindow(SW_SHOW);
		bDate = true;
	}
}


void CBOKOToolsDlg::OnBnClickedButtonTimerGdi()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (!bTimer)
	{
		timer = new Timer(currentTheme, this);
		timer->Create(IDD_DIALOG_TIMER, GetDesktopWindow());
		timer->ShowWindow(SW_SHOW);
		bTimer = true;
	}
}


void CBOKOToolsDlg::OnBnClickedButtonNotepadGdi()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (!bNotepad)
	{
		notepad = new NotePad(currentTheme, this);
		notepad->Create(IDD_DIALOG_NOTEPAD, GetDesktopWindow());
		notepad->ShowWindow(SW_SHOW);
		bNotepad = true;
	}
}

void CBOKOToolsDlg::OnBnClickedButtonBaseTimerGdi()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (!bBaseTimer)
	{
		basetimer = new BaseTimer(currentTheme, this);
		basetimer->Create(IDD_DIALOG_BASE_TIMER, GetDesktopWindow());
		basetimer->ShowWindow(SW_SHOW);
		bBaseTimer = true;
	}
}

void CBOKOToolsDlg::OnBnClickedButtonWorldClockGdi()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (!bWorldClock)
	{
		worldclock = new WorldClock(currentTheme, this);
		worldclock->Create(IDD_DIALOG_WORLD_CLOCK, GetDesktopWindow());
		worldclock->ShowWindow(SW_SHOW);
		bWorldClock = true;
	}
}

HBRUSH CBOKOToolsDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);
	
	// TODO:  여기서 DC의 특성을 변경합니다.
	if (nCtlColor == CTLCOLOR_STATIC)
	{
		if (pWnd->GetDlgCtrlID() == IDC_STATIC_BASE)
		{
			if (currentTheme)
			{
				pDC->SetTextColor(currentTheme->GetTextColor());
			}
		}
		else if (pWnd->GetDlgCtrlID() == IDC_STATIC_ENGINEERING)
		{
			if (currentTheme)
			{
				pDC->SetTextColor(currentTheme->GetTextColor());
			}
		}
		else if (pWnd->GetDlgCtrlID() == IDC_STATIC_STOPWATCH)
		{
			if (currentTheme)
			{
				pDC->SetTextColor(currentTheme->GetTextColor());
			}
		}
		else if (pWnd->GetDlgCtrlID() == IDC_STATIC_CONVERTER)
		{
			if (currentTheme)
			{
				pDC->SetTextColor(currentTheme->GetTextColor());
			}
		}
		else if (pWnd->GetDlgCtrlID() == IDC_STATIC_DATE)
		{
			if (currentTheme)
			{
				pDC->SetTextColor(currentTheme->GetTextColor());
			}
		}
		else if (pWnd->GetDlgCtrlID() == IDC_STATIC_TIMER1)
		{
			if (currentTheme)
			{
				pDC->SetTextColor(currentTheme->GetTextColor());
			}
		}
		else if (pWnd->GetDlgCtrlID() == IDC_STATIC_NOTEPAD)
		{
			if (currentTheme)
			{
				pDC->SetTextColor(currentTheme->GetTextColor());
			}
		}
		else if (pWnd->GetDlgCtrlID() == IDC_STATIC_BASE_TIMER)
		{
			if (currentTheme)
			{
				pDC->SetTextColor(currentTheme->GetTextColor());
			}
		}
		else if (pWnd->GetDlgCtrlID() == IDC_STATIC_WORLD_CLOCK)
		{
			if (currentTheme)
			{
				pDC->SetTextColor(currentTheme->GetTextColor());
			}
		}
	}
	// TODO:  기본값이 적당하지 않으면 다른 브러시를 반환합니다.
	return hbr;
}


void CBOKOToolsDlg::OnMenuSettingTheme()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	SettingTheme settingtheme(themeList, currentTheme, this);
	settingtheme.DoModal();
}

void CBOKOToolsDlg::OnMenuSortIcon()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	SortIcon sorticon(ctlItemVector, currentTheme, this);
	sorticon.DoModal();
}

void CBOKOToolsDlg::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CMenu mainMenu;
	mainMenu.LoadMenuW(IDR_MENU_MAIN);

	CMenu* pPopupMenu = mainMenu.GetSubMenu(0);
	
	this->ClientToScreen(&point);
	
	pPopupMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);

	CDialogEx::OnRButtonDown(nFlags, point);
}

void CBOKOToolsDlg::ExecuteSelectTheme(ThemeData* selectTheme)
{
	currentTheme = selectTheme;
	scroll.ThemeChange(currentTheme);
	LoadUserInterface(currentTheme);
	Invalidate();
}



void CBOKOToolsDlg::OnClose()
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	if (bBase || bEngineering || bConverter || bDate || bStopWatch || bTimer || bNotepad || bBaseTimer || bWorldClock)
	{
		if (MessageBox(_T("도구가 열려있습니다. 정말 종료하겠습니까?"), _T("종료"), MB_ICONQUESTION | MB_OKCANCEL) != IDOK)
		{
			return;
		}
	}

	CDialogEx::OnClose();
}

void CBOKOToolsDlg::ButtonCtlDisConnect()
{
	m_btn_base_gdi.DisConnect();
	m_btn_calculator_gdi.DisConnect();
	m_btn_stopwatch_gdi.DisConnect();
	m_btn_converter_gdi.DisConnect();
	m_btn_date_gdi.DisConnect();
	m_btn_worktimer_gdi.DisConnect();
	m_btn_notepad_gdi.DisConnect();
	m_btn_basetimer_gdi.DisConnect();
	m_btn_world_clock_gdi.DisConnect();
	m_btn_comingsoon_1.DisConnect();
	m_btn_comingsoon_2.DisConnect();
	m_btn_comingsoon_3.DisConnect();
}

void CBOKOToolsDlg::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	scroll.OperateScroll(nSBCode, nPos);
	ButtonCtlDisConnect();
	Invalidate();
	CDialogEx::OnVScroll(nSBCode, nPos, pScrollBar);
}


BOOL CBOKOToolsDlg::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
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
