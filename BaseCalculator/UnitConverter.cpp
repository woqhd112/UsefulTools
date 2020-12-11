// UnitConverter.cpp: 구현 파일
//

#include "pch.h"
#include "BaseCalculator.h"
#include "UnitConverter.h"
#include "BaseCalculatorDlg.h"
#include "afxdialogex.h"


// UnitConverter 대화 상자

IMPLEMENT_DYNAMIC(UnitConverter, CDialogEx)

UnitConverter::UnitConverter(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_CONVERTER, pParent)
{
	this->pParent = pParent;
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
END_MESSAGE_MAP()


// UnitConverter 메시지 처리기


BOOL UnitConverter::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	this->SetBackgroundColor(RGB(255, 255, 255));

	CRect tabRect;
	m_stt_tab.GetWindowRect(&tabRect);

	m_convert_length = new ConvertLengthTab;
	m_convert_length->Create(IDD_TAB_LENGTH, &m_stt_tab);
	m_convert_length->MoveWindow(0, 0, tabRect.Width(), tabRect.Height());
	m_convert_length->ShowWindow(SW_SHOW);

	m_convert_width = new ConvertWidthTab;
	m_convert_width->Create(IDD_TAB_WIDTH, &m_stt_tab);
	m_convert_width->MoveWindow(0, 0, tabRect.Width(), tabRect.Height());
	m_convert_width->ShowWindow(SW_HIDE);

	m_convert_weight = new ConvertWeightTab;
	m_convert_weight->Create(IDD_TAB_WEIGHT, &m_stt_tab);
	m_convert_weight->MoveWindow(0, 0, tabRect.Width(), tabRect.Height());
	m_convert_weight->ShowWindow(SW_HIDE);

	m_convert_time = new ConvertTimeTab;
	m_convert_time->Create(IDD_TAB_TIME, &m_stt_tab);
	m_convert_time->MoveWindow(0, 0, tabRect.Width(), tabRect.Height());
	m_convert_time->ShowWindow(SW_HIDE);

	m_convert_bit = new ConvertBitTab;
	m_convert_bit->Create(IDD_TAB_BIT, &m_stt_tab);
	m_convert_bit->MoveWindow(0, 0, tabRect.Width(), tabRect.Height());
	m_convert_bit->ShowWindow(SW_HIDE);

	m_btn_length.Initialize(RGB(255, 255, 255), CMFCButton::FlatStyle::BUTTONSTYLE_NOBORDERS, _T("휴먼매직체"));
	m_btn_width.Initialize(RGB(255, 255, 255), CMFCButton::FlatStyle::BUTTONSTYLE_NOBORDERS, _T("휴먼매직체"));
	m_btn_weight.Initialize(RGB(255, 255, 255), CMFCButton::FlatStyle::BUTTONSTYLE_NOBORDERS, _T("휴먼매직체"));
	m_btn_time.Initialize(RGB(255, 255, 255), CMFCButton::FlatStyle::BUTTONSTYLE_NOBORDERS, _T("휴먼매직체"));
	m_btn_bit.Initialize(RGB(255, 255, 255), CMFCButton::FlatStyle::BUTTONSTYLE_NOBORDERS, _T("휴먼매직체"));

	m_btn_length.ModifyStyle(0, WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 0);
	m_btn_width.ModifyStyle(0, WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 0);
	m_btn_weight.ModifyStyle(0, WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 0);
	m_btn_time.ModifyStyle(0, WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 0);
	m_btn_bit.ModifyStyle(0, WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 0);
	m_stt_tab.ModifyStyle(0, WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 0);

	m_stt_tab.BringWindowToTop();

	pointDesc = CONVERT_LENGTH_DESC;
	m_btn_length.ConvertButton::SetFont(ConvertButton::FontFlag::CLICK);

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
					OnBnClickedButtonTimec();
					break;
				case CONVERT_TIME_DESC:
					bClickTab = true;
					OnBnClickedButtonBit();
					break;
				case CONVERT_BIT_DESC:
					bClickTab = true;
					OnBnClickedButtonLength();
					break;
				default:
					break;
			}
		}
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}


