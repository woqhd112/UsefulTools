// AnalogWatch.cpp: 구현 파일
//

#include "pch.h"
#include "BOKOTools.h"
#include "AnalogWatch.h"
#include "WorldClock.h"
#include "afxdialogex.h"
#include <math.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// AnalogWatch 대화 상자

IMPLEMENT_DYNAMIC(AnalogWatch, CDialogEx)

AnalogWatch::AnalogWatch(ThemeData* currentTheme, CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_ANALOG_WATCH, pParent)
{
	this->pParent = pParent;
	this->currentTheme = currentTheme;
	nClockIdx = 0;
	m_bInitSuccess = false;
	bTimeSync = false;
	bInitWorldSearchList = false;
	bClockDataInit = false;
}

AnalogWatch::~AnalogWatch()
{
	if (bInitWorldSearchList)
	{
		delete worldsearchlist;
		worldsearchlist = nullptr;
	}
}

void AnalogWatch::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_ANALOG_DATE, m_stt_analog_date);
	DDX_Control(pDX, IDC_BUTTON_ANALOG_SUBMIT, m_btn_analog_submit);
	DDX_Control(pDX, IDC_EDIT_ANALOG_SEARCH, m_edit_analog_search);
	DDX_Control(pDX, IDC_STATIC_ANALOG_WORLDNAME, m_stt_analog_worldname);
	DDX_Control(pDX, IDC_EDIT_DIGITAL_CLOCK, m_edit_digital_clock);
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
	m_digitalBrush.CreateSolidBrush(currentTheme->GetFunctionBkColor());
	this->SetBackgroundColor(currentTheme->GetFunctionBkColor());
	m_edit_digital_clock.LimitText(8);
	
	worldclock = (WorldClock*)pParent;

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void AnalogWatch::Initialize(ClockData* clockData)
{
	this->GetWindowRect(thisRect);
	watchRect = { 5, 30 + 40, thisRect.Width() - 5, 30 + 40 + thisRect.Width() - 5 - 5 };
	watchBorderRect = { 0, 30 + 40 - 5, thisRect.Width(), 30 + 40 + thisRect.Width() - 5 };
	cpt = watchRect.CenterPoint();

	m_stt_analog_worldname.Initialize(25, _T("godoMaum"));
	m_stt_analog_worldname.MoveWindow(0, 0, thisRect.Width(), 30);
	m_stt_analog_date.Initialize(25, _T("godoMaum"));
	m_stt_analog_date.MoveWindow(0, 30, thisRect.Width(), 30);

	m_edit_analog_search.Initialize(20, _T("godoMaum"));
	m_edit_analog_search.MoveWindow(0, 30 + 40 + thisRect.Width() - 5 + 10, thisRect.Width() - 5 - 30, 30);
	int nDigitalFontSize = 0;
	int nDigitalFontHeight = 0;
	if (nClockIdx > 0)
	{
		nDigitalFontSize = 15;
		nDigitalFontHeight = 15;
	}
	else
	{
		nDigitalFontSize = 20;
		nDigitalFontHeight = 20;
	}
	m_edit_digital_clock.Initialize(nDigitalFontSize, _T("DS-Digital"));
	m_edit_digital_clock.MoveWindow((thisRect.Width() - 5) / 2 / 2, 30 + 40 + (thisRect.Width() - 5) / 2 + (thisRect.Width() - 5) / 2 / 2 / 2, (thisRect.Width() - 5) / 2, nDigitalFontHeight);

	m_btn_analog_submit.Initialize(currentTheme->GetButtonColor(), CMFCButton::FlatStyle::BUTTONSTYLE_NOBORDERS, _T("godoMaum"), 20);
	m_btn_analog_submit.SetTextColor(currentTheme->GetTextColor());
	m_btn_analog_submit.MoveWindow(thisRect.Width() - 5 - 35 + 10, 30 + 40 + thisRect.Width() - 5 + 10, 30, 30);

	CRect dynamicSearchRect = { 0, 30 + 40 + thisRect.Width() - 5 - 135 + 10, thisRect.Width() - 5 - 30, 30 + 40 + thisRect.Width() - 5 + 10 };
	worldsearchlist = new WorldSearchList(dynamicSearchRect, currentTheme, this);
	worldsearchlist->Create(IDD_DIALOG_SEARCH_LIST, this);
	worldsearchlist->MoveWindow(dynamicSearchRect);
	worldsearchlist->ShowWindow(SW_HIDE);
	bInitWorldSearchList = true;

	this->clockData = clockData;
	m_stt_analog_worldname.SetWindowTextW(clockData->strWorldCityName);
	m_bInitSuccess = true;
	bClockDataInit = true;
}

