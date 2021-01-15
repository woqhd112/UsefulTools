// WorldClock.cpp: 구현 파일
//

#include "pch.h"
#include "BOKOTools.h"
#include "WorldClock.h"
#include "BOKOToolsDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// WorldClock 대화 상자

IMPLEMENT_DYNAMIC(WorldClock, CDialogEx)

WorldClock::WorldClock(ThemeData* currentTheme, CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_WORLD_CLOCK, pParent)
{
	this->pParent = pParent;
	this->currentTheme = currentTheme;
	bWillModify = false;
	bCurTimeThread = false;
	nErrorTimeHour = 0;
	nErrorTimeMinute = 0;
	nErrorTimeSecond = 0;
}

WorldClock::~WorldClock()
{
	for (int i = 0; i < (int)clockDataVector.size(); i++)
	{
		AnalogWatch::ClockData* deleteClock = clockDataVector.at(i);
		delete deleteClock;
		deleteClock = nullptr;
	}
	clockDataVector.clear();

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
	DDX_Control(pDX, IDC_BUTTON_WORLDCLOCK_SYNCRONIZE, m_btn_worldclock_localtime_sync);
	DDX_Control(pDX, IDC_STATIC_CLOCK_OFFSET, m_stt_clock_offset);
}


BEGIN_MESSAGE_MAP(WorldClock, CDialogEx)
	ON_WM_CLOSE()
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BUTTON_WORLDCLOCK_SYNCRONIZE, &WorldClock::OnBnClickedButtonWorldclockSyncronize)
END_MESSAGE_MAP()


// WorldClock 메시지 처리기
// 변경해야하는 사항
//1. 메인시계는 시간값 변경가능
//2. 서브시계들은 메인시계의 시간값에따라 gmp값을 추가하여 설정
//3. 메인시계는 로컬타임 동기화버튼 지원함


