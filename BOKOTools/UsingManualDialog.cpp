// UsingManualDialog.cpp: 구현 파일
//

#include "pch.h"
#include "BOKOTools.h"
#include "UsingManualDialog.h"
#include "BOKOToolsDlg.h"
#include "afxdialogex.h"


// UsingManualDialog 대화 상자

IMPLEMENT_DYNAMIC(UsingManualDialog, CDialogEx)

UsingManualDialog::UsingManualDialog(bool bFuncPopUp, int nParentID, int nManualImageID, ThemeData* currentTheme, CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_USING_MANUAL, pParent)
{
	this->currentTheme = currentTheme;
	this->nManualImageID = nManualImageID;
	this->nParentID = nParentID;
	this->bFuncPopUp = bFuncPopUp;
}

UsingManualDialog::~UsingManualDialog()
{
}

void UsingManualDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHECK_NEVER_LOOK_BACK, m_btn_check_never_look_back);
	DDX_Control(pDX, IDC_BUTTON_USING_MANUAL, m_btn_manual_image);
}


BEGIN_MESSAGE_MAP(UsingManualDialog, CDialogEx)
	ON_WM_CLOSE()
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_CHECK_NEVER_LOOK_BACK, &UsingManualDialog::OnBnClickedCheckNeverLookBack)
END_MESSAGE_MAP()


// UsingManualDialog 메시지 처리기


BOOL UsingManualDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	SetWindowTheme(m_btn_check_never_look_back, _T(""), _T(""));

	checkFont.CreateFontW(25, 0, 0, 0, FW_BOLD, FALSE, FALSE, 0, DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS,
		currentTheme->GetThemeFontName());

	int nThisHeight = bFuncPopUp ? 450 : 410;
	this->SetBackgroundColor(currentTheme->GetFunctionBkColor());
	this->SetWindowPos(NULL, 0, 0, 600, nThisHeight, SWP_NOMOVE);

	checkPosRect = { 200, 450 - 80, 200 + 180, 30 + 450 - 80 };
	m_btn_check_never_look_back.MoveWindow(checkPosRect);
	m_btn_check_never_look_back.SetFont(&checkFont);

	m_btn_manual_image.LoadStdImage(nManualImageID, _T("PNG"));
	m_btn_manual_image.LoadHovImage(nManualImageID, _T("PNG"));
	m_btn_manual_image.LoadAltImage(nManualImageID, _T("PNG"));
	m_btn_manual_image.m_bUseMouseEvent = false;
	m_btn_manual_image.MoveWindow(10, 10, 560, 340);

	CString strParentName = GetDialogName(nParentID);

	this->SetWindowTextW(strParentName + _T("의 설명서"));

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void UsingManualDialog::OnOK()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	//CDialogEx::OnOK();
}


void UsingManualDialog::OnClose()
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	//if (m_btn_check_never_look_back.GetCheck() == TRUE)
	//{
	//	// 다시보지않기 저장함수
	//	SaveUsingManual();
	//}

	CDialogEx::OnClose();
}

CString UsingManualDialog::GetDialogName(int nID)
{
	CString strDialogName = _T("");
	if (nID == IDD_DIALOG_BASE) strDialogName = _T("진법 계산기");
	else if (nID == IDD_DIALOG_ENGINEERING) strDialogName = _T("공학 계산기");
	else if (nID == IDD_DIALOG_STOPWATCH) strDialogName = _T("스탑워치");
	else if (nID == IDD_DIALOG_CONVERTER) strDialogName = _T("단위 변환기");
	else if (nID == IDD_DIALOG_DATE) strDialogName = _T("날짜 계산기");
	else if (nID == IDD_DIALOG_TIMER) strDialogName = _T("업무 타이머");
	else if (nID == IDD_DIALOG_NOTEPAD) strDialogName = _T("메모장");
	else if (nID == IDD_DIALOG_BASE_TIMER) strDialogName = _T("기본 타이머");
	else if (nID == IDD_DIALOG_WORLD_CLOCK) strDialogName = _T("세계 시계");
	else if (nID == IDD_DIALOG_SORT_ICON) strDialogName = _T("아이콘 정렬");
	else if (nID == IDD_DIALOG_SETTING_THEME) strDialogName = _T("테마 세팅");
	else if (nID == IDD_BASECALCULATOR_DIALOG) strDialogName = _T("메인 화면");

	return strDialogName;
}

void UsingManualDialog::SaveUsingManual()
{
	CMarkup markUp;
	CString szRoot = _T("");
	CustomXml::CreateConfigFile(szRoot);
	CString strFullPath = szRoot + _T("\\UsingManual.conf");
	CBOKOToolsDlg* mainFrame = (CBOKOToolsDlg*)AfxGetMainWnd();

	if (markUp.Load(strFullPath))
	{
		markUp.FindElem(_T("Manual"));
		markUp.IntoElem();
		while (markUp.FindElem(_T("func")))
		{
			if (markUp.GetAttrib(_T("name")) == GetDialogName(nParentID))
			{
				markUp.SetAttrib(_T("use"), 0);
				if (nParentID == IDD_DIALOG_BASE) mainFrame->bBaseUsingManual = false;
				else if (nParentID == IDD_DIALOG_ENGINEERING) mainFrame->bEngineeringUsingManual = false;
				else if (nParentID == IDD_DIALOG_STOPWATCH) mainFrame->bStopWatchUsingManual = false;
				else if (nParentID == IDD_DIALOG_CONVERTER) mainFrame->bConverterUsingManual = false;
				else if (nParentID == IDD_DIALOG_DATE) mainFrame->bDateUsingManual = false;
				else if (nParentID == IDD_DIALOG_TIMER) mainFrame->bTimerUsingManual = false;
				else if (nParentID == IDD_DIALOG_NOTEPAD) mainFrame->bNotepadUsingManual = false;
				else if (nParentID == IDD_DIALOG_BASE_TIMER) mainFrame->bBaseTimerUsingManual = false;
				else if (nParentID == IDD_DIALOG_WORLD_CLOCK) mainFrame->bWorldClockUsingManual = false;
				else if (nParentID == IDD_DIALOG_SORT_ICON) mainFrame->bIconSortManual = false;
				else if (nParentID == IDD_DIALOG_SETTING_THEME) mainFrame->bSettingThemeManual = false;
				else if (nParentID == IDD_BASECALCULATOR_DIALOG) mainFrame->bMainFrameManual = false;
				break;
			}
		}
	}

	CustomXml::SaveXml(&markUp, strFullPath);
}

BOOL UsingManualDialog::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	return CDialogEx::PreTranslateMessage(pMsg);
}


HBRUSH UsingManualDialog::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  여기서 DC의 특성을 변경합니다.
	if (nCtlColor == CTLCOLOR_BTN)
	{
		if (pWnd->GetDlgCtrlID() == m_btn_check_never_look_back.GetDlgCtrlID())
		{
			pDC->SetTextColor(currentTheme->GetTextColor());
		}
	}
	else if (nCtlColor == CTLCOLOR_STATIC)
	{
		if (pWnd->GetDlgCtrlID() == m_btn_check_never_look_back.GetDlgCtrlID())
		{
			pDC->SetTextColor(currentTheme->GetTextColor());
		}
	}

	// TODO:  기본값이 적당하지 않으면 다른 브러시를 반환합니다.
	return hbr;
}



void UsingManualDialog::OnBnClickedCheckNeverLookBack()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (m_btn_check_never_look_back.GetCheck())
	{
		SaveUsingManual();
		PostMessage(WM_CLOSE);
	}
}
