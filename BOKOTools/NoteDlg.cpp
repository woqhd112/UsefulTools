// NoteDlg.cpp: 구현 파일
//

#include "pch.h"
#include "BOKOTools.h"
#include "NoteDlg.h"
#include "afxdialogex.h"


// NoteDlg 대화 상자

IMPLEMENT_DYNAMIC(NoteDlg, CDialogEx)

NoteDlg::NoteDlg(int nFolderMode, ThemeData* currentTheme, CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_CREATE_NOTE, pParent)
{
	this->currentTheme = currentTheme;
	this->pParent = pParent;
	this->nFolderMode = nFolderMode;
}

NoteDlg::~NoteDlg()
{
}

void NoteDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON_CREATE_NOTE_BOLD, m_btn_bold);
	DDX_Control(pDX, IDC_BUTTON_CREATE_NOTE_ITALIC, m_btn_italic);
	DDX_Control(pDX, IDC_BUTTON_CREATE_NOTE_UNDERLINE, m_btn_underline);
	DDX_Control(pDX, IDC_BUTTON_CREATE_NOTE_LOCK, m_btn_lock);
	DDX_Control(pDX, IDC_RICHEDIT2_CREATE_NOTE, m_richedit_notepad);
	DDX_Control(pDX, IDC_BUTTON_CREATE_NOTE_REPORT, m_btn_report);
}


BEGIN_MESSAGE_MAP(NoteDlg, CDialogEx)
	ON_WM_CLOSE()
	ON_WM_CTLCOLOR()
	ON_WM_PAINT()
END_MESSAGE_MAP()


// NoteDlg 메시지 처리기


BOOL NoteDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	this->SetBackgroundColor(currentTheme->GetFunctionBkColor());
	m_topBrush.CreateSolidBrush(currentTheme->GetFunctionBkColor());
	m_bottomBrush.CreateSolidBrush(RGB(255, 255, 255));

	CRect parentRect;
	pParent->GetWindowRect(parentRect);

	this->MoveWindow(parentRect.right, parentRect.top, MARGIN_X(435), MARGIN_Y(674));
	m_btn_bold.MoveWindow(20, 20, 25, 25);
	m_btn_italic.MoveWindow(50, 20, 25, 25);
	m_btn_underline.MoveWindow(80, 20, 25, 25);
	m_btn_lock.MoveWindow(375, 34, 40, 40);
	m_richedit_notepad.MoveWindow(20, 50, 395, 540);
	m_btn_report.MoveWindow(365, 565, 64, 64);
	wrapBorderRect = { 15, 45, 405, 615 };
	wrapCenterRect = { 20, 50, 415, 610 };

	m_btn_bold.Initialize(currentTheme->GetButtonColor(), CMFCButton::FlatStyle::BUTTONSTYLE_NOBORDERS, currentTheme->GetThemeFontName(), 20);
	m_btn_italic.Initialize(currentTheme->GetButtonColor(), CMFCButton::FlatStyle::BUTTONSTYLE_NOBORDERS, currentTheme->GetThemeFontName(), 20);
	m_btn_underline.Initialize(currentTheme->GetButtonColor(), CMFCButton::FlatStyle::BUTTONSTYLE_NOBORDERS, currentTheme->GetThemeFontName(), 20);
	m_btn_bold.m_bUseMouseTextItalicEvent = true;
	m_btn_italic.m_bUseMouseTextItalicEvent = true;
	m_btn_underline.m_bUseMouseTextItalicEvent = true;
	m_btn_bold.SetTextColor(currentTheme->GetTextColor());
	m_btn_italic.SetTextColor(currentTheme->GetTextColor());
	m_btn_underline.SetTextColor(currentTheme->GetTextColor());

	m_btn_report.LoadStdImage(IDB_PNG_NOTEPAD_REPORT_NOMAL, _T("PNG"));
	m_btn_report.LoadHovImage(IDB_PNG_NOTEPAD_REPORT_HOVER, _T("PNG"));
	m_btn_report.LoadAltImage(IDB_PNG_NOTEPAD_REPORT_CLICK, _T("PNG"));

	m_btn_lock.LoadStdImage(IDB_PNG_NOTEPAD_LOCK_NOMAL, _T("PNG"));
	m_btn_lock.LoadHovImage(IDB_PNG_NOTEPAD_LOCK_HOVER, _T("PNG"));
	m_btn_lock.LoadAltImage(IDB_PNG_NOTEPAD_LOCK_CLICK, _T("PNG"));
	m_btn_lock.EnableToggle();

	m_btn_report.ModifyStyle(0, WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 0);
	m_btn_lock.ModifyStyle(0, WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 0);
	m_richedit_notepad.ModifyStyle(0, WS_CLIPSIBLINGS, 0);

	m_btn_report.BringWindowToTop();
	m_btn_lock.BringWindowToTop();

	thisFont.CreateFontW(25, 0, 0, 0, FW_NORMAL, FALSE, FALSE, 0, DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS,
		currentTheme->GetThemeFontName());

	m_richedit_notepad.SetFont(&thisFont);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void NoteDlg::OnOK()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	CDialogEx::OnOK();
}


void NoteDlg::OnClose()
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CDialogEx::OnClose();
}


HBRUSH NoteDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  여기서 DC의 특성을 변경합니다.

	// TODO:  기본값이 적당하지 않으면 다른 브러시를 반환합니다.
	return hbr;
}


BOOL NoteDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	return CDialogEx::PreTranslateMessage(pMsg);
}


void NoteDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 여기에 메시지 처리기 코드를 추가합니다.
					   // 그리기 메시지에 대해서는 CDialogEx::OnPaint()을(를) 호출하지 마십시오.
	CBrush *pOld;
	dc.SelectObject(&m_topBrush);
	dc.PatBlt(wrapBorderRect.left, wrapBorderRect.top, wrapBorderRect.Width(), wrapBorderRect.Height(), PATCOPY);
	pOld = dc.SelectObject(&m_bottomBrush);
	dc.PatBlt(wrapCenterRect.left, wrapCenterRect.top, wrapCenterRect.Width(), wrapCenterRect.Height(), PATCOPY);
	dc.SelectObject(pOld);
}