BOOL WorldClock::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	this->SetBackgroundColor(currentTheme->GetFunctionBkColor());
	m_backBrush.CreateSolidBrush(currentTheme->GetFunctionBkColor());

	m_btn_worldclock_localtime_sync.Initialize(currentTheme->GetButtonColor(), CMFCButton::FlatStyle::BUTTONSTYLE_NOBORDERS, _T("가비아 솔미체"), 18);
	m_btn_worldclock_localtime_sync.SetTextColor(currentTheme->GetTextColor());
	m_stt_clock_offset.Initialize(25, _T("가비아 솔미체"));

	this->SetWindowPos(NULL, 0, 0, 1000, 620, SWP_NOMOVE);

	m_stt_clock_offset.MoveWindow(80, 90 + 200 + 40 + 40 + 40, 210, 30);
	m_stt_clock_offset.SetWindowTextW(_T("시간 오차 : + 00:00:00"));
	m_btn_worldclock_localtime_sync.MoveWindow(80, 90 + 200 + 40 + 40 + 40 + 35, 110, 20);

	AnalogWatch* newAnalogwatch0 = new AnalogWatch(currentTheme, this);
	newAnalogwatch0->Create(IDD_DIALOG_ANALOG_WATCH, this);
	newAnalogwatch0->MoveWindow(80, 90, 210, 200 + 40 + 40 + 40);
	newAnalogwatch0->ShowWindow(SW_SHOW);
	analogWatchVector.push_back(newAnalogwatch0);

	AnalogWatch* newAnalogwatch1 = new AnalogWatch(currentTheme, this);
	newAnalogwatch1->Create(IDD_DIALOG_ANALOG_WATCH, this);
	newAnalogwatch1->MoveWindow(365, 20, 160, 150 + 40 + 40 + 40);
	newAnalogwatch1->ShowWindow(SW_SHOW);
	analogWatchVector.push_back(newAnalogwatch1);

	AnalogWatch* newAnalogwatch2 = new AnalogWatch(currentTheme, this);
	newAnalogwatch2->Create(IDD_DIALOG_ANALOG_WATCH, this);
	newAnalogwatch2->MoveWindow(565, 20, 160, 150 + 40 + 40 + 40);
	newAnalogwatch2->ShowWindow(SW_SHOW);
	analogWatchVector.push_back(newAnalogwatch2);

	AnalogWatch* newAnalogwatch3 = new AnalogWatch(currentTheme, this);
	newAnalogwatch3->Create(IDD_DIALOG_ANALOG_WATCH, this);
	newAnalogwatch3->MoveWindow(765, 20, 160, 150 + 40 + 40 + 40);
	newAnalogwatch3->ShowWindow(SW_SHOW);
	analogWatchVector.push_back(newAnalogwatch3);

	AnalogWatch* newAnalogwatch4 = new AnalogWatch(currentTheme, this);
	newAnalogwatch4->Create(IDD_DIALOG_ANALOG_WATCH, this);
	newAnalogwatch4->MoveWindow(465, 270 + 30, 160, 150 + 40 + 40 + 40);
	newAnalogwatch4->ShowWindow(SW_SHOW);
	analogWatchVector.push_back(newAnalogwatch4);

	AnalogWatch* newAnalogwatch5 = new AnalogWatch(currentTheme, this);
	newAnalogwatch5->Create(IDD_DIALOG_ANALOG_WATCH, this);
	newAnalogwatch5->MoveWindow(665, 270 + 30, 160, 150 + 40 + 40 + 40);
	newAnalogwatch5->ShowWindow(SW_SHOW);
	analogWatchVector.push_back(newAnalogwatch5);

	if (LoadWorldClockData())
	{
		newAnalogwatch0->worldsearchlist->ModifyStyle(0, WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 0);
		newAnalogwatch1->worldsearchlist->ModifyStyle(0, WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 0);
		newAnalogwatch2->worldsearchlist->ModifyStyle(0, WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 0);
		newAnalogwatch3->worldsearchlist->ModifyStyle(0, WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 0);
		newAnalogwatch4->worldsearchlist->ModifyStyle(0, WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 0);
		newAnalogwatch5->worldsearchlist->ModifyStyle(0, WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 0);
		newAnalogwatch0->m_edit_digital_clock.ModifyStyle(0, WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 0);
		newAnalogwatch1->m_edit_digital_clock.ModifyStyle(0, WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 0);
		newAnalogwatch2->m_edit_digital_clock.ModifyStyle(0, WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 0);
		newAnalogwatch3->m_edit_digital_clock.ModifyStyle(0, WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 0);
		newAnalogwatch4->m_edit_digital_clock.ModifyStyle(0, WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 0);
		newAnalogwatch5->m_edit_digital_clock.ModifyStyle(0, WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 0);
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
	}
	else
	{
		MessageBox(_T("Config 폴더 안의 WorldClock.conf 파일 설정값이 잘못되었습니다.\n 해당 파일을 삭제하고 다시 실행하여 주십시오."));
		PostMessage(WM_CLOSE, 0, 0);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

bool WorldClock::LoadWorldClockData()
{
	bool bReturn = false;
	bool bSavedXml = false;
	CMarkup markUp;

	CString szRoot = _T("");
	CreateConfigClockFile(szRoot);

	CString strFullPath = szRoot + _T("\\WorldClock.conf");

	if (markUp.Load(strFullPath))
	{
		markUp.FindElem(_T("Clock"));
		markUp.IntoElem();
		while (markUp.FindElem(_T("data")))
		{
			WorldSearchList::GreenWichWorldClockData thisErrorTimeValue = WorldSearchList::GreenWichWorldClockData(_ttoi(markUp.GetAttrib(_T("mainGWCD"))));
			WorldSearchList::GreenWichWorldClockData targetErrorTimeValue = WorldSearchList::GreenWichWorldClockData(_ttoi(markUp.GetAttrib(_T("subGWDC"))));
			CString strWorldName = markUp.GetAttrib(_T("worldcity"));
			int nClockIdx = _ttoi(markUp.GetAttrib(_T("clockidx")));
			AnalogWatch::ClockData* clockData = new AnalogWatch::ClockData;
			clockData->mainGWCD = thisErrorTimeValue;
			clockData->subGWCD = targetErrorTimeValue;
			clockData->strWorldCityName = strWorldName;
			clockDataVector.push_back(clockData);

			AnalogWatch* analog = analogWatchVector.at(nClockIdx);
			analog->SetClockPriority(nClockIdx);
			analog->Initialize(clockData);
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

	if (clockDataVector.size() == 6)
	{
		bReturn = true;
		for (int i = 0; i < (int)analogWatchVector.size(); i++)
		{
			if (analogWatchVector.at(i)->worldsearchlist->GetWorldCityName(analogWatchVector.at(i)->clockData->mainGWCD) == _T("")) bReturn = false;
			if (analogWatchVector.at(i)->worldsearchlist->GetWorldCityName(analogWatchVector.at(i)->clockData->subGWCD) == _T("")) bReturn = false;
			if (analogWatchVector.at(i)->worldsearchlist->GetWorldClockData(analogWatchVector.at(i)->clockData->strWorldCityName) == WorldSearchList::GreenWichWorldClockData::WORLD_CLOCK_NONE) bReturn = false;
		}
	}


	return bReturn;
}

void WorldClock::SaveClockXml(int nClockIdx)
{
	CMarkup markUp;
	CString szRoot = _T("");
	CreateConfigClockFile(szRoot);
	CString strFullPath = szRoot + _T("\\WorldClock.conf");

	if (markUp.Load(strFullPath))
	{
		if (markUp.FindElem(_T("Clock")))
		{
			markUp.IntoElem();
			while (markUp.FindElem(_T("data")))
			{
				if (_ttoi(markUp.GetAttrib(_T("clockidx"))) == nClockIdx)
				{
					markUp.SetAttrib(_T("mainGWCD"), analogWatchVector.at(nClockIdx)->clockData->mainGWCD);
					markUp.SetAttrib(_T("subGWDC"), analogWatchVector.at(nClockIdx)->clockData->subGWCD);
					markUp.SetAttrib(_T("worldcity"), analogWatchVector.at(nClockIdx)->clockData->strWorldCityName);
					break;
				}
			}
		}
	}

	SaveXml(&markUp, strFullPath);
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
			markUp->AddAttrib(_T("clockidx"), i);

			WorldSearchList::GreenWichWorldClockData thisErrorTimeValue = WorldSearchList::GreenWichWorldClockData::SOUTHKOREA_SEOUL;
			WorldSearchList::GreenWichWorldClockData targetErrorTimeValue = WorldSearchList::GreenWichWorldClockData::SOUTHKOREA_SEOUL;
			CString strWorldName = _T("대한민국 - 서울");
			AnalogWatch::ClockData* clockData = new AnalogWatch::ClockData;
			clockData->mainGWCD = thisErrorTimeValue;
			clockData->subGWCD = targetErrorTimeValue;
			clockData->strWorldCityName = strWorldName;
			clockDataVector.push_back(clockData);

			AnalogWatch* analog = analogWatchVector.at(i);
			analog->SetClockPriority(i);
			analog->Initialize(clockData);
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
	inputTime->curTimeVal = CTime(_ttoi(strYear), _ttoi(strMonth), _ttoi(strDay), _ttoi(strHour), _ttoi(strMinute), _ttoi(strSecond));
}

void WorldClock::StartWorldClock()
{
	while (bCurTimeThread)
	{
		clock_t start, finish;
		double duration;

		start = clock();

		for (int i = 0; i < (int)analogWatchVector.size(); i++)
		{
			AnalogWatch::ClockData* clock = analogWatchVector.at(i)->clockData;
			FormatClockData(GetCurTime(analogWatchVector.at(i)->worldsearchlist->GetGMPCalcValue(clock->subGWCD)), clock);

			if (analogWatchVector.at(i)->bTimeSync) ErrorTimeCalc(clock);

			analogWatchVector.at(i)->InvalidClockRect(clock);
		}

		finish = clock();
		duration = (double)(finish - start) / CLOCKS_PER_SEC;

		Sleep((1000 - (duration * 1000) <= 0) ? DWORD(0) : DWORD(1000 - (duration * 1000)));
	}
}

void WorldClock::ErrorTimeCalc(AnalogWatch::ClockData* inputTime)
{
	inputTime->curTimeVal -= CTimeSpan(0, nErrorTimeHour, nErrorTimeMinute, nErrorTimeSecond);

	int nOffsetHour = nErrorTimeHour * 60 * 60;
	int nOffsetMinute = nErrorTimeMinute * 60;
	int nOffsetSecond = nErrorTimeSecond;
	int nOffset = nOffsetHour + nOffsetMinute + nOffsetSecond;
	unsigned int absOffset = abs(nOffset);
	CString strSymbol, strOffsetTime;
	if (nOffset > 0) strSymbol = _T("-"); 
	else			 strSymbol = _T("+");

	nOffsetHour = absOffset / 3600;
	nOffsetMinute = (absOffset % 3600) / 60;
	nOffsetSecond = (absOffset % 3600) % 60;

	strOffsetTime.Format(_T("시간 오차 : %s %02d:%02d:%02d"), strSymbol, nOffsetHour, nOffsetMinute, nOffsetSecond);
	m_stt_clock_offset.SetWindowTextW(strOffsetTime);
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
			if (bWillModify) analogWatchVector.at(0)->SetErrorTime();

			bWillModify = false;
			for (int i = 0; i < (int)analogWatchVector.size(); i++)
			{
				analogWatchVector.at(i)->worldsearchlist->ShowWindow(SW_HIDE);
				analogWatchVector.at(i)->SetFocus();
				analogWatchVector.at(i)->m_edit_digital_clock.HideCaret();
			}
		}
	}
	else if (pMsg->message == WM_KEYDOWN)
	{
		if (pMsg->wParam == VK_ESCAPE)
		{
			return TRUE;
		}
	}


	return CDialogEx::PreTranslateMessage(pMsg);
}


HBRUSH WorldClock::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  여기서 DC의 특성을 변경합니다.
	if (nCtlColor == CTLCOLOR_STATIC)
	{
		if (pWnd->GetDlgCtrlID() == m_stt_clock_offset.GetDlgCtrlID())
		{
			pDC->SetBkColor(currentTheme->GetFunctionBkColor());
			pDC->SetTextColor(currentTheme->GetTextColor());
			hbr = (HBRUSH)m_backBrush;
		}
	}

	// TODO:  기본값이 적당하지 않으면 다른 브러시를 반환합니다.
	return hbr;
}


void WorldClock::OnBnClickedButtonWorldclockSyncronize()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (MessageBox(_T("로컬 시간으로 동기화 하시겠습니까?"), _T("동기화"), MB_ICONQUESTION | MB_OKCANCEL) == IDOK)
	{
		for (int i = 0; i < (int)analogWatchVector.size(); i++)
		{
			analogWatchVector.at(i)->bTimeSync = false;
		}
		nErrorTimeHour = 0;
		nErrorTimeMinute = 0;
		nErrorTimeSecond = 0;
		m_stt_clock_offset.SetWindowTextW(_T("시간 오차 : + 00:00:00"));
	}
}
