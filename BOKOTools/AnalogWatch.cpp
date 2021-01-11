// AnalogWatch.cpp: 구현 파일
//

#include "pch.h"
#include "BOKOTools.h"
#include "AnalogWatch.h"
#include "afxdialogex.h"


// AnalogWatch 대화 상자

IMPLEMENT_DYNAMIC(AnalogWatch, CDialogEx)

AnalogWatch::AnalogWatch(ThemeData* currentTheme, CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_ANALOG_WATCh, pParent)
{
	this->pParent = pParent;
	this->currentTheme = currentTheme;
	bMainClock = false;
}

AnalogWatch::~AnalogWatch()
{
	if (worldsearchlist)
	{
		delete worldsearchlist;
		worldsearchlist = nullptr;
	}

	if (clockData)
	{
		delete clockData;
		clockData = nullptr;
	}
}

void AnalogWatch::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_ANALOG_DATE, m_stt_analog_date);
	DDX_Control(pDX, IDC_BUTTON_ANALOG_SUBMIT, m_btn_analog_submit);
	DDX_Control(pDX, IDC_EDIT_ANALOG_SEARCH, m_edit_analog_search);
}


BEGIN_MESSAGE_MAP(AnalogWatch, CDialogEx)
	ON_WM_PAINT()
	ON_WM_CTLCOLOR()
	ON_EN_CHANGE(IDC_EDIT_ANALOG_SEARCH, &AnalogWatch::OnEnChangeEditAnalogSearch)
	ON_BN_CLICKED(IDC_BUTTON_ANALOG_SUBMIT, &AnalogWatch::OnBnClickedButtonAnalogSubmit)
END_MESSAGE_MAP()


// AnalogWatch 메시지 처리기


BOOL AnalogWatch::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	nBrightness = GetBrightness(GetRValue(currentTheme->GetFunctionSubColor()), GetGValue(currentTheme->GetFunctionSubColor()), GetBValue(currentTheme->GetFunctionSubColor()));

	if (nBrightness > 120)
		bkBorderColor = RGB(0, 0, 0);
	else
		bkBorderColor = RGB(255, 255, 255);

	m_backBrush.CreateSolidBrush(currentTheme->GetFunctionSubColor());
	this->SetBackgroundColor(currentTheme->GetFunctionBkColor());
	

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void AnalogWatch::Initialize()
{
	this->GetWindowRect(thisRect);
	watchRect = { 0, 40, thisRect.Width() - 5, 40 + thisRect.Width() - 5 };

	m_stt_analog_date.Initialize(40, _T("godoMaum"));
	m_stt_analog_date.SetWindowTextW(_T("테스트"));
	m_stt_analog_date.MoveWindow(0, 0, thisRect.Width(), 30);

	m_edit_analog_search.Initialize(20, _T("godoMaum"));
	m_edit_analog_search.MoveWindow(0, 40 + thisRect.Width() - 5 + 10, thisRect.Width() - 5 - 40, 30);
	m_btn_analog_submit.Initialize(currentTheme->GetButtonColor(), CMFCButton::FlatStyle::BUTTONSTYLE_NOBORDERS, _T("godoMaum"), 20);
	m_btn_analog_submit.SetTextColor(currentTheme->GetTextColor());
	m_btn_analog_submit.MoveWindow(thisRect.Width() - 5 - 40 + 10, 40 + thisRect.Width() - 5 + 10, 30, 30);

	//CRect dynamicSearchRect = { 0, 40 + thisRect.Width() - 5 + 10 + 30 + 10, thisRect.Width() - 5 - 40, 40 + thisRect.Width() - 5 + 10 + 30 + 10 + 135 };
	CRect dynamicSearchRect = { 0, 40 + thisRect.Width() - 5 - 135 + 10, thisRect.Width() - 5 - 40, 40 + thisRect.Width() - 5 + 10 };
	worldsearchlist = new WorldSearchList(dynamicSearchRect, currentTheme, this);
	worldsearchlist->Create(IDD_DIALOG_SEARCH_LIST, this);
	worldsearchlist->MoveWindow(dynamicSearchRect);
	worldsearchlist->ShowWindow(SW_HIDE);

}

void AnalogWatch::InvalidClockRect()
{
	InvalidateRect(watchRect);
}


void AnalogWatch::OnOK()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	//CDialogEx::OnOK();
}


BOOL AnalogWatch::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	if (pMsg->message == WM_LBUTTONUP)
	{
		if (pMsg->hwnd == this->m_hWnd)
		{
			worldsearchlist->ShowWindow(SW_HIDE);
		}
		else if (pMsg->hwnd == m_edit_analog_search.m_hWnd)
		{
			CString strSearchText;
			m_edit_analog_search.GetWindowTextW(strSearchText);

			if (worldsearchlist->SearchClockListFromInputText(strSearchText))
			{
				worldsearchlist->ShowWindow(SW_SHOW);
			}
			m_edit_analog_search.SetFocus();
		}
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}


