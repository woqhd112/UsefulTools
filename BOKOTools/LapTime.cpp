// LapTime.cpp: 구현 파일
//

#include "pch.h"
#include "BOKOTools.h"
#include "LapTime.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// LapTime 대화 상자

IMPLEMENT_DYNAMIC(LapTime, CDialogEx)

LapTime::LapTime(ThemeData* currentTheme, CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_LAPTIME, pParent)
{
	ResetGValue();
	cy = 0;	// 한 페이지의 사이즈

	this->currentTheme = currentTheme;
}

LapTime::~LapTime()
{
	if (!editVector.empty())
	{
		for (int i = 0; i < (int)editVector.size(); i++)
		{
			CEdit* edit = editVector.at(i);
			edit->DestroyWindow();
			delete edit;
			edit = (CEdit*)nullptr;
		}
		editVector.clear();
	}
}

void LapTime::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(LapTime, CDialogEx)
	ON_WM_CTLCOLOR()
	ON_WM_SIZE()
	ON_WM_VSCROLL()
	ON_WM_MOUSEWHEEL()
END_MESSAGE_MAP()


// LapTime 메시지 처리기

void LapTime::ResetGValue()
{
	nStaticEditID = 0;	// 에딧의 동적 아이디
	nStartEditPos = 10;	// 에딧을 입력할 시작 위치
	m_nBasic = 35;	// 스크롤 위아래 버튼 클릭 시 스크롤 간격
	nViewHeight = 0;	// 스크롤 전체 출력 화면
	nScrollPos = 0;	// 현재 스크롤의 위치
	nPageSize = 0;	// 한페이지의 사이즈
	nStaticLapTimeCount = 0;
}


BOOL LapTime::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	GetWindowRect(&thisRect);
	this->SetBackgroundColor(currentTheme->GetFunctionSubColor());
	m_backBrush.CreateSolidBrush(currentTheme->GetFunctionSubColor());

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void LapTime::AppendLapTime(CString strM, CString strS, CString strMils)
{
	int nID = 20000 + (++nStaticEditID);
	nStaticLapTimeCount++;
	CalculateEdit* newEdit = new CalculateEdit;
	newEdit->Create(WS_CHILD | WS_VISIBLE | ES_MULTILINE | ES_LEFT | WS_DISABLED, CRect(0, 0, 0, 0), this, nID);
	newEdit->MoveWindow(10, 10, thisRect.Width() - 30, 10000);
	newEdit->Initialize(25, _T("고딕"));

	CString strFormat;
	strFormat.Format(_T("%d.\t%s : %s : %s"), nStaticLapTimeCount, strM, strS, strMils);
	newEdit->SetWindowTextW(strFormat);
	int lineCount = newEdit->GetLineCount();
	newEdit->MoveWindow(10, nStartEditPos, 240, lineCount * 25);
	nStartEditPos += (lineCount * 25 + 10);
	if (nViewHeight == 0) nViewHeight = 35;
	nViewHeight += (lineCount * 25 + 10);
	SetScrollSize(cy);

	editVector.push_back(newEdit);
	newEdit->Invalidate();

	if(cy < nViewHeight) OnVScroll(SB_LINEDOWN, 0, GetScrollBarCtrl(SB_VERT));
}

void LapTime::DeleteLapTime()
{
	for (int i = 0; i < (int)editVector.size(); i++)
	{
		CalculateEdit* edit = editVector.at(i);
		edit->DestroyWindow();
		delete edit;
		edit = (CalculateEdit*)nullptr;
	}
	editVector.clear();
	ResetGValue();
	SetScrollSize(cy);
}


HBRUSH LapTime::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  여기서 DC의 특성을 변경합니다.
	if (nCtlColor == CTLCOLOR_STATIC)
	{
		if (pWnd->GetDlgCtrlID() >= 20001)
		{
			pDC->SetBkColor(currentTheme->GetFunctionSubColor());
			pDC->SetTextColor(currentTheme->GetFunctionTextColor());
			hbr = (HBRUSH)m_backBrush;
		}
	}
	else
	{
		hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);
	}

	// TODO:  기본값이 적당하지 않으면 다른 브러시를 반환합니다.
	return hbr;
}


void LapTime::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);
	this->cy = cy;
	SetScrollSize(cy);
}


void LapTime::SetScrollSize(int nThisHeight)
{
	//nViewHeight = nStartEditSize;// rect.Height() + 120;
	int nScrollMax = 0;
	if (nThisHeight < nViewHeight)
	{
		nScrollMax = nViewHeight - 1;
		nPageSize = nThisHeight;
		nScrollPos = min(nScrollPos, nViewHeight - nPageSize - 1);
	}

	SCROLLINFO si;
	si.fMask = SIF_RANGE | SIF_PAGE | SIF_POS;
	si.nMin = 0;
	si.nMax = nScrollMax;
	si.nPos = nScrollPos;
	si.nPage = nPageSize;
	SetScrollInfo(SB_VERT, &si, TRUE);
}


void LapTime::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	int delta = 0;
	switch (nSBCode)
	{
	case SB_LINEUP:
		delta = -m_nBasic;
		break;
	case SB_PAGEUP:
		delta = -nPageSize;
		break;
	case SB_THUMBTRACK:
		delta = static_cast<int>(nPos) - nScrollPos;
		break;
	case SB_PAGEDOWN:
		delta = nPageSize;
		break;
	case SB_LINEDOWN:
		delta = m_nBasic;
		break;
	default:
		return;
	}

	int scrollpos = nScrollPos + delta;
	int nMaxPos = nViewHeight - nPageSize;

	if (scrollpos < 0)
	{
		delta = -nScrollPos;
	}
	else
	{
		if (scrollpos > nMaxPos)
		{
			delta = nMaxPos - nScrollPos;
		}
	}

	if (delta != 0)
	{
		nScrollPos += delta;
		SetScrollPos(SB_VERT, nScrollPos, TRUE);
		ScrollWindow(0, -delta);
		nStartEditPos -= delta;
	}
	
	//CDialogEx::OnVScroll(nSBCode, nPos, pScrollBar);
}


BOOL LapTime::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	UINT nFlag;
	if (zDelta > 0)	// 위스크롤
	{
		nFlag = SB_LINEUP;
	}
	else // 아래스크롤
	{
		nFlag = SB_LINEDOWN;
	}

	OnVScroll(nFlag, 0, GetScrollBarCtrl(SB_VERT));

	return CDialogEx::OnMouseWheel(nFlags, zDelta, pt);
}


void LapTime::OnOK()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	//CDialogEx::OnOK();
}
