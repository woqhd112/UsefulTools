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

	if (bCurTimeThread)
	{
		bCurTimeThread = false;
		DWORD nExitCode = NULL;

		GetExitCodeThread(m_curtimeThread->m_hThread, &nExitCode);
		if (TerminateThread(m_curtimeThread->m_hThread, nExitCode) != 0)
		{
			delete m_curtimeThread;
			m_curtimeThread = nullptr;
		}
	}
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

	this->SetWindowPos(NULL, 0, 0, 1000, 620, SWP_NOMOVE);
	m_btn_search.ShowWindow(SW_HIDE);
	m_edit_search.ShowWindow(SW_HIDE);
	m_stt_result_view.ShowWindow(SW_HIDE);


	analogwatch = new AnalogWatch(currentTheme, this);
	analogwatch->Create(IDD_DIALOG_ANALOG_WATCh, this);
	analogwatch->MoveWindow(50, 75, 200, 200 + 40 + 40 + 40);
	analogwatch->ShowWindow(SW_SHOW);
	AnalogWatch::ClockData* clockData = new AnalogWatch::ClockData;
	clockData->mainGWCD = WorldSearchList::GreenWichWorldClockData::SOUTHKOREA_SEOUL;
	clockData->subGWCD = WorldSearchList::GreenWichWorldClockData::SOUTHKOREA_SEOUL;
	clockData->strWorldCityName = analogwatch->worldsearchlist->GetWorldCityName(clockData->subGWCD);
	analogwatch->Initialize(clockData);
	analogwatch->bMainClock = true;

	AnalogWatch* newAnalogwatch1 = new AnalogWatch(currentTheme, this);
	newAnalogwatch1->Create(IDD_DIALOG_ANALOG_WATCh, this);
	newAnalogwatch1->MoveWindow(400, 20, 150, 150 + 40 + 40 + 40);
	newAnalogwatch1->ShowWindow(SW_SHOW);
	AnalogWatch::ClockData* clockData1 = new AnalogWatch::ClockData;
	clockData1->mainGWCD = WorldSearchList::GreenWichWorldClockData::SOUTHKOREA_SEOUL;
	clockData1->subGWCD = WorldSearchList::GreenWichWorldClockData::SOUTHKOREA_SEOUL;
	clockData1->strWorldCityName = analogwatch->worldsearchlist->GetWorldCityName(clockData->subGWCD);
	newAnalogwatch1->Initialize(clockData1);
	newAnalogwatch1->worldsearchlist->ModifyStyle(0, WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 0);
	subAnalogWatchVector.push_back(newAnalogwatch1);

	AnalogWatch* newAnalogwatch2 = new AnalogWatch(currentTheme, this);
	newAnalogwatch2->Create(IDD_DIALOG_ANALOG_WATCh, this);
	newAnalogwatch2->MoveWindow(600, 20, 150, 150 + 40 + 40 + 40);
	newAnalogwatch2->ShowWindow(SW_SHOW);
	AnalogWatch::ClockData* clockData2 = new AnalogWatch::ClockData;
	clockData2->mainGWCD = WorldSearchList::GreenWichWorldClockData::SOUTHKOREA_SEOUL;
	clockData2->subGWCD = WorldSearchList::GreenWichWorldClockData::SOUTHKOREA_SEOUL;
	clockData2->strWorldCityName = analogwatch->worldsearchlist->GetWorldCityName(clockData->subGWCD);
	newAnalogwatch2->Initialize(clockData2);
	newAnalogwatch2->worldsearchlist->ModifyStyle(0, WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 0);
	subAnalogWatchVector.push_back(newAnalogwatch2);

	AnalogWatch* newAnalogwatch3 = new AnalogWatch(currentTheme, this);
	newAnalogwatch3->Create(IDD_DIALOG_ANALOG_WATCh, this);
	newAnalogwatch3->MoveWindow(800, 20, 150, 150 + 40 + 40 + 40);
	newAnalogwatch3->ShowWindow(SW_SHOW);
	AnalogWatch::ClockData* clockData3 = new AnalogWatch::ClockData;
	clockData3->mainGWCD = WorldSearchList::GreenWichWorldClockData::SOUTHKOREA_SEOUL;
	clockData3->subGWCD = WorldSearchList::GreenWichWorldClockData::SOUTHKOREA_SEOUL;
	clockData3->strWorldCityName = analogwatch->worldsearchlist->GetWorldCityName(clockData->subGWCD);
	newAnalogwatch3->Initialize(clockData3);
	newAnalogwatch3->worldsearchlist->ModifyStyle(0, WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 0);
	subAnalogWatchVector.push_back(newAnalogwatch3);

	AnalogWatch* newAnalogwatch4 = new AnalogWatch(currentTheme, this);
	newAnalogwatch4->Create(IDD_DIALOG_ANALOG_WATCh, this);
	newAnalogwatch4->MoveWindow(500, 270 + 30, 150, 150 + 40 + 40 + 40);
	newAnalogwatch4->ShowWindow(SW_SHOW);
	AnalogWatch::ClockData* clockData4 = new AnalogWatch::ClockData;
	clockData4->mainGWCD = WorldSearchList::GreenWichWorldClockData::SOUTHKOREA_SEOUL;
	clockData4->subGWCD = WorldSearchList::GreenWichWorldClockData::SOUTHKOREA_SEOUL;
	clockData4->strWorldCityName = analogwatch->worldsearchlist->GetWorldCityName(clockData->subGWCD);
	newAnalogwatch4->Initialize(clockData4);
	subAnalogWatchVector.push_back(newAnalogwatch4);

	AnalogWatch* newAnalogwatch5 = new AnalogWatch(currentTheme, this);
	newAnalogwatch5->Create(IDD_DIALOG_ANALOG_WATCh, this);
	newAnalogwatch5->MoveWindow(700, 270 + 30, 150, 150 + 40 + 40 + 40);
	newAnalogwatch5->ShowWindow(SW_SHOW);
	AnalogWatch::ClockData* clockData5 = new AnalogWatch::ClockData;
	clockData5->mainGWCD = WorldSearchList::GreenWichWorldClockData::SOUTHKOREA_SEOUL;
	clockData5->subGWCD = WorldSearchList::GreenWichWorldClockData::SOUTHKOREA_SEOUL;
	clockData5->strWorldCityName = analogwatch->worldsearchlist->GetWorldCityName(clockData->subGWCD);
	newAnalogwatch5->Initialize(clockData5);
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

	bCurTimeThread = true;
	m_curtimeThread = AfxBeginThread(thrStartWorldClock, this);


	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