void AnalogWatch::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 여기에 메시지 처리기 코드를 추가합니다.
					   // 그리기 메시지에 대해서는 CDialogEx::OnPaint()을(를) 호출하지 마십시오.

	CPen ellipsePen(PS_SOLID, 2, currentTheme->GetRectBorderColor());
	CPen *pOldPen = dc.SelectObject(&ellipsePen);

	dc.Ellipse(&watchRect);
	const CPoint cpt = watchRect.CenterPoint();
	double radius = watchRect.Width() / 2;

	CPen markpen(PS_SOLID, (int)(watchRect.Width() / WATCH_MARKWIDTH), currentTheme->GetRectBorderColor());
	pOldPen = dc.SelectObject(&markpen);

	CFont font, *pOldFont;
	font.CreatePointFont(watchRect.Width() / WATCH_HOURTEXT, _T("godoMaum"));
	pOldFont = dc.SelectObject(&font);


	int minmark = 0;

	for (int i = 0; i < 360; i += 6)
	{
		// 원의 외접선 좌표 구하기
		CPoint dpt = GetRotatedPos(cpt, radius, (double)i);
		// 원의 외접선 좌표부터 안쪽 분 마크 좌표 구하기
		CPoint mpt = GetRotatedPos(CPoint(cpt.x + dpt.x, cpt.y + dpt.y), 0 - radius / WATCH_MINMARK, (double)i);

		// 5분 단위로 굵게 분 마킹
		if (minmark % 5 == 0)
		{
			dc.SelectObject(&markpen);

			CString str;
			if (minmark == 0)
				str = _T("12");
			else
				str.Format(_T("%d"), minmark / 5);

			// 원의 분마크 좌표에서 시간 글자 좌표 구하기			
			CPoint tpt = GetRotatedPos(CPoint(cpt.x + dpt.x + mpt.x, cpt.y + dpt.y + mpt.y), 0 - radius / WATCH_MINMARK, (double)i);
			tpt.x = cpt.x + dpt.x + mpt.x + tpt.x;
			tpt.y = cpt.y - dpt.y - mpt.y - tpt.y;

			// 폰트 크기 구하기
			CSize size = dc.GetTextExtent(str);

			CRect textrect(tpt.x - size.cx / 2, tpt.y - size.cy / 2, tpt.x + size.cx / 2, tpt.y + size.cy / 2);
			dc.SetTextColor(currentTheme->GetRectBorderColor());
			dc.DrawText(str, textrect, DT_CENTER);
		}
		else
			dc.SelectObject(&ellipsePen);

		// 분 마크 그리기
		dc.MoveTo(cpt.x + dpt.x, cpt.y - dpt.y);
		dc.LineTo(cpt.x + dpt.x + mpt.x, cpt.y - dpt.y - mpt.y);

		minmark++;
	}

	// 시계 로고
	CFont logofont;
	logofont.CreatePointFont(watchRect.Width() / WATCH_LOGOTEXT, _T("godoMaum"));
	dc.SelectObject(&logofont);
	CRect logorect(watchRect);
	logorect.OffsetRect(0, (int)((double)logorect.Height() - (double)logorect.Height() / WATCH_LOGODOWN));
	CString str;
	str.Format(_T("Ocean Coding School\r\n%s"), _T("!!"));

	dc.DrawText(str, &logorect, DT_CENTER);


	//DrawYMD(dc);
	DrawTime(dc);


	// 사용한 GDI Object 반환, 삭제	
	dc.SelectObject(pOldPen);
	dc.SelectObject(pOldFont);
	ellipsePen.DeleteObject();
	markpen.DeleteObject();
	font.DeleteObject();
}