void AnalogWatch::SetClockPriority(int nPriority)
{
	nClockIdx = nPriority;

	if (nClockIdx != 0) m_edit_digital_clock.EnableWindow(FALSE);
}

void AnalogWatch::InvalidClockRect(ClockData* clockData)
{
	this->clockData = clockData;
	if (!worldclock->bWillModify)
	{
		InvalidateRect(watchBorderRect);
	}
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
			if (worldclock->bWillModify)
			{
				SetErrorTime();
				for (int i = 0; i < (int)worldclock->analogWatchVector.size(); i++)
				{
					worldclock->analogWatchVector.at(i)->bTimeSync = true;
				}
			}

			worldclock->bWillModify = false;
			for (int i = 0; i < (int)worldclock->analogWatchVector.size(); i++)
			{
				worldclock->analogWatchVector.at(i)->worldsearchlist->ShowWindow(SW_HIDE);
				worldclock->analogWatchVector.at(i)->SetFocus();
				worldclock->analogWatchVector.at(i)->m_edit_digital_clock.HideCaret();
			}
		}
		else if (pMsg->hwnd == m_edit_analog_search.m_hWnd)
		{
			if (worldclock->bWillModify)
			{
				SetErrorTime();
				for (int i = 0; i < (int)worldclock->analogWatchVector.size(); i++)
				{
					worldclock->analogWatchVector.at(i)->bTimeSync = true;
				}
			}
			worldclock->bWillModify = false;
			CString strText;
			m_edit_analog_search.GetWindowTextW(strText);

			if (worldsearchlist->SearchClockListFromInputText(strText))
			{
				worldsearchlist->ShowWindow(SW_SHOW);
			}
			m_edit_analog_search.SetFocus();
		}
		else if (pMsg->hwnd == m_edit_digital_clock.m_hWnd)
		{
			worldclock->bWillModify = true;
		}
	}
	else if (pMsg->message == WM_KEYDOWN)
	{
		if (pMsg->wParam == VK_NUMPAD0) pMsg->wParam = L'0';
		else if (pMsg->wParam == VK_NUMPAD1) pMsg->wParam = L'1';
		else if (pMsg->wParam == VK_NUMPAD2) pMsg->wParam = L'2';
		else if (pMsg->wParam == VK_NUMPAD3) pMsg->wParam = L'3';
		else if (pMsg->wParam == VK_NUMPAD4) pMsg->wParam = L'4';
		else if (pMsg->wParam == VK_NUMPAD5) pMsg->wParam = L'5';
		else if (pMsg->wParam == VK_NUMPAD6) pMsg->wParam = L'6';
		else if (pMsg->wParam == VK_NUMPAD7) pMsg->wParam = L'7';
		else if (pMsg->wParam == VK_NUMPAD8) pMsg->wParam = L'8';
		else if (pMsg->wParam == VK_NUMPAD9) pMsg->wParam = L'9';

		if (pMsg->hwnd == m_edit_digital_clock.m_hWnd)
		{
			CString strFullText;
			m_edit_digital_clock.GetWindowTextW(strFullText);
			if (pMsg->wParam == VK_BACK)
			{
				int nStart, nEnd;
				m_edit_digital_clock.GetSel(nStart, nEnd);
				if (nStart < nEnd) return TRUE;
				if (nEnd > 0)
				{
					if ((CString)strFullText.GetAt(nEnd - 1) != _T(":"))
					{
						strFullText.SetAt(nEnd - 1, '0');
						m_edit_digital_clock.SetWindowTextW(strFullText);
					}
					m_edit_digital_clock.SetSel(nEnd - 1, nEnd - 1);
					return TRUE;
				}
			}
			else if (pMsg->wParam == L'0' ||
					 pMsg->wParam == L'1' ||
				 	 pMsg->wParam == L'2' ||
					 pMsg->wParam == L'3' ||
					 pMsg->wParam == L'4' ||
					 pMsg->wParam == L'5' ||
					 pMsg->wParam == L'6' ||
					 pMsg->wParam == L'7' ||
					 pMsg->wParam == L'8' ||
					 pMsg->wParam == L'9' ||
					 pMsg->wParam == VK_NUMPAD0 ||
					 pMsg->wParam == VK_NUMPAD1 || 
					 pMsg->wParam == VK_NUMPAD2 || 
					 pMsg->wParam == VK_NUMPAD3 || 
					 pMsg->wParam == VK_NUMPAD4 || 
					 pMsg->wParam == VK_NUMPAD5 || 
					 pMsg->wParam == VK_NUMPAD6 || 
					 pMsg->wParam == VK_NUMPAD7 || 
					 pMsg->wParam == VK_NUMPAD8 || 
					 pMsg->wParam == VK_NUMPAD9)
			{
				int nStart, nEnd;
				m_edit_digital_clock.GetSel(nStart, nEnd);
				if (nStart < nEnd) return TRUE;
				if (nEnd == 0 && pMsg->wParam > L'2') return TRUE;
				else if (nEnd == 1 && pMsg->wParam > L'3' && (CString)strFullText.GetAt(nEnd - 1) == _T("2")) return TRUE;
				else if (nEnd == 3 && pMsg->wParam > L'5') return TRUE;
				else if (nEnd == 6 && pMsg->wParam > L'5') return TRUE;
				if (nEnd != strFullText.GetLength())
				{
					if ((CString)strFullText.GetAt(nEnd) != _T(":"))
					{
						strFullText.SetAt(nEnd, (wchar_t)pMsg->wParam);
						m_edit_digital_clock.SetWindowTextW(strFullText);
					}
					m_edit_digital_clock.SetSel(nEnd + 1, nEnd + 1);
					return TRUE;
				}
			}
			else if (pMsg->wParam == VK_LEFT || 
					 pMsg->wParam == VK_RIGHT || 
					 pMsg->wParam == VK_UP || 
					 pMsg->wParam == VK_DOWN) {}
			else if (pMsg->wParam == VK_RETURN)
			{
				worldclock->bWillModify = false;
				for (int i = 0; i < (int)worldclock->analogWatchVector.size(); i++)
				{
					worldclock->analogWatchVector.at(i)->bTimeSync = true;
				}
				this->SetFocus();
				m_edit_digital_clock.HideCaret();
				SetErrorTime();
			}
			else if (pMsg->wParam == VK_ESCAPE)
			{
				worldclock->bWillModify = false;
				this->SetFocus();
				m_edit_digital_clock.HideCaret();
				return TRUE;
			}
			else
			{
				return TRUE;
			}

		}
		else
		{
			if (pMsg->wParam == VK_ESCAPE)
			{
				return TRUE;
			}
		}
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}

