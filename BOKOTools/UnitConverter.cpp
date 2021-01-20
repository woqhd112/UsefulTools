// UnitConverter.cpp: 구현 파일
//

#include "pch.h"
#include "BOKOTools.h"
#include "UnitConverter.h"
#include "BOKOToolsDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// UnitConverter 대화 상자

IMPLEMENT_DYNAMIC(UnitConverter, CDialogEx)

UnitConverter::UnitConverter(bool bUsingManual, ThemeData* currentTheme, CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_CONVERTER, pParent)
{
	this->pParent = pParent;
	this->currentTheme = currentTheme;
	this->bUsingManual = bUsingManual;
	std::vector<int> manualList = { IDB_PNG_BASE_CLICK_THEME_BASIC, IDB_PNG_BASE_CLICK_THEME_CLOUD, IDB_PNG_BASE_CLICK_THEME_DETECTIVE, IDB_PNG_BASE_CLICK_THEME_INK };
	usingManual = new UsingManualDialog(manualList, currentTheme, this);
	bClickTab = false;
}

UnitConverter::~UnitConverter()
{
	if (m_convert_length)
	{
		delete m_convert_length;
		m_convert_length = (ConvertLengthTab*)nullptr;
	}

	if (m_convert_width)
	{
		delete m_convert_width;
		m_convert_width = (ConvertWidthTab*)nullptr;
	}

	if (m_convert_weight)
	{
		delete m_convert_weight;
		m_convert_weight = (ConvertWeightTab*)nullptr;
	}

	if (m_convert_time)
	{
		delete m_convert_time;
		m_convert_time = (ConvertTimeTab*)nullptr;
	}

	if (m_convert_bit)
	{
		delete m_convert_bit;
		m_convert_bit = (ConvertBitTab*)nullptr;
	}

	if (usingManual)
	{
		delete usingManual;
		usingManual = nullptr;
	}
}

void UnitConverter::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_TAB, m_stt_tab);
	DDX_Control(pDX, IDC_BUTTON_LENGTH, m_btn_length);
	DDX_Control(pDX, IDC_BUTTON_WIDTH, m_btn_width);
	DDX_Control(pDX, IDC_BUTTON_WEIGHT, m_btn_weight);
	DDX_Control(pDX, IDC_BUTTON_TIMEC, m_btn_time);
	DDX_Control(pDX, IDC_BUTTON_BIT, m_btn_bit);
}


BEGIN_MESSAGE_MAP(UnitConverter, CDialogEx)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BUTTON_LENGTH, &UnitConverter::OnBnClickedButtonLength)
	ON_BN_CLICKED(IDC_BUTTON_WIDTH, &UnitConverter::OnBnClickedButtonWidth)
	ON_BN_CLICKED(IDC_BUTTON_WEIGHT, &UnitConverter::OnBnClickedButtonWeight)
	ON_BN_CLICKED(IDC_BUTTON_TIMEC, &UnitConverter::OnBnClickedButtonTimec)
	ON_BN_CLICKED(IDC_BUTTON_BIT, &UnitConverter::OnBnClickedButtonBit)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// UnitConverter 메시지 처리기


