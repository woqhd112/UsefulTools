// WorldClockList.cpp: 구현 파일
//

#include "pch.h"
#include "BOKOTools.h"
#include "WorldClockList.h"
#include "WorldClock.h"
#include "afxdialogex.h"


// WorldClockList 대화 상자

IMPLEMENT_DYNAMIC(WorldClockList, CDialogEx)

WorldClockList::WorldClockList(ThemeData* currentTheme, CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_WORLD_LIST, pParent)
{
	this->currentTheme = currentTheme;
	this->pParent = pParent;
	nWorldButtonID = 58000;
	nClockButtonPos_x = 2;
	nClockButtonPos_y = 2;
	nClockButtonWidth = 259;
	nClockButtonHeight = 37;
	nButtonCount = 0;
	nDetectHeight = 0;
}

WorldClockList::~WorldClockList()
{
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

	for (int i = 0; i < (int)clockButtonVector.size(); i++)
	{
		CalculateButton* deleteButton = clockButtonVector.at(i);
		CalculateStatic* deleteStatic = clockStaticVector.at(i);
		delete deleteButton;
		delete deleteStatic;
		deleteButton = nullptr;
		deleteStatic = nullptr;
	}
	clockButtonVector.clear();
	clockStaticVector.clear();
	clockDataVector.clear();
}

void WorldClockList::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(WorldClockList, CDialogEx)
	ON_WM_CTLCOLOR()
	ON_WM_PAINT()
	ON_WM_VSCROLL()
	ON_WM_MOUSEWHEEL()
END_MESSAGE_MAP()


// WorldClockList 메시지 처리기


BOOL WorldClockList::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	m_backBrush.CreateSolidBrush(currentTheme->GetButtonColor());
	nBrightness = GetBrightness(GetRValue(currentTheme->GetFunctionSubColor()), GetGValue(currentTheme->GetFunctionSubColor()), GetBValue(currentTheme->GetFunctionSubColor()));

	if (nBrightness > 120)
		bkBorderColor = RGB(0, 0, 0);
	else
		bkBorderColor = RGB(255, 255, 255);

	this->SetBackgroundColor(currentTheme->GetFunctionSubColor());

	worldclock = (WorldClock*)pParent;

	//HINSTANCE hResInstanceBold = AfxGetResourceHandle();
	//HINSTANCE hResInstanceRegular = AfxGetResourceHandle();

	//HRSRC res = FindResource(hResInstanceBold,
	//	MAKEINTRESOURCE(IDR_TEXT_FONT_DIGITAL), L"TEXT");

	//if (res)
	//{
	//	HGLOBAL mem = LoadResource(hResInstanceBold, res);
	//	void *data = LockResource(mem);
	//	size_t len = SizeofResource(hResInstanceBold, res);

	//	DWORD nFonts;
	//	m_fonthandle = AddFontMemResourceEx(
	//		data,       // font resource
	//		(DWORD)len,       // number of bytes in font resource 
	//		NULL,          // Reserved. Must be 0.
	//		&nFonts      // number of fonts installed
	//	);

	//	if (m_fonthandle == 0)
	//	{
	//		TRACE("실패");
	//	}
	//}

	scroll.Create(this);
	CustomScroll::CustomScrollInfo csi;
	csi.cst = CustomScroll::CUSTOM_SCROLL_TYPE_DEFAULT;
	csi.nAllPageSize = 0;
	csi.nKindOfScrollFlags = SB_VERT;
	csi.nOnePageSize = 236;
	csi.nScrollPos = 0;
	csi.nWheelValue = 234;
	scroll.Initialize(csi);

	// 로드 xml로 설정
	LoadWorldClock();

	bCurTimeThread = true;
	m_curtimeThread = AfxBeginThread(thrStartWorldTime, this);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void WorldClockList::LoadWorldClock()
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
		while (markUp.FindElem(_T("data")))
		{
			double dErrorTimeValue = _ttof(markUp.GetAttrib(_T("error")));
			CString strWorldName = markUp.GetAttrib(_T("world"));
			CString strCityName = markUp.GetAttrib(_T("city"));
			AddClock(dErrorTimeValue, strWorldName, strCityName);
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

void WorldClockList::CreateConfigClockFile(CString& strFullPath)
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

void WorldClockList::SaveXml(CMarkup* markup, CString strSaveFullPath)
{
	CString strXML = markup->GetDoc();

	HRESULT hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);
	JWXml::CXml saveXML;
	saveXML.LoadXml((LPCTSTR)strXML);
	saveXML.SaveWithFormatted(strSaveFullPath);
	saveXML.Close();
	CoUninitialize();
}

void WorldClockList::CreateDefaultDirectory(CString& strFullPath, CString strAppendPath)
{
	CFileFind findPath;
	strFullPath += strAppendPath;
	if (!findPath.FindFile(strFullPath))
	{
		CreateDirectory(strFullPath, NULL);
	}
	findPath.Close();
}