void AnalogWatch::DrawTime(CDC& memDC)
{
	CPoint cpt = watchRect.CenterPoint();
	int size = watchRect.Width() / WATCH_CENTERSIZE;

	// 중심 점 그리기
	memDC.Ellipse(cpt.x - size, cpt.y - size, cpt.x + size, cpt.y + size);


	//CTime curTime = CTime::GetCurrentTime();
	CTime curTime = CTime::GetCurrentTime();

	double radius = watchRect.Width() / 2;

	// 초,분,시침 좌표 얻기
	CPoint secpt = GetClockHandPos(TIME_SEC, curTime, cpt, radius*WATCH_SECLENGTH);
	CPoint minpt = GetClockHandPos(TIME_MIN, curTime, cpt, radius*WATCH_MINLENGTH);
	CPoint hourpt = GetClockHandPos(TIME_HOUR, curTime, cpt, radius*WATCH_HOURLENGTH);

	// 초,분,시침 그리기
	CPen hourpen(PS_SOLID, (int)(watchRect.Width() / WATCH_HOURWIDTH), RGB(0, 0, 0));
	CPen* pOldPen = memDC.SelectObject(&hourpen);
	memDC.MoveTo(cpt.x, cpt.y);
	memDC.LineTo(cpt.x + hourpt.x, cpt.y - hourpt.y);

	CPen minpen(PS_SOLID, (int)(watchRect.Width() / WATCH_MINWIDTH), RGB(0, 0, 0));
	memDC.SelectObject(&minpen);
	memDC.MoveTo(cpt.x, cpt.y);
	memDC.LineTo(cpt.x + minpt.x, cpt.y - minpt.y);

	CPen secpen(PS_SOLID, int(watchRect.Width() / WATCH_SECWIDTH), RGB(0, 0, 0));
	memDC.SelectObject(&secpen);
	memDC.MoveTo(cpt.x, cpt.y);
	memDC.LineTo(cpt.x + secpt.x, cpt.y - secpt.y);

	memDC.SelectObject(pOldPen);
	hourpen.DeleteObject();
	minpen.DeleteObject();
	secpen.DeleteObject();
}


CPoint AnalogWatch::GetClockHandPos(AnalogWatch::TIME_ TIME, const CTime& time, const CPoint& anchorPt, double radius)
{
	double deg = 0;
	double sec, min, hour;
	hour = time.GetHour();
	min = time.GetMinute();
	sec = time.GetSecond();

	switch (TIME)
	{
	case TIME_HOUR:
		deg = (((int)hour % (int)12.0) + (min / 60.0)) * 30.0;
		break;
	case TIME_MIN:
		deg = (min + sec / 60.0) * 6.0;
		break;
	case TIME_SEC:
		deg = sec * 6.0;
		break;
	}

	return GetRotatedPos(anchorPt, radius, deg);
}

CPoint AnalogWatch::GetRotatedPos(const CPoint& anchorPt, double radius, double deg) const
{
	double radian = deg * PI / 180.0;

	double dx = sin(radian)*radius;
	double dy = cos(radian)*radius;

	CPoint newPt((int)dx, (int)dy);

	return newPt;
}


HBRUSH AnalogWatch::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  여기서 DC의 특성을 변경합니다.
	if (nCtlColor == CTLCOLOR_STATIC)
	{
		if (pWnd->GetDlgCtrlID() == m_stt_analog_date.GetDlgCtrlID())
		{
			pDC->SetTextColor(currentTheme->GetTextColor());
		}
	}
	else if (nCtlColor == CTLCOLOR_EDIT)
	{
		if (pWnd->GetDlgCtrlID() == m_edit_analog_search.GetDlgCtrlID())
		{
			pDC->SetBkColor(currentTheme->GetFunctionSubColor());
			pDC->SetTextColor(currentTheme->GetFunctionTextColor());
			hbr = (HBRUSH)m_backBrush;
		}
	}

	// TODO:  기본값이 적당하지 않으면 다른 브러시를 반환합니다.
	return hbr;
}


void AnalogWatch::OnEnChangeEditAnalogSearch()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString strSearchText;
	m_edit_analog_search.GetWindowTextW(strSearchText);
	if (strSearchText.IsEmpty())
	{
		worldsearchlist->ShowWindow(SW_HIDE);
		return;
	}

	if (worldsearchlist->SearchClockListFromInputText(strSearchText))
	{
		worldsearchlist->ShowWindow(SW_SHOW);
	}
	m_edit_analog_search.SetFocus();
}


void AnalogWatch::OnBnClickedButtonAnalogSubmit()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (MessageBox(_T("선택한 국가로 등록 하시겠습니까?"), _T("추가"), MB_ICONQUESTION | MB_OKCANCEL) == IDOK)
	{
		//
		CString strSuccessName;
		CString strWorldName, strCityName;
		AfxExtractSubString(strWorldName, strSuccessName, 0, '-');
		AfxExtractSubString(strCityName, strSuccessName, 1, '-');

		m_edit_analog_search.GetWindowTextW(strSuccessName);
		m_stt_analog_date.SetWindowTextW(strSuccessName);
		double dGMPValue = worldsearchlist->GetGMPCalcValue(worldsearchlist->GetWorldClockData(strSuccessName));
		if (bMainClock) clockData->dErrorMainGMPValue = dGMPValue;
		clockData->dErrorSubGMPValue = dGMPValue;
		clockData->strWorldName = strWorldName;
		clockData->strCityName = strCityName;
	}
}