void AnalogWatch::SetErrorTime()
{
	CTime curTime = clockData->curTimeVal;

	CString strFormatTime, strFormatHour, strFormatMinute, strFormatSecond;
	m_edit_digital_clock.GetWindowTextW(strFormatTime);
	AfxExtractSubString(strFormatHour, strFormatTime, 0, ':');
	AfxExtractSubString(strFormatMinute, strFormatTime, 1, ':');
	AfxExtractSubString(strFormatSecond, strFormatTime, 2, ':');

	int nHour = _ttoi(strFormatHour);
	int nMinute = _ttoi(strFormatMinute);
	int nSecond = _ttoi(strFormatSecond);

	worldclock->nErrorTimeHour += (curTime.GetHour() - nHour);
	worldclock->nErrorTimeMinute += (curTime.GetMinute() - nMinute);
	worldclock->nErrorTimeSecond += (curTime.GetSecond() - nSecond);
}

void AnalogWatch::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 여기에 메시지 처리기 코드를 추가합니다.
					   // 그리기 메시지에 대해서는 CDialogEx::OnPaint()을(를) 호출하지 마십시오.

	if (bClockDataInit)
	{
		CString strCurDate, strCurTime;
		strCurDate.Format(_T("%04d년 %02d월 %02d일"), clockData->curTimeVal.GetYear(), clockData->curTimeVal.GetMonth(), clockData->curTimeVal.GetDay());
		strCurTime.Format(_T("%02d:%02d:%02d"), clockData->curTimeVal.GetHour(), clockData->curTimeVal.GetMinute(), clockData->curTimeVal.GetSecond());
		m_stt_analog_date.SetWindowTextW(strCurDate);
		m_edit_digital_clock.SetWindowTextW(strCurTime);

	}

	COLORREF borderAMPMBrushColor,borderAMPMPenColor;
	if (clockData->curTimeVal.GetHour() < 12)
	{
		borderAMPMBrushColor = RGB(255, 255, 255);
		borderAMPMPenColor = RGB(0, 0, 0);
	}
	else
	{
		borderAMPMBrushColor = RGB(0, 0, 0);
		borderAMPMPenColor = RGB(255, 255, 255);
	}

	CBrush boderAMPMBrush, ellipseBrush, *pOldBrush;
	CPen borderAMPMPen, markpen, ellipsePen, *pOldPen;
	CFont font, *pOldFont;

	markpen.CreatePen(PS_SOLID, (int)(watchRect.Width() / WATCH_MARKWIDTH), currentTheme->GetFunctionRectBorderColor());
	ellipsePen.CreatePen(PS_SOLID, 2, currentTheme->GetFunctionRectBorderColor());
	borderAMPMPen.CreatePen(PS_GEOMETRIC, 1, borderAMPMPenColor);
	boderAMPMBrush.CreateSolidBrush(borderAMPMBrushColor);
	ellipseBrush.CreateSolidBrush(currentTheme->GetFunctionSubColor());
	font.CreatePointFont(watchRect.Width() / WATCH_HOURTEXT, _T("godoMaum"));

	pOldPen = dc.SelectObject(&borderAMPMPen);
	pOldBrush = dc.SelectObject(&boderAMPMBrush);

	dc.Ellipse(&watchBorderRect);
	dc.SelectObject(&ellipseBrush);
	dc.Ellipse(&watchRect);

	const CPoint cpt = watchRect.CenterPoint();
	double radius = watchRect.Width() / 2;

	dc.SelectObject(&markpen);

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
			dc.SetTextColor(currentTheme->GetFunctionRectBorderColor());
			dc.SetBkColor(currentTheme->GetFunctionSubColor());
			dc.DrawText(str, textrect, DT_CENTER);
		}
		else
			dc.SelectObject(&ellipsePen);

		// 분 마크 그리기
		dc.MoveTo(cpt.x + dpt.x, cpt.y - dpt.y);
		dc.LineTo(cpt.x + dpt.x + mpt.x, cpt.y - dpt.y - mpt.y);

		minmark++;
	}

	if (m_bInitSuccess) DrawTime(dc);


	// 사용한 GDI Object 반환, 삭제	
	dc.SelectObject(pOldPen);
	dc.SelectObject(pOldFont);
	dc.SelectObject(pOldBrush);
	ellipseBrush.DeleteObject();
	ellipsePen.DeleteObject();
	markpen.DeleteObject();
	font.DeleteObject();
	borderAMPMPen.DeleteObject();
	boderAMPMBrush.DeleteObject();
}


