// WorldSearchList.cpp: 구현 파일
//

#include "pch.h"
#include "BOKOTools.h"
#include "WorldSearchList.h"
#include "AnalogWatch.h"
//#include "WorldClock.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// WorldSearchList 대화 상자

IMPLEMENT_DYNAMIC(WorldSearchList, CDialogEx)

WorldSearchList::WorldSearchList(CRect buttonPosRect, ThemeData* currentTheme, CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_SEARCH_LIST, pParent)
{
	this->buttonRect = buttonPosRect;
	this->currentTheme = currentTheme;
	this->pParent = pParent;
	nWorldButtonID = 55000;
	nSearchButtonPos_x = 2;
	nSearchButtonPos_y = 2;
	nSearchButtonWidth = buttonPosRect.Width() - 4;
	nSearchButtonHeight = (buttonPosRect.Height()) / 3 - 1;
}

WorldSearchList::~WorldSearchList()
{
	DeleteButtonVector();
}

void WorldSearchList::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(WorldSearchList, CDialogEx)
	ON_WM_CTLCOLOR()
	ON_WM_PAINT()
	ON_WM_VSCROLL()
	ON_WM_MOUSEWHEEL()
END_MESSAGE_MAP()


// WorldSearchList 메시지 처리기


BOOL WorldSearchList::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	LoadWorldClockList();

	nBrightness = GetBrightness(GetRValue(currentTheme->GetFunctionSubColor()), GetGValue(currentTheme->GetFunctionSubColor()), GetBValue(currentTheme->GetFunctionSubColor()));

	if (nBrightness > 120)
		bkBorderColor = RGB(0, 0, 0);
	else
		bkBorderColor = RGB(255, 255, 255);

	this->SetBackgroundColor(currentTheme->GetFunctionSubColor());

	//worldclock = (WorldClock*)pParent;
	analogwatch = (AnalogWatch*)pParent;

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void WorldSearchList::LoadWorldClockList()
{
	worldVector.push_back(GetGreenWichWorldClockData(GREECE_ATHENS));
	worldVector.push_back(GetGreenWichWorldClockData(REPUBLICOFSOUTHAFRICA_PRETORIA));
	worldVector.push_back(GetGreenWichWorldClockData(NETHERLANDS_AMSTERDAM));
	worldVector.push_back(GetGreenWichWorldClockData(NORWAY_OSLO));
	worldVector.push_back(GetGreenWichWorldClockData(NEWZEALAND_WELLINGTON));
	worldVector.push_back(GetGreenWichWorldClockData(TAIWAN_TAIPEI));
	worldVector.push_back(GetGreenWichWorldClockData(SOUTHKOREA_SEOUL));
	worldVector.push_back(GetGreenWichWorldClockData(DENMARK_COPENHAGEN));
	worldVector.push_back(GetGreenWichWorldClockData(GERMANY_BERLIN));
	worldVector.push_back(GetGreenWichWorldClockData(GERMANY_MUNICH));
	worldVector.push_back(GetGreenWichWorldClockData(LATVIA_RIGA));
	worldVector.push_back(GetGreenWichWorldClockData(RUSIA_MOSKVA));
	worldVector.push_back(GetGreenWichWorldClockData(LUXEMBOURG_LUXEMBOURG));
	worldVector.push_back(GetGreenWichWorldClockData(LITHUANIA_VILNIUS));
	worldVector.push_back(GetGreenWichWorldClockData(MEXICO_MEXICOCITY));
	worldVector.push_back(GetGreenWichWorldClockData(USA_ATLANTA));
	worldVector.push_back(GetGreenWichWorldClockData(USA_NEWYORK));
	worldVector.push_back(GetGreenWichWorldClockData(USA_LASVEGAS));
	worldVector.push_back(GetGreenWichWorldClockData(USA_LOSANGELES));
	worldVector.push_back(GetGreenWichWorldClockData(USA_MIAMI));
	worldVector.push_back(GetGreenWichWorldClockData(USA_VIRGINIA));
	worldVector.push_back(GetGreenWichWorldClockData(USA_SANFRANCISCO));
	worldVector.push_back(GetGreenWichWorldClockData(USA_SEATTLE));
	worldVector.push_back(GetGreenWichWorldClockData(USA_WASHINGTONDC));
	worldVector.push_back(GetGreenWichWorldClockData(NORTHKOREA_PYONGYANG));
	worldVector.push_back(GetGreenWichWorldClockData(BRAZIL_BRASILIA));
	worldVector.push_back(GetGreenWichWorldClockData(BRAZIL_SAOPAULO));
	worldVector.push_back(GetGreenWichWorldClockData(BELGIUM_BRUSSELS));
	worldVector.push_back(GetGreenWichWorldClockData(SWEDEN_STOCKHOLM));
	worldVector.push_back(GetGreenWichWorldClockData(SWISS_BERN));
	worldVector.push_back(GetGreenWichWorldClockData(SWISS_ZURICH));
	worldVector.push_back(GetGreenWichWorldClockData(SPAIN_BARCELONA));
	worldVector.push_back(GetGreenWichWorldClockData(SPAIN_MADRID));
	worldVector.push_back(GetGreenWichWorldClockData(SLOVAKIA_BRATISLAVA));
	worldVector.push_back(GetGreenWichWorldClockData(SLOVENIA_LJUBLJANA));
	worldVector.push_back(GetGreenWichWorldClockData(UAE_DUBAI));
	worldVector.push_back(GetGreenWichWorldClockData(ISLAND_REYKJAVIK));
	worldVector.push_back(GetGreenWichWorldClockData(IRELAND_DUBLIN));
	worldVector.push_back(GetGreenWichWorldClockData(ENGLAND_GREENWICH));
	worldVector.push_back(GetGreenWichWorldClockData(ENGLAND_LONDON));
	worldVector.push_back(GetGreenWichWorldClockData(ENGLAND_LIVERPOOL));
	worldVector.push_back(GetGreenWichWorldClockData(ENGLAND_MANCHESTER));
	worldVector.push_back(GetGreenWichWorldClockData(ENGLAND_OXFORD));
	worldVector.push_back(GetGreenWichWorldClockData(ESTONIA_TALLINN));
	worldVector.push_back(GetGreenWichWorldClockData(AUSTRIA_WIEN));
	worldVector.push_back(GetGreenWichWorldClockData(ISRAEL_JERUSALEM));
	worldVector.push_back(GetGreenWichWorldClockData(ITALIA_NEAPOLITAN));
	worldVector.push_back(GetGreenWichWorldClockData(ITALY_ROME));
	worldVector.push_back(GetGreenWichWorldClockData(ITALIA_MILAN));
	worldVector.push_back(GetGreenWichWorldClockData(ITALIA_VENETIAN));
	worldVector.push_back(GetGreenWichWorldClockData(ITALIA_PISA));
	worldVector.push_back(GetGreenWichWorldClockData(INDIA_NEWDELHI));
	worldVector.push_back(GetGreenWichWorldClockData(INDONESIA_JAKARTA));
	worldVector.push_back(GetGreenWichWorldClockData(JAPAN_TOKYO));
	worldVector.push_back(GetGreenWichWorldClockData(CHINA_BEIJING));
	worldVector.push_back(GetGreenWichWorldClockData(CZECH_PRAGUE));
	worldVector.push_back(GetGreenWichWorldClockData(CHILE_SANTIAGO));
	worldVector.push_back(GetGreenWichWorldClockData(CANADA_VANCOUVER));
	worldVector.push_back(GetGreenWichWorldClockData(CANADA_OTTAWA));
	worldVector.push_back(GetGreenWichWorldClockData(CANADA_TORONTO));
	worldVector.push_back(GetGreenWichWorldClockData(COSTARICA_SANJOSE));
	worldVector.push_back(GetGreenWichWorldClockData(COLUMBIA_SANTAFEDEBOGOTA));
	worldVector.push_back(GetGreenWichWorldClockData(TURKEY_ANKARA));
	worldVector.push_back(GetGreenWichWorldClockData(PORTUGAL_LISBON));
	worldVector.push_back(GetGreenWichWorldClockData(POLAND_WARSZAWA));
	worldVector.push_back(GetGreenWichWorldClockData(FRANCE_MARSEILLE));
	worldVector.push_back(GetGreenWichWorldClockData(FRANCE_PARIS));
	worldVector.push_back(GetGreenWichWorldClockData(FINLAND_HELSINKI));
	worldVector.push_back(GetGreenWichWorldClockData(PHILIPPINES_MANILA));
	worldVector.push_back(GetGreenWichWorldClockData(HUNGARY_BUDAPEST));
	worldVector.push_back(GetGreenWichWorldClockData(AUSTRALIA_SYDNEY));
	worldVector.push_back(GetGreenWichWorldClockData(AUSTRALIA_CANBERRA));
}