BOOL UnitConverter::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	this->SetBackgroundColor(currentTheme->GetFunctionBkColor());


	CRect tabRect;
	this->SetWindowPos(NULL, 0, 0, 610, 450, SWP_NOMOVE);
	m_stt_tab.MoveWindow(30, 60, 529, 314);
	m_stt_tab.GetWindowRect(&tabRect);
	m_btn_length.MoveWindow(30, 30, 100, 30);
	m_btn_width.MoveWindow(135, 30, 100, 30);
	m_btn_weight.MoveWindow(240, 30, 100, 30);
	m_btn_bit.MoveWindow(345, 30, 100, 30);
	m_btn_time.MoveWindow(450, 30, 100, 30);

	converterBorderRect = { 30, 60, 30 + 529, 60 + 314 };

	m_convert_length = new ConvertLengthTab(currentTheme, this);
	m_convert_length->Create(IDD_TAB_LENGTH, &m_stt_tab);
	m_convert_length->MoveWindow(0, 0, tabRect.Width(), tabRect.Height());
	m_convert_length->ShowWindow(SW_SHOW);

	m_convert_width = new ConvertWidthTab(currentTheme, this);
	m_convert_width->Create(IDD_TAB_WIDTH, &m_stt_tab);
	m_convert_width->MoveWindow(0, 0, tabRect.Width(), tabRect.Height());
	m_convert_width->ShowWindow(SW_HIDE);

	m_convert_weight = new ConvertWeightTab(currentTheme, this);
	m_convert_weight->Create(IDD_TAB_WEIGHT, &m_stt_tab);
	m_convert_weight->MoveWindow(0, 0, tabRect.Width(), tabRect.Height());
	m_convert_weight->ShowWindow(SW_HIDE);

	m_convert_time = new ConvertTimeTab(currentTheme, this);
	m_convert_time->Create(IDD_TAB_TIME, &m_stt_tab);
	m_convert_time->MoveWindow(0, 0, tabRect.Width(), tabRect.Height());
	m_convert_time->ShowWindow(SW_HIDE);

	m_convert_bit = new ConvertBitTab(currentTheme, this);
	m_convert_bit->Create(IDD_TAB_BIT, &m_stt_tab);
	m_convert_bit->MoveWindow(0, 0, tabRect.Width(), tabRect.Height());
	m_convert_bit->ShowWindow(SW_HIDE);

	m_btn_length.Initialize(currentTheme->GetFunctionBkColor(), CMFCButton::FlatStyle::BUTTONSTYLE_NOBORDERS, currentTheme->GetThemeFontName(), 25);
	m_btn_width.Initialize(currentTheme->GetFunctionBkColor(), CMFCButton::FlatStyle::BUTTONSTYLE_NOBORDERS, currentTheme->GetThemeFontName(), 25);
	m_btn_weight.Initialize(currentTheme->GetFunctionBkColor(), CMFCButton::FlatStyle::BUTTONSTYLE_NOBORDERS, currentTheme->GetThemeFontName(), 25);
	m_btn_time.Initialize(currentTheme->GetFunctionBkColor(), CMFCButton::FlatStyle::BUTTONSTYLE_NOBORDERS, currentTheme->GetThemeFontName(), 25);
	m_btn_bit.Initialize(currentTheme->GetFunctionBkColor(), CMFCButton::FlatStyle::BUTTONSTYLE_NOBORDERS, currentTheme->GetThemeFontName(), 25);
	m_btn_length.m_bUseMouseBkGroundColorEvent = false;
	m_btn_length.m_bUseMouseTextItalicEvent = true;
	m_btn_length.m_bUseMouseTextBoldEvent = true;
	m_btn_width.m_bUseMouseBkGroundColorEvent = false;
	m_btn_width.m_bUseMouseTextItalicEvent = true;
	m_btn_width.m_bUseMouseTextBoldEvent = true;
	m_btn_weight.m_bUseMouseBkGroundColorEvent = false;
	m_btn_weight.m_bUseMouseTextItalicEvent = true;
	m_btn_weight.m_bUseMouseTextBoldEvent = true;
	m_btn_time.m_bUseMouseBkGroundColorEvent = false;
	m_btn_time.m_bUseMouseTextItalicEvent = true;
	m_btn_time.m_bUseMouseTextBoldEvent = true;
	m_btn_bit.m_bUseMouseBkGroundColorEvent = false;
	m_btn_bit.m_bUseMouseTextItalicEvent = true;
	m_btn_bit.m_bUseMouseTextBoldEvent = true;
	m_btn_length.SetTextColor(currentTheme->GetTextColor());
	m_btn_width.SetTextColor(currentTheme->GetTextColor());
	m_btn_weight.SetTextColor(currentTheme->GetTextColor());
	m_btn_time.SetTextColor(currentTheme->GetTextColor());
	m_btn_bit.SetTextColor(currentTheme->GetTextColor());

	m_btn_length.ModifyStyle(0, WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 0);
	m_btn_width.ModifyStyle(0, WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 0);
	m_btn_weight.ModifyStyle(0, WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 0);
	m_btn_time.ModifyStyle(0, WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 0);
	m_btn_bit.ModifyStyle(0, WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 0);
	m_stt_tab.ModifyStyle(0, WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 0);

	m_stt_tab.BringWindowToTop();

	m_btn_length.m_bClick = true;
	pointDesc = CONVERT_LENGTH_DESC;
	m_btn_length.CalculateButton::SetFont(CalculateButton::FontFlag::CLICK);

	if (bUsingManual)
	{
		usingManual->Create(IDD_DIALOG_USING_MANUAL, this);
		usingManual->ShowWindow(SW_SHOW);
	}


	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void UnitConverter::OnOK()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	//CDialogEx::OnOK();
}