void AnalogWatch::DrawTime(CDC& memDC)
{
	int size = watchRect.Width() / WATCH_CENTERSIZE;

	CBrush centerBrush, *pOldBrush;
	centerBrush.CreateSolidBrush(currentTheme->GetFunctionSubColor());
	pOldBrush = memDC.SelectObject(&centerBrush);
	// 중심 점 그리기
	memDC.Ellipse(cpt.x - size, cpt.y - size, cpt.x + size, cpt.y + size);
	memDC.SelectObject(pOldBrush);

	//CTime curTime = CTime::GetCurrentTime();
	CTime curTime(clockData->curTimeVal.GetYear(), clockData->curTimeVal.GetMonth(), clockData->curTimeVal.GetDay(),
				  clockData->curTimeVal.GetHour(), clockData->curTimeVal.GetMinute(), clockData->curTimeVal.GetSecond());

	// 시계 ampm
	CFont ampmfont;
	ampmfont.CreatePointFont(watchRect.Width() / WATCH_LOGOTEXT, _T("godoMaum"));
	memDC.SelectObject(&ampmfont);
	CRect ampmrect(watchRect);
	ampmrect.OffsetRect(0, (int)((double)ampmrect.Height() / WATCH_LOGODOWN / WATCH_LOGODOWN));
	CString strAMPM;
	strAMPM.Format(_T("%s"), curTime.GetHour() < 12 ? _T("AM") : _T("PM"));
	memDC.DrawText(strAMPM, &ampmrect, DT_CENTER);

	double radius = watchRect.Width() / 2;

	// 초,분,시침 좌표 얻기
	CPoint secpt = GetClockHandPos(TIME_SEC, curTime, cpt, radius*WATCH_SECLENGTH);
	CPoint minpt = GetClockHandPos(TIME_MIN, curTime, cpt, radius*WATCH_MINLENGTH);
	CPoint hourpt = GetClockHandPos(TIME_HOUR, curTime, cpt, radius*WATCH_HOURLENGTH);

	// 초,분,시침 그리기
	DrawClockData(memDC, hourpt, WATCH_HOURWIDTH);
	DrawClockData(memDC, minpt, WATCH_MINWIDTH);
	DrawClockData(memDC, secpt, WATCH_SECWIDTH);

	centerBrush.DeleteObject();
	ampmfont.DeleteObject();
}