CString WorldClock::GetCurTime(double dErrorSubTimeValue)
{
	SYSTEMTIME cur_time;
	GetSystemTime(&cur_time);
	CTime cTime(cur_time);
	
	int hour = int(dErrorSubTimeValue);
	int minute = int((dErrorSubTimeValue - hour) * 60);
	cTime += CTimeSpan(0, hour, minute, 0);
	
	CString strTimeFormat;
	strTimeFormat.Format(_T("%04d:%02d:%02d:%02d:%02d:%02d"), cTime.GetYear(), cTime.GetMonth(), cTime.GetDay(), cTime.GetHour(), cTime.GetMinute(), cTime.GetSecond());

	return strTimeFormat;
}

UINT WorldClock::thrStartWorldClock(LPVOID method)
{
	WorldClock* worldclock = (WorldClock*)method;
	worldclock->StartWorldClock();

	return 0;
}

void WorldClock::FormatClockData(CString strInputTime, AnalogWatch::ClockData* inputTime)
{
	CString strYear, strMonth, strDay, strHour, strMinute, strSecond;
	AfxExtractSubString(strYear, strInputTime, 0, ':');
	AfxExtractSubString(strMonth, strInputTime, 1, ':');
	AfxExtractSubString(strDay, strInputTime, 2, ':');
	AfxExtractSubString(strHour, strInputTime, 3, ':');
	AfxExtractSubString(strMinute, strInputTime, 4, ':');
	AfxExtractSubString(strSecond, strInputTime, 5, ':');
	inputTime->m_nYear = _ttoi(strYear);
	inputTime->m_nMonth = _ttoi(strMonth);
	inputTime->m_nDay = _ttoi(strDay);
	inputTime->m_nHour = _ttoi(strHour);
	inputTime->m_nMinute = _ttoi(strMinute);
	inputTime->m_nSecond = _ttoi(strSecond);
}

void WorldClock::StartWorldClock()
{
	while (bCurTimeThread)
	{
		clock_t start, finish;
		double duration;

		start = clock();
		FormatClockData(GetCurTime(analogwatch->worldsearchlist->GetGMPCalcValue(analogwatch->clockData->subGWCD)), analogwatch->clockData);
		analogwatch->InvalidClockRect(analogwatch->clockData);
		for (int i = 0; i < (int)subAnalogWatchVector.size(); i++)
		{
			AnalogWatch::ClockData* clock = subAnalogWatchVector.at(i)->clockData;
			FormatClockData(GetCurTime(analogwatch->worldsearchlist->GetGMPCalcValue(clock->subGWCD)), clock);
			subAnalogWatchVector.at(i)->InvalidClockRect(clock);
		}
		finish = clock();
		duration = (double)(finish - start) / CLOCKS_PER_SEC;

		Sleep((1000 - (duration * 1000) <= 0) ? DWORD(0) : DWORD(1000 - (duration * 1000)));
	}
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
