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
	bWillModify = false;
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

	/*if (analogwatch)
	{
		delete analogwatch;
		analogwatch = nullptr;
	}*/

	for (int i = 0; i < (int)analogWatchVector.size(); i++)
	{
		AnalogWatch* deleteWatch = analogWatchVector.at(i);
		delete deleteWatch;
		deleteWatch = nullptr;
	}
	analogWatchVector.clear();

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
//9. xml값은 설정한 시계데이터 저장
//10. 적용버튼 클릭시 해당 시계의 전 데이터를 찾아 변경한 데이터로 수정 (xml 저장은 아직안됨)

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



	AnalogWatch* newAnalogwatch0 = new AnalogWatch(currentTheme, this);
	newAnalogwatch0->Create(IDD_DIALOG_ANALOG_WATCh, this);
	newAnalogwatch0->MoveWindow(50, 75, 200, 200 + 40 + 40 + 40);
	newAnalogwatch0->ShowWindow(SW_SHOW);
	analogWatchVector.push_back(newAnalogwatch0);

	AnalogWatch* newAnalogwatch1 = new AnalogWatch(currentTheme, this);
	newAnalogwatch1->Create(IDD_DIALOG_ANALOG_WATCh, this);
	newAnalogwatch1->MoveWindow(400, 20, 150, 150 + 40 + 40 + 40);
	newAnalogwatch1->ShowWindow(SW_SHOW);
	analogWatchVector.push_back(newAnalogwatch1);

	AnalogWatch* newAnalogwatch2 = new AnalogWatch(currentTheme, this);
	newAnalogwatch2->Create(IDD_DIALOG_ANALOG_WATCh, this);
	newAnalogwatch2->MoveWindow(600, 20, 150, 150 + 40 + 40 + 40);
	newAnalogwatch2->ShowWindow(SW_SHOW);
	analogWatchVector.push_back(newAnalogwatch2);

	AnalogWatch* newAnalogwatch3 = new AnalogWatch(currentTheme, this);
	newAnalogwatch3->Create(IDD_DIALOG_ANALOG_WATCh, this);
	newAnalogwatch3->MoveWindow(800, 20, 150, 150 + 40 + 40 + 40);
	newAnalogwatch3->ShowWindow(SW_SHOW);
	analogWatchVector.push_back(newAnalogwatch3);

	AnalogWatch* newAnalogwatch4 = new AnalogWatch(currentTheme, this);
	newAnalogwatch4->Create(IDD_DIALOG_ANALOG_WATCh, this);
	newAnalogwatch4->MoveWindow(500, 270 + 30, 150, 150 + 40 + 40 + 40);
	newAnalogwatch4->ShowWindow(SW_SHOW);
	analogWatchVector.push_back(newAnalogwatch4);

	AnalogWatch* newAnalogwatch5 = new AnalogWatch(currentTheme, this);
	newAnalogwatch5->Create(IDD_DIALOG_ANALOG_WATCh, this);
	newAnalogwatch5->MoveWindow(700, 270 + 30, 150, 150 + 40 + 40 + 40);
	newAnalogwatch5->ShowWindow(SW_SHOW);
	analogWatchVector.push_back(newAnalogwatch5);


	LoadWorldClockData();

	newAnalogwatch0->ModifyStyle(0, WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 0);
	newAnalogwatch1->ModifyStyle(0, WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 0);
	newAnalogwatch2->ModifyStyle(0, WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 0);
	newAnalogwatch3->ModifyStyle(0, WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 0);
	newAnalogwatch4->ModifyStyle(0, WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 0);
	newAnalogwatch5->ModifyStyle(0, WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 0);
	newAnalogwatch0->worldsearchlist->BringWindowToTop();
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

