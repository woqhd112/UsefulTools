// NotePad.cpp: 구현 파일
//

#include "pch.h"
#include "BOKOTools.h"
#include "NotePad.h"
#include "BOKOToolsDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// NotePad 대화 상자

IMPLEMENT_DYNAMIC(NotePad, CDialogEx)

NotePad::NotePad(bool bUsingManual, ThemeData* currentTheme, CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_NOTEPAD, pParent)
{
	this->pParent = pParent;
	this->currentTheme = currentTheme; 
	this->bUsingManual = bUsingManual;
	std::vector<int> manualList = { IDB_PNG_BASE_CLICK_THEME_BASIC, IDB_PNG_BASE_CLICK_THEME_CLOUD, IDB_PNG_BASE_CLICK_THEME_DETECTIVE, IDB_PNG_BASE_CLICK_THEME_INK };
	usingManual = new UsingManualDialog(manualList, currentTheme, this);
}

NotePad::~NotePad()
{
	if (notepadlist)
	{
		delete notepadlist;
		notepadlist = nullptr;
	}

	if (usingManual)
	{
		delete usingManual;
		usingManual = nullptr;
	}
}

void NotePad::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON_EDIT_BOLD, m_btn_edit_bold);
	DDX_Control(pDX, IDC_BUTTON_EDIT_ITALIC, m_btn_edit_italic);
	DDX_Control(pDX, IDC_BUTTON_EDIT_UNDERLINE, m_btn_edit_underline);
	DDX_Control(pDX, IDC_RICHEDIT_NOTEPAD, m_richedit_note);
	DDX_Control(pDX, IDC_BUTTON_NOTEPAD_REPORT, m_btn_report);
	DDX_Control(pDX, IDC_STATIC_NOTEPAD_LIST, m_stt_notepad_list);
}


BEGIN_MESSAGE_MAP(NotePad, CDialogEx)
	ON_WM_CTLCOLOR()
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BUTTON_EDIT_BOLD, &NotePad::OnBnClickedButtonEditBold)
	ON_BN_CLICKED(IDC_BUTTON_EDIT_ITALIC, &NotePad::OnBnClickedButtonEditItalic)
	ON_BN_CLICKED(IDC_BUTTON_EDIT_UNDERLINE, &NotePad::OnBnClickedButtonEditUnderline)
	ON_BN_CLICKED(IDC_BUTTON_NOTEPAD_REPORT, &NotePad::OnBnClickedButtonNotepadReport)
END_MESSAGE_MAP()


// NotePad 메시지 처리기



BOOL NotePad::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	this->SetBackgroundColor(currentTheme->GetFunctionBkColor());

	m_btn_edit_bold.Initialize(currentTheme->GetButtonColor(), CMFCButton::FlatStyle::BUTTONSTYLE_NOBORDERS);
	m_btn_edit_italic.Initialize(currentTheme->GetButtonColor(), CMFCButton::FlatStyle::BUTTONSTYLE_NOBORDERS);
	m_btn_edit_underline.Initialize(currentTheme->GetButtonColor(), CMFCButton::FlatStyle::BUTTONSTYLE_NOBORDERS);
	m_btn_report.Initialize(currentTheme->GetButtonColor(), CMFCButton::FlatStyle::BUTTONSTYLE_NOBORDERS);
	m_btn_edit_bold.m_bUseMouseTextItalicEvent = true;
	m_btn_edit_italic.m_bUseMouseTextItalicEvent = true;
	m_btn_edit_underline.m_bUseMouseTextItalicEvent = true;
	m_btn_edit_bold.SetTextColor(currentTheme->GetTextColor());
	m_btn_edit_italic.SetTextColor(currentTheme->GetTextColor());
	m_btn_edit_underline.SetTextColor(currentTheme->GetTextColor());
	m_btn_report.SetTextColor(currentTheme->GetTextColor());
	//m_richedit_note.SetBackgroundColor(false, RGB(200, 200, 200));

	m_btn_report.ModifyStyle(0, WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 0);
	m_richedit_note.ModifyStyle(0, WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 0);

	m_btn_report.BringWindowToTop();

	thisFont.CreateFontW(16, 0, 0, 0, FW_NORMAL, FALSE, FALSE, 0, DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS,
		_T("고딕"));

	m_richedit_note.SetFont(&thisFont);

	CRect notepadlistRect;
	m_stt_notepad_list.GetWindowRect(notepadlistRect);

	notepadlist = new NotePadList(currentTheme, this);
	notepadlist->Create(IDD_DIALOG_NOTEPAD_LIST, &m_stt_notepad_list);
	notepadlist->MoveWindow(0, 0, notepadlistRect.Width(), notepadlistRect.Height());
	notepadlist->ShowWindow(SW_SHOW);

	notepadlist->LoadNotePad();

	if (bUsingManual)
	{
		usingManual->Create(IDD_DIALOG_USING_MANUAL, this);
		usingManual->ShowWindow(SW_SHOW);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void NotePad::OnOK()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	//CDialogEx::OnOK();
}