BOOL UnitConverter::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	if (WM_KEYDOWN == pMsg->message)
	{
		if (pMsg->wParam == VK_TAB)
		{
			switch (pointDesc)
			{
				case CONVERT_LENGTH_DESC:
					bClickTab = true;
					OnBnClickedButtonWidth();
					break;
				case CONVERT_WIDTH_DESC:
					bClickTab = true;
					OnBnClickedButtonWeight();
					break;
				case CONVERT_WEIGHT_DESC:
					bClickTab = true;
					OnBnClickedButtonBit();
					break;
				case CONVERT_BIT_DESC:
					bClickTab = true;
					OnBnClickedButtonTimec();
					break;
				case CONVERT_TIME_DESC:
					bClickTab = true;
					OnBnClickedButtonLength();
					break;
				default:
					break;
			}
		}
		else if (pMsg->wParam == VK_ESCAPE)
		{
			return TRUE;
		}
}

	return CDialogEx::PreTranslateMessage(pMsg);
}


void UnitConverter::PostNcDestroy()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	CBOKOToolsDlg* parent = (CBOKOToolsDlg*)pParent;
	parent->bConverter = false;
	delete this;
	CDialogEx::PostNcDestroy();
}


void UnitConverter::OnClose()
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CDialogEx::OnClose();
	UnitConverter::PostNcDestroy();
}



void UnitConverter::OnBnClickedButtonLength()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_btn_length.m_bClick = true;
	m_btn_length.CalculateButton::SetFont(bClickTab ? CalculateButton::FontFlag::CLICK : CalculateButton::FontFlag::CLICKHOVER);
	m_btn_width.m_bClick = false;
	m_btn_width.CalculateButton::SetFont(CalculateButton::FontFlag::DEFAULT);
	m_btn_weight.m_bClick = false;
	m_btn_weight.CalculateButton::SetFont(CalculateButton::FontFlag::DEFAULT);
	m_btn_time.m_bClick = false;
	m_btn_time.CalculateButton::SetFont(CalculateButton::FontFlag::DEFAULT);
	m_btn_bit.m_bClick = false;
	m_btn_bit.CalculateButton::SetFont(CalculateButton::FontFlag::DEFAULT);

	m_convert_length->ShowWindow(SW_SHOW);
	m_convert_width->ShowWindow(SW_HIDE);
	m_convert_weight->ShowWindow(SW_HIDE);
	m_convert_time->ShowWindow(SW_HIDE);
	m_convert_bit->ShowWindow(SW_HIDE);

	pointDesc = CONVERT_LENGTH_DESC;
	bClickTab = false;
}


void UnitConverter::OnBnClickedButtonWidth()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_btn_width.m_bClick = true;
	m_btn_width.CalculateButton::SetFont(bClickTab ? CalculateButton::FontFlag::CLICK : CalculateButton::FontFlag::CLICKHOVER);
	m_btn_length.m_bClick = false;
	m_btn_length.CalculateButton::SetFont(CalculateButton::FontFlag::DEFAULT);
	m_btn_weight.m_bClick = false;
	m_btn_weight.CalculateButton::SetFont(CalculateButton::FontFlag::DEFAULT);
	m_btn_time.m_bClick = false;
	m_btn_time.CalculateButton::SetFont(CalculateButton::FontFlag::DEFAULT);
	m_btn_bit.m_bClick = false;
	m_btn_bit.CalculateButton::SetFont(CalculateButton::FontFlag::DEFAULT);

	m_convert_length->ShowWindow(SW_HIDE);
	m_convert_width->ShowWindow(SW_SHOW);
	m_convert_weight->ShowWindow(SW_HIDE);
	m_convert_time->ShowWindow(SW_HIDE);
	m_convert_bit->ShowWindow(SW_HIDE);

	pointDesc = CONVERT_WIDTH_DESC;
	bClickTab = false;
}