bool WorldSearchList::SearchClockListFromInputText(CString strInputText)
{
	bool bFind = false;

	DeleteButtonVector();
	scroll.Destroy();

	scroll.Create(this);
	CustomScroll::CustomScrollInfo csi;
	csi.cst = CustomScroll::CUSTOM_SCROLL_TYPE_DEFAULT;
	csi.nAllPageSize = 0;
	csi.nKindOfScrollFlags = SB_VERT;
	csi.nOnePageSize = nSearchButtonHeight + 2;
	csi.nScrollPos = 0;
	csi.nWheelValue = nSearchButtonHeight + 2;
	csi.bLikeButtonEvent = false;
	scroll.Initialize(csi);

	for (int i = 0; i < (int)worldVector.size(); i++)
	{
		CString strFullName = worldVector.at(i).strWorldName;
		CString strWorldName;
		CString strCityName;

		int nFind = strFullName.Find(strInputText);
		if (nFind != -1)
		{
			AfxExtractSubString(strWorldName, strFullName, 0, '-');
			AfxExtractSubString(strCityName, strFullName, 1, '-');
			int nWorldNameFind = strWorldName.Find(strInputText);
			int nCityNameFind = strCityName.Find(strInputText);
			if (nWorldNameFind != -1) { bFind = true; }
			if (nCityNameFind != -1) { bFind = true; }

			if (nWorldNameFind != -1)
			{
				CreateWorldDataButton(worldVector.at(i));
			}
			else if (nCityNameFind != -1)
			{
				CreateCityDataButton(worldVector.at(i));
			}
		}
	}
	SetApsorptionToButtonPos();

	for (int i = 0; i < ((int)allDataButtonVector.size() - 1); i++)
	{
		scroll.LineEnd();
	}
	scroll.ExecuteScrollPos(currentTheme);
	return bFind;
}