void NotePad::OnClose()
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CDialogEx::OnClose();
	NotePad::PostNcDestroy();
}

void NotePad::PostNcDestroy()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	CBOKOToolsDlg* parent = (CBOKOToolsDlg*)pParent;
	parent->bNotepad = false;
	delete this;
	CDialogEx::PostNcDestroy();
}



HBRUSH NotePad::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  여기서 DC의 특성을 변경합니다.

	// TODO:  기본값이 적당하지 않으면 다른 브러시를 반환합니다.
	return hbr;
}

BOOL NotePad::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	if (pMsg->message == WM_KEYDOWN)
	{
		if (pMsg->wParam == VK_ESCAPE)
		{
			return TRUE;
		}
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}



void NotePad::OnBnClickedButtonEditBold()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	long nStart = 0;
	long nEnd = 0;
	m_richedit_note.GetSel(nStart, nEnd);
	CString strText = m_richedit_note.GetSelText();

	CHARFORMAT getcf;
	m_richedit_note.GetSelectionCharFormat(getcf);

	CHARFORMAT cf;
	memset(&cf, 0, sizeof(CHARFORMAT));
	cf.cbSize = sizeof(CHARFORMAT);
	cf.dwMask = getcf.dwMask | CFM_BOLD;
	cf.dwEffects = getcf.dwEffects | CFE_BOLD;
	m_richedit_note.SetSelectionCharFormat(cf);
	m_richedit_note.ReplaceSel(strText);
	m_richedit_note.SetSel(nStart, nEnd);
	m_richedit_note.SetFocus();
}


void NotePad::OnBnClickedButtonEditItalic()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	long nStart = 0;
	long nEnd = 0;
	m_richedit_note.GetSel(nStart, nEnd);
	CString strText = m_richedit_note.GetSelText();

	CHARFORMAT getcf;
	m_richedit_note.GetSelectionCharFormat(getcf);

	CHARFORMAT cf;
	memset(&cf, 0, sizeof(CHARFORMAT));
	cf.cbSize = sizeof(CHARFORMAT);
	cf.dwMask = getcf.dwMask | CFM_ITALIC;
	cf.dwEffects = getcf.dwEffects | CFE_ITALIC;
	m_richedit_note.SetSelectionCharFormat(cf);
	m_richedit_note.ReplaceSel(strText);
	m_richedit_note.SetSel(nStart, nEnd);
	m_richedit_note.SetFocus();
}


void NotePad::OnBnClickedButtonEditUnderline()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	long nStart = 0;
	long nEnd = 0;
	m_richedit_note.GetSel(nStart, nEnd);
	CString strText = m_richedit_note.GetSelText();

	CHARFORMAT getcf;
	m_richedit_note.GetSelectionCharFormat(getcf);

	CHARFORMAT cf;
	memset(&cf, 0, sizeof(CHARFORMAT));
	cf.cbSize = sizeof(CHARFORMAT);
	cf.dwMask = getcf.dwMask | CFM_UNDERLINE;
	cf.dwEffects = getcf.dwEffects | CFE_UNDERLINE;
	m_richedit_note.SetSelectionCharFormat(cf);
	m_richedit_note.ReplaceSel(strText);
	m_richedit_note.SetSel(nStart, nEnd);
	m_richedit_note.SetFocus();
}


void NotePad::OnBnClickedButtonNotepadReport()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_richedit_note.SetSel(0, 18);
	CString strNoteTitle = m_richedit_note.GetSelText();
	CString strNoteContent;
	m_richedit_note.GetWindowTextW(strNoteContent);
	
	// title, content를 notepadlist에 전달해서 버튼생성
}