void UnitConverter::OnBnClickedButtonWeight()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_btn_weight.m_bClick = true;
	m_btn_weight.CalculateButton::SetFont(bClickTab ? CalculateButton::FontFlag::CLICK : CalculateButton::FontFlag::CLICKHOVER);
	m_btn_length.m_bClick = false;
	m_btn_length.CalculateButton::SetFont(CalculateButton::FontFlag::DEFAULT);
	m_btn_width.m_bClick = false;
	m_btn_width.CalculateButton::SetFont(CalculateButton::FontFlag::DEFAULT);
	m_btn_time.m_bClick = false;
	m_btn_time.CalculateButton::SetFont(CalculateButton::FontFlag::DEFAULT);
	m_btn_bit.m_bClick = false;
	m_btn_bit.CalculateButton::SetFont(CalculateButton::FontFlag::DEFAULT);

	m_convert_length->ShowWindow(SW_HIDE);
	m_convert_width->ShowWindow(SW_HIDE);
	m_convert_weight->ShowWindow(SW_SHOW);
	m_convert_time->ShowWindow(SW_HIDE);
	m_convert_bit->ShowWindow(SW_HIDE);

	pointDesc = CONVERT_WEIGHT_DESC;
	bClickTab = false;
}


void UnitConverter::OnBnClickedButtonTimec()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_btn_time.m_bClick = true;
	m_btn_time.CalculateButton::SetFont(bClickTab ? CalculateButton::FontFlag::CLICK : CalculateButton::FontFlag::CLICKHOVER);
	m_btn_length.m_bClick = false;
	m_btn_length.CalculateButton::SetFont(CalculateButton::FontFlag::DEFAULT);
	m_btn_width.m_bClick = false;
	m_btn_width.CalculateButton::SetFont(CalculateButton::FontFlag::DEFAULT);
	m_btn_weight.m_bClick = false;
	m_btn_weight.CalculateButton::SetFont(CalculateButton::FontFlag::DEFAULT);
	m_btn_bit.m_bClick = false;
	m_btn_bit.CalculateButton::SetFont(CalculateButton::FontFlag::DEFAULT);

	m_convert_length->ShowWindow(SW_HIDE);
	m_convert_width->ShowWindow(SW_HIDE);
	m_convert_weight->ShowWindow(SW_HIDE);
	m_convert_time->ShowWindow(SW_SHOW);
	m_convert_bit->ShowWindow(SW_HIDE);

	pointDesc = CONVERT_TIME_DESC;
	bClickTab = false;
}


void UnitConverter::OnBnClickedButtonBit()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_btn_bit.m_bClick = true;
	m_btn_bit.CalculateButton::SetFont(bClickTab ? CalculateButton::FontFlag::CLICK : CalculateButton::FontFlag::CLICKHOVER);
	m_btn_length.m_bClick = false;
	m_btn_length.CalculateButton::SetFont(CalculateButton::FontFlag::DEFAULT);
	m_btn_width.m_bClick = false;
	m_btn_width.CalculateButton::SetFont(CalculateButton::FontFlag::DEFAULT);
	m_btn_weight.m_bClick = false;
	m_btn_weight.CalculateButton::SetFont(CalculateButton::FontFlag::DEFAULT);
	m_btn_time.m_bClick = false;
	m_btn_time.CalculateButton::SetFont(CalculateButton::FontFlag::DEFAULT);

	m_convert_length->ShowWindow(SW_HIDE);
	m_convert_width->ShowWindow(SW_HIDE);
	m_convert_weight->ShowWindow(SW_HIDE);
	m_convert_time->ShowWindow(SW_HIDE);
	m_convert_bit->ShowWindow(SW_SHOW);

	pointDesc = CONVERT_BIT_DESC;
	bClickTab = false;
}



void UnitConverter::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 여기에 메시지 처리기 코드를 추가합니다.
					   // 그리기 메시지에 대해서는 CDialogEx::OnPaint()을(를) 호출하지 마십시오.

	dc.Draw3dRect(converterBorderRect, currentTheme->GetRectBorderColor(), currentTheme->GetRectBorderColor());
}
