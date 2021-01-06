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
	nClockButtonWidth = 240;
	nClockButtonHeight = 37;
	nButtonCount = 0;
	nDetectHeight = 0;
}

WorldClockList::~WorldClockList()
{
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

	nBrightness = GetBrightness(GetRValue(currentTheme->GetFunctionSubColor()), GetGValue(currentTheme->GetFunctionSubColor()), GetBValue(currentTheme->GetFunctionSubColor()));

	if (nBrightness > 120)
		bkBorderColor = RGB(0, 0, 0);
	else
		bkBorderColor = RGB(255, 255, 255);

	this->SetBackgroundColor(currentTheme->GetFunctionSubColor());

	worldclock = (WorldClock*)pParent;

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
	AddClock(8, _T("대한민국 - 서울"));
	AddClock(8, _T("대한민국 - 서울"));
	AddClock(8, _T("대한민국 - 서울"));
	AddClock(8, _T("대한민국 - 서울"));
	AddClock(8, _T("대한민국 - 서울"));
	AddClock(8, _T("대한민국 - 서울"));

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
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

void WorldClockList::AddClock(double dErrorTimeValue, CString strWorldClockName)
{
	// 여기에 시간값 넣는 함수 추가
	CalculateButton* newSearchButton = new CalculateButton;
	newSearchButton->Create(strWorldClockName, BS_PUSHBUTTON, CRect(0, 0, 0, 0), this, nWorldButtonID++);
	nDetectHeight = nClockButtonPos_y + ((2 + nClockButtonHeight) * (nButtonCount - (6 * (scroll.GetCurrentLinePos() - 1))));
	newSearchButton->MoveWindow(nClockButtonPos_x, nDetectHeight, nClockButtonWidth, nClockButtonHeight);
	newSearchButton->ShowWindow(SW_SHOW);
	newSearchButton->Initialize(currentTheme->GetButtonColor(), CMFCButton::FlatStyle::BUTTONSTYLE_NOBORDERS);
	newSearchButton->SetAlignment(CMFCButton::AlignStyle::ALIGN_LEFT);
	newSearchButton->Invalidate();
	clockButtonVector.push_back(newSearchButton);
	nButtonCount++;
	SizeToScrollDetect();
}

void WorldClockList::SizeToScrollDetect()
{

	//scroll.Destroy();

	//scroll.Create(this);
	//CustomScroll::CustomScrollInfo csi;
	//csi.cst = CustomScroll::CUSTOM_SCROLL_TYPE_DEFAULT;
	//csi.nAllPageSize = 0;
	//csi.nKindOfScrollFlags = SB_VERT;
	//csi.nOnePageSize = 236;
	//csi.nScrollPos = 0;
	//csi.nWheelValue = 236;
	//scroll.Initialize(csi);
	if (((int)clockButtonVector.size() - 1) % 6 == 0)
	{
		scroll.LineEnd();
	}
/*
	for (int i = 0; i < (int)clockButtonVector.size() + 1 - 6; i++)
	{
		scroll.LineEnd();
	}*/
	/*scroll.LineEnd();
	scroll.LoadScroll(scroll.csi.nOnePageSize);*/
	scroll.ExecuteScrollPos(currentTheme);
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