void AnalogWatch::DrawClockData(CDC& memDC, CPoint selectPoint, const double selectWidth)
{
	CPen pen(PS_SOLID, (int)(watchRect.Width() / selectWidth), currentTheme->GetFunctionRectBorderColor());
	CPen* pOldPen = memDC.SelectObject(&pen);
	memDC.MoveTo(cpt.x, cpt.y);
	memDC.LineTo(cpt.x + selectPoint.x, cpt.y - selectPoint.y);
	
	memDC.SelectObject(pOldPen);
	pen.DeleteObject();
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
		else if (pWnd->GetDlgCtrlID() == m_stt_analog_worldname.GetDlgCtrlID())
		{
			pDC->SetTextColor(currentTheme->GetTextColor());
		}
		else if (pWnd->GetDlgCtrlID() == m_edit_digital_clock.GetDlgCtrlID())
		{
			pDC->SetBkColor(currentTheme->GetFunctionBkColor());
			pDC->SetTextColor(currentTheme->GetTextColor());
			hbr = (HBRUSH)m_digitalBrush;
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
		else if (pWnd->GetDlgCtrlID() == m_edit_digital_clock.GetDlgCtrlID())
		{
			pDC->SetBkColor(currentTheme->GetFunctionBkColor());
			pDC->SetTextColor(currentTheme->GetTextColor());
			hbr = (HBRUSH)m_digitalBrush;
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
		CString strSuccessName;
		m_edit_analog_search.GetWindowTextW(strSuccessName);
		WorldSearchList::GreenWichWorldClockData GMPValue = worldsearchlist->GetWorldClockData(strSuccessName);
		if (GMPValue != WorldSearchList::GreenWichWorldClockData::WORLD_CLOCK_NONE)
		{
			m_stt_analog_worldname.SetWindowTextW(strSuccessName);
			if (nClockIdx == 0) clockData->mainGWCD = GMPValue;
			clockData->subGWCD = GMPValue;
			clockData->strWorldCityName = strSuccessName;
			m_edit_analog_search.SetWindowTextW(_T(""));

			worldclock->SaveClockXml(nClockIdx);
		}
		else
		{
			MessageBox(_T("해당 국가가 존재하지 않습니다."));
		}
	}
}