bool WorldClockList::CreateDefaultClockXml(CMarkup* markUp, CString strFilePath)
{
	bool bReturn = false;
	CFileFind xmlFind;
	strFilePath += _T("\\WorldClock.conf");
	if (!xmlFind.FindFile(strFilePath))
	{
		markUp->AddElem(_T("Clock"));
		markUp->IntoElem();
		markUp->AddElem(_T("data"));
		markUp->AddAttrib(_T("error"), 8);
		markUp->AddAttrib(_T("world"), _T("대한민국 "));
		markUp->AddAttrib(_T("city"), _T(" 서울"));

		AddClock(8, _T("대한민국 "), _T(" 서울"));

		bReturn = true;
	}
	xmlFind.Close();

	return bReturn;
}


UINT WorldClockList::thrStartWorldTime(LPVOID method)
{
	WorldClockList* thisDlg = (WorldClockList*)method;
	thisDlg->StartWorldTime();

	return 0;
}

void WorldClockList::StartWorldTime()
{
	CString strFullTime;
	while (bCurTimeThread)
	{
		clock_t start, finish;
		double duration;

		start = clock();
		for (int i = 0; i < (int)clockStaticVector.size(); i++)
		{
			CalculateStatic* timeStatic = clockStaticVector.at(i);
			strFullTime = GetCurTime(clockDataVector.at(i));
			timeStatic->SetWindowTextW(strFullTime);
		}
		finish = clock();
		duration = (double)(finish - start) / CLOCKS_PER_SEC;
		Sleep((1000 - (duration * 1000) <= 0) ? DWORD(0) : DWORD(1000 - (duration * 1000)));
	}
}


void WorldClockList::OnOK()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	//CDialogEx::OnOK();
}


BOOL WorldClockList::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	if (pMsg->message == WM_LBUTTONUP)
	{
		worldclock->GetSearchInstance()->ShowWindow(SW_HIDE);
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}


HBRUSH WorldClockList::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  여기서 DC의 특성을 변경합니다.
	if (nCtlColor == CTLCOLOR_STATIC)
	{
		pDC->SetBkColor(currentTheme->GetButtonColor());
		hbr = (HBRUSH)m_backBrush;
	}

	// TODO:  기본값이 적당하지 않으면 다른 브러시를 반환합니다.
	return hbr;
}


void WorldClockList::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 여기에 메시지 처리기 코드를 추가합니다.
					   // 그리기 메시지에 대해서는 CDialogEx::OnPaint()을(를) 호출하지 마십시오.

	CRect thisRect;
	GetWindowRect(thisRect);
	dc.Draw3dRect(0, 0, thisRect.Width(), thisRect.Height(), bkBorderColor, bkBorderColor);
}

CString WorldClockList::GetCurTime(double dErrorTimeValue)
{
	CTime cTime = CTime::GetCurrentTime();
	dErrorTimeValue = 8 - dErrorTimeValue;

	int hour = int(dErrorTimeValue);
	int minute = int((dErrorTimeValue - hour) * 60);

	int nTimeHour = cTime.GetHour() - hour;
	if (nTimeHour < 0)
	{
		nTimeHour += 12;
	}
	else if (nTimeHour >= 24)
	{
		nTimeHour -= 24;
	}
	int nTimeMinute = cTime.GetMinute() - minute;
	int nTimeSecond = cTime.GetSecond();
	CString strTimeFormat;
	strTimeFormat.Format(_T("%02d:%02d:%02d"), nTimeHour, nTimeMinute, nTimeSecond);

	return strTimeFormat;
}

bool WorldClockList::AddClock(double dErrorTimeValue, CString strWorldClockName, CString strCityClockName)
{
	if (clockButtonVector.size() >= 20)
	{
		MessageBox(_T("시계는 최대 20개 까지 등록 가능합니다."));
		return false;
	}

	// 여기에 시간값 넣는 함수 추가
	CalculateButton* newSearchButton = new CalculateButton;
	newSearchButton->Create(strWorldClockName + _T("\r\n") + strCityClockName, BS_PUSHBUTTON, CRect(0, 0, 0, 0), this, nWorldButtonID++);
	nDetectHeight = nClockButtonPos_y + ((2 + nClockButtonHeight) * (nButtonCount - (6 * (scroll.GetCurrentLinePos() - 1))));
	newSearchButton->MoveWindow(nClockButtonPos_x, nDetectHeight, nClockButtonWidth, nClockButtonHeight);
	newSearchButton->ShowWindow(SW_SHOW);
	newSearchButton->Initialize(currentTheme->GetButtonColor(), CMFCButton::FlatStyle::BUTTONSTYLE_NOBORDERS);
	newSearchButton->SetAlignment(CMFCButton::AlignStyle::ALIGN_LEFT);
	newSearchButton->Invalidate();
	clockButtonVector.push_back(newSearchButton);

	CalculateStatic* newSearchStatic = new CalculateStatic;
	newSearchStatic->Create(GetCurTime(dErrorTimeValue), SS_CENTER, CRect(0, 0, 0, 0), this, nWorldButtonID++);
	newSearchStatic->MoveWindow(nClockButtonPos_x + 100, nDetectHeight + 4, nClockButtonWidth - 100 - 4, nClockButtonHeight - 8);
	newSearchStatic->ShowWindow(SW_SHOW);
	CFont fnt;
	LOGFONT lf;
	::ZeroMemory(&lf, sizeof(lf));
	lf.lfHeight = 30;
	lf.lfWeight = FW_BOLD;
	_tcscpy_s(lf.lfFaceName, L"DS-Digital");
	fnt.CreateFontIndirect(&lf);
	newSearchStatic->SetFont(&fnt);
	fnt.Detach();
	clockStaticVector.push_back(newSearchStatic);
	clockDataVector.push_back(dErrorTimeValue);

	newSearchButton->ModifyStyle(0, WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 0);
	newSearchStatic->ModifyStyle(0, WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 0);
	newSearchStatic->BringWindowToTop();

	nButtonCount++;


	if (((int)clockButtonVector.size() - 1) % 6 == 0)
	{
		scroll.LineEnd();
	}
	scroll.ExecuteScrollPos(currentTheme);

	// xml 업데이트 함수

	return true;
}