void WorldClock::LoadWorldClockData()
{
	bool bSavedXml = false;
	CMarkup markUp;

	CString szRoot = _T("");
	CreateConfigClockFile(szRoot);

	CString strFullPath = szRoot + _T("\\WorldClock.conf");

	if (markUp.Load(strFullPath))
	{
		markUp.FindElem(_T("Clock"));
		markUp.IntoElem();
		int nAnalogIdx = 0;
		while (markUp.FindElem(_T("data")))
		{
			if (nAnalogIdx >= 6) break;

			WorldSearchList::GreenWichWorldClockData thisErrorTimeValue = WorldSearchList::GreenWichWorldClockData(_ttoi(markUp.GetAttrib(_T("mainGWCD"))));
			WorldSearchList::GreenWichWorldClockData targetErrorTimeValue = WorldSearchList::GreenWichWorldClockData(_ttoi(markUp.GetAttrib(_T("subGWDC"))));
			CString strWorldName = markUp.GetAttrib(_T("worldcity"));
			AnalogWatch::ClockData* clockData = new AnalogWatch::ClockData;
			clockData->mainGWCD = thisErrorTimeValue;
			clockData->subGWCD = targetErrorTimeValue;
			clockData->strWorldCityName = strWorldName;

			AnalogWatch* analog = analogWatchVector.at(nAnalogIdx);
			analog->Initialize(clockData);
			analog->SetClockPriority(nAnalogIdx);
			nAnalogIdx++;
		}
	}
	else
	{
		CString szRoot = _T("");

		CreateConfigClockFile(szRoot);
		if (CreateDefaultClockXml(&markUp, szRoot)) bSavedXml = true;
		if (bSavedXml)
		{
			SaveXml(&markUp, strFullPath);
		}
	}
}


void WorldClock::CreateConfigClockFile(CString& strFullPath)
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
	CreateDefaultDirectory(strFullPath, _T("\\WorldClock"));
}

void WorldClock::SaveXml(CMarkup* markup, CString strSaveFullPath)
{
	CString strXML = markup->GetDoc();

	HRESULT hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);
	JWXml::CXml saveXML;
	saveXML.LoadXml((LPCTSTR)strXML);
	saveXML.SaveWithFormatted(strSaveFullPath);
	saveXML.Close();
	CoUninitialize();
}

void WorldClock::CreateDefaultDirectory(CString& strFullPath, CString strAppendPath)
{
	CFileFind findPath;
	strFullPath += strAppendPath;
	if (!findPath.FindFile(strFullPath))
	{
		CreateDirectory(strFullPath, NULL);
	}
	findPath.Close();
}

bool WorldClock::CreateDefaultClockXml(CMarkup* markUp, CString strFilePath)
{
	bool bReturn = false;
	CFileFind xmlFind;
	strFilePath += _T("\\WorldClock.conf");
	if (!xmlFind.FindFile(strFilePath))
	{
		markUp->AddElem(_T("Clock"));
		markUp->IntoElem();

		for (int i = 0; i < 6; i++)
		{
			markUp->AddElem(_T("data"));
			markUp->AddAttrib(_T("mainGWCD"), 9002);
			markUp->AddAttrib(_T("subGWDC"), 9002);
			markUp->AddAttrib(_T("worldcity"), _T("대한민국 - 서울"));

			WorldSearchList::GreenWichWorldClockData thisErrorTimeValue = WorldSearchList::GreenWichWorldClockData::SOUTHKOREA_SEOUL;
			WorldSearchList::GreenWichWorldClockData targetErrorTimeValue = WorldSearchList::GreenWichWorldClockData::SOUTHKOREA_SEOUL;
			CString strWorldName = _T("대한민국 - 서울");
			AnalogWatch::ClockData* clockData = new AnalogWatch::ClockData;
			clockData->mainGWCD = thisErrorTimeValue;
			clockData->subGWCD = targetErrorTimeValue;
			clockData->strWorldCityName = strWorldName;

			AnalogWatch* analog = analogWatchVector.at(i);
			analog->Initialize(clockData);
			analog->SetClockPriority(i);
		}

		bReturn = true;
	}
	xmlFind.Close();

	return bReturn;
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

		if (!bWillModify)
		{
			for (int i = 0; i < (int)analogWatchVector.size(); i++)
			{
				AnalogWatch::ClockData* clock = analogWatchVector.at(i)->clockData;
				FormatClockData(GetCurTime(analogWatchVector.at(i)->worldsearchlist->GetGMPCalcValue(clock->subGWCD)), clock);
				analogWatchVector.at(i)->InvalidClockRect(clock);
			}
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
	if (pMsg->message == WM_LBUTTONUP)
	{
		if (pMsg->hwnd == this->m_hWnd)
		{
			//analogwatch->worldsearchlist->ShowWindow(SW_HIDE);
			for (int i = 0; i < (int)analogWatchVector.size(); i++)
			{
				analogWatchVector.at(i)->worldsearchlist->ShowWindow(SW_HIDE);
			}
			bWillModify = false;
		}
	}


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
