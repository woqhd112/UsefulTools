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
	/*if (worldclocklist)
	{
		delete worldclocklist;
		worldclocklist = nullptr;
	}

	if (worldsearchlist)
	{
		delete worldsearchlist;
		worldsearchlist = nullptr;
	}*/

	if (analogwatch)
	{
		delete analogwatch;
		analogwatch = nullptr;
	}

	for (int i = 0; i < (int)subAnalogWatchVector.size(); i++)
	{
		AnalogWatch* deleteWatch = subAnalogWatchVector.at(i);
		delete deleteWatch;
		deleteWatch = nullptr;
	}
	subAnalogWatchVector.clear();
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
	ON_BN_CLICKED(IDC_BUTTON_WORLD_SEARCH, &WorldClock::OnBnClickedButtonWorldSearch)
END_MESSAGE_MAP()


// WorldClock 메시지 처리기
// 변경해야하는 사항
//1. 메인시계는 시간값 변경가능
//2. 서브시계들은 메인시계의 시간값에따라 gmp값을 추가하여 설정
//3. 메인시계는 로컬타임 동기화버튼 지원함
//4. 아날로그시게의 static은 국가명 - 도시명 \r\n 년월일 출력
//5. 아날로그시계 가운데에 am\pm 추가
//6. 시계 스타트 스레드는 worldclock에서 작동
//7. 스레드함수 안에서 각 analogwatch 객체의 시간값 변경하여 invalidrect 수행
//8. analogwatch 객체에는 시간값 데이터만 갱신시키고 스레드는 수행하지않음.
//9. xml값은 설정한 시계데이터 저장
//10. 적용버튼 클릭시 해당 시계의 전 데이터를 찾아 변경한 데이터로 수정

BOOL WorldClock::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	this->SetBackgroundColor(currentTheme->GetFunctionBkColor());
	m_backBrush.CreateSolidBrush(currentTheme->GetFunctionSubColor());

	m_btn_search.Initialize(currentTheme->GetButtonColor(), CMFCButton::FlatStyle::BUTTONSTYLE_NOBORDERS, _T("godoMaum"), 30);
	m_btn_search.SetTextColor(currentTheme->GetTextColor());
	m_edit_search.Initialize(40, _T("godoMaum"));

	this->SetWindowPos(NULL, 0, 0, 1000, 550, SWP_NOMOVE);
	m_btn_search.ShowWindow(SW_HIDE);
	m_edit_search.ShowWindow(SW_HIDE);
	m_stt_result_view.ShowWindow(SW_HIDE);


	analogwatch = new AnalogWatch(currentTheme, this);
	analogwatch->Create(IDD_DIALOG_ANALOG_WATCh, this);
	analogwatch->MoveWindow(50, 75, 200, 200 + 40 + 40);
	analogwatch->ShowWindow(SW_SHOW);
	analogwatch->Initialize();

	AnalogWatch* newAnalogwatch1 = new AnalogWatch(currentTheme, this);
	newAnalogwatch1->Create(IDD_DIALOG_ANALOG_WATCh, this);
	newAnalogwatch1->MoveWindow(400, 20, 150, 150 + 40 + 40);
	newAnalogwatch1->ShowWindow(SW_SHOW);
	newAnalogwatch1->Initialize();
	newAnalogwatch1->worldsearchlist->ModifyStyle(0, WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 0);
	subAnalogWatchVector.push_back(newAnalogwatch1);

	AnalogWatch* newAnalogwatch2 = new AnalogWatch(currentTheme, this);
	newAnalogwatch2->Create(IDD_DIALOG_ANALOG_WATCh, this);
	newAnalogwatch2->MoveWindow(600, 20, 150, 150 + 40 + 40);
	newAnalogwatch2->ShowWindow(SW_SHOW);
	newAnalogwatch2->Initialize();
	newAnalogwatch2->worldsearchlist->ModifyStyle(0, WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 0);
	subAnalogWatchVector.push_back(newAnalogwatch2);

	AnalogWatch* newAnalogwatch3 = new AnalogWatch(currentTheme, this);
	newAnalogwatch3->Create(IDD_DIALOG_ANALOG_WATCh, this);
	newAnalogwatch3->MoveWindow(800, 20, 150, 150 + 40 + 40);
	newAnalogwatch3->ShowWindow(SW_SHOW);
	newAnalogwatch3->Initialize();
	newAnalogwatch3->worldsearchlist->ModifyStyle(0, WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 0);
	subAnalogWatchVector.push_back(newAnalogwatch3);

	AnalogWatch* newAnalogwatch4 = new AnalogWatch(currentTheme, this);
	newAnalogwatch4->Create(IDD_DIALOG_ANALOG_WATCh, this);
	newAnalogwatch4->MoveWindow(500, 270, 150, 150 + 40 + 40);
	newAnalogwatch4->ShowWindow(SW_SHOW);
	newAnalogwatch4->Initialize();
	subAnalogWatchVector.push_back(newAnalogwatch4);

	AnalogWatch* newAnalogwatch5 = new AnalogWatch(currentTheme, this);
	newAnalogwatch5->Create(IDD_DIALOG_ANALOG_WATCh, this);
	newAnalogwatch5->MoveWindow(700, 270, 150, 150 + 40 + 40);
	newAnalogwatch5->ShowWindow(SW_SHOW);
	newAnalogwatch5->Initialize();
	subAnalogWatchVector.push_back(newAnalogwatch5);

	analogwatch->ModifyStyle(0, WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 0);
	newAnalogwatch1->ModifyStyle(0, WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 0);
	newAnalogwatch2->ModifyStyle(0, WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 0);
	newAnalogwatch3->ModifyStyle(0, WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 0);
	newAnalogwatch4->ModifyStyle(0, WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 0);
	newAnalogwatch5->ModifyStyle(0, WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 0);
	analogwatch->worldsearchlist->BringWindowToTop();
	newAnalogwatch1->worldsearchlist->BringWindowToTop();
	newAnalogwatch2->worldsearchlist->BringWindowToTop();
	newAnalogwatch3->worldsearchlist->BringWindowToTop();
	newAnalogwatch4->worldsearchlist->BringWindowToTop();
	newAnalogwatch5->worldsearchlist->BringWindowToTop();


	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}
//
//WorldClockList* WorldClock::GetClockInstance() const
//{
//	return worldclocklist;
//}
//
//WorldSearchList* WorldClock::GetSearchInstance() const
//{
//	return worldsearchlist;
//}

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
	/*if (pMsg->message == WM_LBUTTONUP)
	{
		if (pMsg->hwnd == this->m_hWnd)
		{
			worldsearchlist->ShowWindow(SW_HIDE);
		}
		else if (pMsg->hwnd == m_edit_search.m_hWnd)
		{
			CString strSearchText;
			m_edit_search.GetWindowTextW(strSearchText);

			if (worldsearchlist->SearchClockListFromInputText(strSearchText))
			{
				worldsearchlist->ShowWindow(SW_SHOW);
			}
			m_edit_search.SetFocus();
		}
	}*/


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

	/*CString strSearchText;
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
	m_edit_search.SetFocus();*/
	
}


void WorldClock::OnBnClickedButtonWorldSearch()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	/*CString strSearchText;
	m_edit_search.GetWindowTextW(strSearchText);

	if (worldsearchlist->SearchClockListFromInputText(strSearchText))
	{
		worldsearchlist->ShowWindow(SW_SHOW);
	}
	m_edit_search.SetFocus();*/
}