void WorldClockList::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	scroll.OperateScroll(nSBCode, nPos);
	CDialogEx::OnVScroll(nSBCode, nPos, pScrollBar);
	Invalidate();
}


BOOL WorldClockList::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (scroll.GetLineCount() > 1)
	{
		UINT nFlag = scroll.OperateWheel(zDelta);
		if (nFlag == SB_PAGEUP && scroll.GetCurrentLinePos() == 1) {}
		else if (nFlag == SB_PAGEDOWN && scroll.GetCurrentLinePos() == scroll.GetLineCount()) {}
		else { OnVScroll(nFlag, 0, GetScrollBarCtrl(SB_VERT)); }
	}
	return CDialogEx::OnMouseWheel(nFlags, zDelta, pt);
}


BOOL WorldClockList::OnCommand(WPARAM wParam, LPARAM lParam)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	CString strCaption;
	CalculateButton* button = (CalculateButton*)GetDlgItem((int)wParam);
	
	bool bDelete = false;
	if (MessageBox(_T("선택한 항목을 삭제 하시겠습니까?"), _T("삭제"), MB_ICONQUESTION | MB_OKCANCEL) == IDOK)
	{
		int i = 0;
		for (i = 0; i < (int)clockButtonVector.size(); i++)
		{
			if (clockButtonVector.at(i) == button)
			{
				nButtonCount--;
				CalculateStatic* statics = clockStaticVector.at(i);
				clockButtonVector.erase(clockButtonVector.begin() + i);
				clockStaticVector.erase(clockStaticVector.begin() + i);
				clockDataVector.erase(clockDataVector.begin() + i);
				button->DestroyWindow();
				statics->DestroyWindow();
				delete button;
				delete statics;
				button = nullptr;
				statics = nullptr;
				bDelete = true;
				if (scroll.GetLineCount() == scroll.GetCurrentLinePos())  OnVScroll(SB_PAGEUP, 0, GetScrollBarCtrl(SB_VERT));
				if ((int)clockButtonVector.size() % 6 == 0)
				{
					scroll.LineDelete();
					scroll.ExecuteScrollPos(currentTheme);
				}
				break;
			}
		}
		if (bDelete)
		{
			for (int j = i; j < (int)clockButtonVector.size(); j++)
			{
				clockButtonVector.at(j)->SetWindowPos(NULL, nClockButtonPos_x, nClockButtonPos_y + ((2 + nClockButtonHeight) * j), 0, 0, SWP_NOSIZE);
				clockStaticVector.at(j)->SetWindowPos(NULL, nClockButtonPos_x + 100, nClockButtonPos_y + ((2 + nClockButtonHeight) * j) + 4, 0, 0, SWP_NOSIZE);
			}
			// xml 업데이트 함수
			SaveClockXml();

			return TRUE;
		}
	}


	return CDialogEx::OnCommand(wParam, lParam);
}

void WorldClockList::SaveClockXml()
{
	CMarkup markUp;
	CString szRoot = _T("");
	CreateConfigClockFile(szRoot);
	CString strFullPath = szRoot + _T("\\WorldClock.conf");

	markUp.AddElem(_T("Clock"));
	markUp.IntoElem();
	for (int i = 0; i < clockButtonVector.size(); i++)
	{
		CalculateButton* saveButton = clockButtonVector.at(i);
		CString strButtonText, strWorldName, strCityName, strGMPValue;
		saveButton->GetWindowTextW(strButtonText);
		strButtonText.Replace(_T("\r\n"), _T("-"));
		strGMPValue.Format(_T("%.1f"), worldclock->GetSearchInstance()->GetGMPCalcValue(worldclock->GetSearchInstance()->GetWorldClockData(strButtonText)));
		AfxExtractSubString(strWorldName, strButtonText, 0, '-');
		AfxExtractSubString(strCityName, strButtonText, 1, '-');

		markUp.AddElem(_T("data"));
		markUp.AddAttrib(_T("error"), strGMPValue);
		markUp.AddAttrib(_T("world"), strWorldName);
		markUp.AddAttrib(_T("city"), strCityName);
	}

	SaveXml(&markUp, strFullPath);
}