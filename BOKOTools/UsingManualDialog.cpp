// UsingManualDialog.cpp: 구현 파일
//

#include "pch.h"
#include "BOKOTools.h"
#include "UsingManualDialog.h"
#include "BOKOToolsDlg.h"
#include "afxdialogex.h"


// UsingManualDialog 대화 상자

IMPLEMENT_DYNAMIC(UsingManualDialog, CDialogEx)

UsingManualDialog::UsingManualDialog(int nParentID, std::vector<int> usingTypeManualVector, ThemeData* currentTheme, CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_USING_MANUAL, pParent)
{
	this->currentTheme = currentTheme;
	this->usingTypeManualVector = usingTypeManualVector;
	this->nParentID = nParentID;
}

UsingManualDialog::~UsingManualDialog()
{
}

void UsingManualDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHECK_NEVER_LOOK_BACK, m_btn_check_never_look_back);
}


BEGIN_MESSAGE_MAP(UsingManualDialog, CDialogEx)
	ON_WM_CLOSE()
	ON_WM_CTLCOLOR()
	ON_WM_VSCROLL()
	ON_WM_MOUSEWHEEL()
END_MESSAGE_MAP()


// UsingManualDialog 메시지 처리기


BOOL UsingManualDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	this->SetBackgroundColor(currentTheme->GetFunctionBkColor());
	this->SetWindowPos(NULL, 0, 0, 500, 700, SWP_NOMOVE);

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

	if (m_btn_check_never_look_back.GetCheck() == TRUE)
	{
		// 다시보지않기 저장함수
		SaveUsingManual();
	}

	CDialogEx::OnClose();
}

CString UsingManualDialog::GetDialogName(int nID)
{
	CString strDialogName = _T("");
	if (nID == IDD_DIALOG_BASE) strDialogName = _T("BaseCalculator");
	else if (nID == IDD_DIALOG_ENGINEERING) strDialogName = _T("EngineeringCalculator");
	else if (nID == IDD_DIALOG_STOPWATCH) strDialogName = _T("StopWatch");
	else if (nID == IDD_DIALOG_CONVERTER) strDialogName = _T("UnitConverter");
	else if (nID == IDD_DIALOG_DATE) strDialogName = _T("DateCalculator");
	else if (nID == IDD_DIALOG_TIMER) strDialogName = _T("WorkTimer");
	else if (nID == IDD_DIALOG_NOTEPAD) strDialogName = _T("NotePad");
	else if (nID == IDD_DIALOG_BASE_TIMER) strDialogName = _T("BaseTimer");
	else if (nID == IDD_DIALOG_WORLD_CLOCK) strDialogName = _T("WorldClock");

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

	// TODO:  기본값이 적당하지 않으면 다른 브러시를 반환합니다.
	return hbr;
}


void UsingManualDialog::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CDialogEx::OnVScroll(nSBCode, nPos, pScrollBar);
}


BOOL UsingManualDialog::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	return CDialogEx::OnMouseWheel(nFlags, zDelta, pt);
}