void UnitConverter::PostNcDestroy()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	CBaseCalculatorDlg* parent = (CBaseCalculatorDlg*)pParent;
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
	m_btn_length.ConvertButton::SetFont(bClickTab ? ConvertButton::FontFlag::CLICK : ConvertButton::FontFlag::CLICKHOVER);
	m_btn_width.m_bClick = false;
	m_btn_width.ConvertButton::SetFont(ConvertButton::FontFlag::DEFAULT);
	m_btn_weight.m_bClick = false;
	m_btn_weight.ConvertButton::SetFont(ConvertButton::FontFlag::DEFAULT);
	m_btn_time.m_bClick = false;
	m_btn_time.ConvertButton::SetFont(ConvertButton::FontFlag::DEFAULT);
	m_btn_bit.m_bClick = false;
	m_btn_bit.ConvertButton::SetFont(ConvertButton::FontFlag::DEFAULT);

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
	m_btn_width.ConvertButton::SetFont(bClickTab ? ConvertButton::FontFlag::CLICK : ConvertButton::FontFlag::CLICKHOVER);
	m_btn_length.m_bClick = false;
	m_btn_length.ConvertButton::SetFont(ConvertButton::FontFlag::DEFAULT);
	m_btn_weight.m_bClick = false;
	m_btn_weight.ConvertButton::SetFont(ConvertButton::FontFlag::DEFAULT);
	m_btn_time.m_bClick = false;
	m_btn_time.ConvertButton::SetFont(ConvertButton::FontFlag::DEFAULT);
	m_btn_bit.m_bClick = false;
	m_btn_bit.ConvertButton::SetFont(ConvertButton::FontFlag::DEFAULT);

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
	m_btn_weight.ConvertButton::SetFont(bClickTab ? ConvertButton::FontFlag::CLICK : ConvertButton::FontFlag::CLICKHOVER);
	m_btn_length.m_bClick = false;
	m_btn_length.ConvertButton::SetFont(ConvertButton::FontFlag::DEFAULT);
	m_btn_width.m_bClick = false;
	m_btn_width.ConvertButton::SetFont(ConvertButton::FontFlag::DEFAULT);
	m_btn_time.m_bClick = false;
	m_btn_time.ConvertButton::SetFont(ConvertButton::FontFlag::DEFAULT);
	m_btn_bit.m_bClick = false;
	m_btn_bit.ConvertButton::SetFont(ConvertButton::FontFlag::DEFAULT);

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
	m_btn_time.ConvertButton::SetFont(bClickTab ? ConvertButton::FontFlag::CLICK : ConvertButton::FontFlag::CLICKHOVER);
	m_btn_length.m_bClick = false;
	m_btn_length.ConvertButton::SetFont(ConvertButton::FontFlag::DEFAULT);
	m_btn_width.m_bClick = false;
	m_btn_width.ConvertButton::SetFont(ConvertButton::FontFlag::DEFAULT);
	m_btn_weight.m_bClick = false;
	m_btn_weight.ConvertButton::SetFont(ConvertButton::FontFlag::DEFAULT);
	m_btn_bit.m_bClick = false;
	m_btn_bit.ConvertButton::SetFont(ConvertButton::FontFlag::DEFAULT);

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
	m_btn_bit.ConvertButton::SetFont(bClickTab ? ConvertButton::FontFlag::CLICK : ConvertButton::FontFlag::CLICKHOVER);
	m_btn_length.m_bClick = false;
	m_btn_length.ConvertButton::SetFont(ConvertButton::FontFlag::DEFAULT);
	m_btn_width.m_bClick = false;
	m_btn_width.ConvertButton::SetFont(ConvertButton::FontFlag::DEFAULT);
	m_btn_weight.m_bClick = false;
	m_btn_weight.ConvertButton::SetFont(ConvertButton::FontFlag::DEFAULT);
	m_btn_time.m_bClick = false;
	m_btn_time.ConvertButton::SetFont(ConvertButton::FontFlag::DEFAULT);

	m_convert_length->ShowWindow(SW_HIDE);
	m_convert_width->ShowWindow(SW_HIDE);
	m_convert_weight->ShowWindow(SW_HIDE);
	m_convert_time->ShowWindow(SW_HIDE);
	m_convert_bit->ShowWindow(SW_SHOW);

	pointDesc = CONVERT_BIT_DESC;
	bClickTab = false;
}