void WorldSearchList::SetApsorptionToButtonPos()
{
	for (int i = 0; i < (int)worldDataButtonVector.size(); i++) { allDataButtonVector.push_back(worldDataButtonVector.at(i)); }
	for (int i = 0; i < (int)cityDataButtonVector.size(); i++) { allDataButtonVector.push_back(cityDataButtonVector.at(i)); }
	for (int i = 0; i < allDataButtonVector.size(); i++)
	{
		CalculateButton* newSearchButton = allDataButtonVector.at(i);
		newSearchButton->MoveWindow(nSearchButtonPos_x, nSearchButtonPos_y + ((2 + nSearchButtonHeight) * i), nSearchButtonWidth, nSearchButtonHeight);
	}
}

void WorldSearchList::CreateCityDataButton(WorldClockData wcd)
{
	CalculateButton* newSearchButton = new CalculateButton;
	CString strCityName = wcd.strWorldName;
	strCityName.Replace(_T("-"), _T("\r\n"));
	newSearchButton->Create(strCityName, BS_PUSHBUTTON, CRect(0, 0, 0, 0), this, nWorldButtonID++);
	newSearchButton->ShowWindow(SW_SHOW);
	newSearchButton->Initialize(currentTheme->GetButtonColor(), CMFCButton::FlatStyle::BUTTONSTYLE_NOBORDERS, _T("가비아 솔미체"), 20);
	newSearchButton->SetAlignment(CMFCButton::AlignStyle::ALIGN_LEFT);
	newSearchButton->Invalidate();
	cityDataButtonVector.push_back(newSearchButton);
}

