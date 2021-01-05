// WorldClock.cpp: 구현 파일
//

#include "pch.h"
#include "BOKOTools.h"
#include "WorldClock.h"
#include "BOKOToolsDlg.h"
#include "afxdialogex.h"


// WorldClock 대화 상자

IMPLEMENT_DYNAMIC(WorldClock, CDialogEx)

WorldClock::WorldClock(ThemeData* currentTheme, CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_WORLD_CLOCK, pParent)
{
	this->pParent = pParent;
	this->currentTheme = currentTheme;
}

WorldClock::~WorldClock()
{
}

void WorldClock::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON_WORLD_SEARCH, m_btn_search);
	DDX_Control(pDX, IDC_EDIT_WORLD_SEARCH, m_edit_search);
	DDX_Control(pDX, IDC_STATIC_RESULT_VIEW, m_stt_result_view);
}


BEGIN_MESSAGE_MAP(WorldClock, CDialogEx)
	ON_WM_CLOSE()
	ON_WM_CTLCOLOR()
	ON_EN_CHANGE(IDC_EDIT_WORLD_SEARCH, &WorldClock::OnEnChangeEditWorldSearch)
END_MESSAGE_MAP()


// WorldClock 메시지 처리기


BOOL WorldClock::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	this->SetBackgroundColor(currentTheme->GetFunctionBkColor());
	m_backBrush.CreateSolidBrush(currentTheme->GetFunctionSubColor());

	m_btn_search.Initialize(currentTheme->GetButtonColor(), CMFCButton::FlatStyle::BUTTONSTYLE_NOBORDERS);
	m_btn_search.SetTextColor(currentTheme->GetTextColor());

	CRect listViewRect, editRect, thisRect;
	m_stt_result_view.GetWindowRect(listViewRect);
	m_edit_search.GetWindowRect(editRect);
	this->GetWindowRect(thisRect);

	worldclocklist = new WorldClockList(currentTheme, this);
	worldclocklist->Create(IDD_DIALOG_WORLD_LIST, &m_stt_result_view);
	worldclocklist->MoveWindow(0, 0, listViewRect.Width(), listViewRect.Height());
	worldclocklist->ShowWindow(SW_SHOW);

	dynamicSearchRect = { editRect.left - thisRect.left - 8, editRect.top - thisRect.top - 38 + editRect.Height() + 9, editRect.left - thisRect.left - 8 + editRect.Width() - 2,editRect.top - thisRect.top - 38 + editRect.Height() + 1 + 100 };
	worldsearchlist = new WorldSearchList(currentTheme, this);
	worldsearchlist->Create(IDD_DIALOG_SEARCH_LIST, this);
	worldsearchlist->MoveWindow(dynamicSearchRect);
	worldsearchlist->ShowWindow(SW_HIDE);
	TRACE(L"width : %d\n", dynamicSearchRect.Width());
	TRACE(L"height : %d\n", dynamicSearchRect.Height());
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void WorldClock::OnOK()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	//CDialogEx::OnOK();
}


void WorldClock::OnClose()
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CDialogEx::OnClose();
	WorldClock::PostNcDestroy();
}


void WorldClock::PostNcDestroy()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	CBOKOToolsDlg* parent = (CBOKOToolsDlg*)pParent;
	parent->bWorldClock = false;
	delete this;
	CDialogEx::PostNcDestroy();
}


BOOL WorldClock::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	// 에딧 마우스 좌클릭시 worldsearchlist sw_show 처리 (현재 edit 텍스트값 뽑아서 SearchClockListFromInputText() 함수 호출)

	return CDialogEx::PreTranslateMessage(pMsg);
}


HBRUSH WorldClock::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  여기서 DC의 특성을 변경합니다.
	if (nCtlColor == CTLCOLOR_EDIT)
	{
		if (pWnd->GetDlgCtrlID() == IDC_EDIT_WORLD_SEARCH)
		{
			pDC->SetBkColor(currentTheme->GetFunctionSubColor());
			pDC->SetTextColor(currentTheme->GetFunctionTextColor());
			hbr = (HBRUSH)m_backBrush;
		}
	}

	// TODO:  기본값이 적당하지 않으면 다른 브러시를 반환합니다.
	return hbr;
}


void WorldClock::OnEnChangeEditWorldSearch()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.

	// 동적으로 입력한 텍스트를 worldsearchlist에서 로드된 시간데이터와 비교하여 같은값만 worldsearchlist 화면에 출력
	// 입력한 값이 존재하면 worldsearchlist의 화면을 sh_show 하고 없으면 sh_hide 한다

	CString strSearchText;
	m_edit_search.GetWindowTextW(strSearchText);

	if (strSearchText.IsEmpty())
	{
		worldsearchlist->ShowWindow(SW_HIDE);
		return;
	}

	if (worldsearchlist->SearchClockListFromInputText(strSearchText))
	{
		worldsearchlist->ShowWindow(SW_SHOW);
	}
	else
	{
		worldsearchlist->ShowWindow(SW_HIDE);
	}
	
}