void WorldSearchList::CreateWorldDataButton(WorldClockData wcd)
{
	CalculateButton* newSearchButton = new CalculateButton;
	CString strWorldName = wcd.strWorldName;
	strWorldName.Replace(_T("-"), _T("\r\n"));
	newSearchButton->Create(strWorldName, BS_PUSHBUTTON, CRect(0, 0, 0, 0), this, nWorldButtonID++);
	newSearchButton->ShowWindow(SW_SHOW);
	newSearchButton->Initialize(currentTheme->GetButtonColor(), CMFCButton::FlatStyle::BUTTONSTYLE_NOBORDERS, _T("가비아 솔미체"), 20);
	newSearchButton->SetAlignment(CMFCButton::AlignStyle::ALIGN_LEFT);
	newSearchButton->Invalidate();
	worldDataButtonVector.push_back(newSearchButton);
}

void WorldSearchList::DeleteButtonVector()
{
	for (int i = 0; i < (int)allDataButtonVector.size(); i++)
	{
		CalculateButton* deleteButton = allDataButtonVector.at(i);
		deleteButton->DestroyWindow();
		delete deleteButton;
		deleteButton = nullptr;
	}
	allDataButtonVector.clear();
	cityDataButtonVector.clear();
	worldDataButtonVector.clear();
	nWorldButtonID = 55000;
}

void WorldSearchList::OnOK()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	//CDialogEx::OnOK();
}


BOOL WorldSearchList::PreTranslateMessage(MSG* pMsg)
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


HBRUSH WorldSearchList::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  여기서 DC의 특성을 변경합니다.

	// TODO:  기본값이 적당하지 않으면 다른 브러시를 반환합니다.
	return hbr;
}


void WorldSearchList::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 여기에 메시지 처리기 코드를 추가합니다.
					   // 그리기 메시지에 대해서는 CDialogEx::OnPaint()을(를) 호출하지 마십시오.

	CRect thisRect;
	GetWindowRect(thisRect);
	dc.Draw3dRect(0, 0, thisRect.Width(), thisRect.Height(), bkBorderColor, bkBorderColor);
}


void WorldSearchList::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	scroll.OperateScroll(nSBCode, nPos);
	CDialogEx::OnVScroll(nSBCode, nPos, pScrollBar);
	Invalidate();
}


BOOL WorldSearchList::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
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


BOOL WorldSearchList::OnCommand(WPARAM wParam, LPARAM lParam)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	CString strCaption, strWorldName, strCityName;
	CalculateButton* button = (CalculateButton*)GetDlgItem((int)wParam);
	button->GetWindowTextW(strCaption);
	strCaption.Replace(_T("\r\n"), _T("-"));
	//AfxExtractSubString(strWorldName, strCaption, 0, '\r\n');
	//AfxExtractSubString(strCityName, strCaption, 1, '\r\n');

	analogwatch->m_edit_analog_search.SetWindowTextW(strCaption);
	this->ShowWindow(SW_HIDE);
	return TRUE;
	/*if (MessageBox(_T("선택한 국가를 추가 하시겠습니까?"), _T("추가"), MB_ICONQUESTION | MB_OKCANCEL) == IDOK)
	{
		if (worldclock->GetClockInstance()->AddClock(GetGMPCalcValue(GetWorldClockData(strCaption)), strWorldName, strCityName))
		{
			this->ShowWindow(SW_HIDE);
			worldclock->GetClockInstance()->SaveClockXml();
		}
	}*/

	//return CDialogEx::OnCommand(wParam, lParam);
}
