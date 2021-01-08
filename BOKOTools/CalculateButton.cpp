// CalculateButton.cpp: 구현 파일
//

#include "pch.h"
#include "BOKOTools.h"
#include "BaseTimer.h"


// CalculateButton

IMPLEMENT_DYNAMIC(CalculateButton, CMFCButton)

CalculateButton::CalculateButton()
{
	m_defaultColor = RGB(220, 220, 220);
	m_hoverColor = RGB(200, 200, 200);
	m_downColor = RGB(150, 150, 150);
	m_bUseMouseBkGroundColorEvent = true;
	m_bClick = false;
	m_bUseMouseTextItalicEvent = false;
	m_bUseMouseTextBoldEvent = false;
	m_bDown = false;
}

CalculateButton::~CalculateButton()
{
}


BEGIN_MESSAGE_MAP(CalculateButton, CMFCButton)
	ON_WM_MOUSEMOVE()
	ON_WM_MOUSEHOVER()
	ON_WM_MOUSELEAVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()



// CalculateButton 메시지 처리기

void CalculateButton::Initialize(COLORREF color, FlatStyle style, CString strFontName /*= _T("고딕")*/, int nFontSize /*= 10*/)
{
	this->EnableWindowsTheming(FALSE);
	this->SetFaceColor(color);
	this->m_bDrawFocus = FALSE;

	nID = this->GetDlgCtrlID();
	int nFontFlag = 0;
	int nRv = GetRValue(color);
	int nGv = GetGValue(color);
	int nBv = GetBValue(color);

	if (nID == IDC_BUTTON_0 ||
		nID == IDC_BUTTON_1 ||
		nID == IDC_BUTTON_2 ||
		nID == IDC_BUTTON_3 ||
		nID == IDC_BUTTON_4 ||
		nID == IDC_BUTTON_5 ||
		nID == IDC_BUTTON_6 ||
		nID == IDC_BUTTON_7 ||
		nID == IDC_BUTTON_8 ||
		nID == IDC_BUTTON_9)
	{
		nFontFlag = FW_BOLD;
		nFontSize = 20;
		m_defaultColor = color;
		m_hoverColor = RGB(MinRGBColor(nRv, 30), MinRGBColor(nGv, 30), MinRGBColor(nBv, 30));
		m_downColor = RGB(MinRGBColor(nRv, 80), MinRGBColor(nGv, 80), MinRGBColor(nBv, 80));
	}
	else
	{
		nFontFlag = FW_NORMAL;
		m_defaultColor = color;
		m_hoverColor = RGB(MinRGBColor(nRv, 20), MinRGBColor(nGv, 20), MinRGBColor(nBv, 20));
		m_downColor = RGB(MinRGBColor(nRv, 70), MinRGBColor(nGv, 70), MinRGBColor(nBv, 70));
	}

	defaultFont.CreateFontW(nFontSize, 0, 0, 0, nFontFlag, FALSE, FALSE, 0, DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS,
		strFontName);
	hoverFont.CreateFontW(nFontSize, 0, 0, 0, FW_NORMAL, FALSE, TRUE, 0, DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS,
		strFontName);
	clickFont.CreateFontW(nFontSize, 0, 0, 0, FW_BOLD, FALSE, FALSE, 0, DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS,
		strFontName);
	clickHoverFont.CreateFontW(nFontSize, 0, 0, 0, FW_BOLD, FALSE, TRUE, 0, DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS,
		strFontName);

	this->CMFCButton::SetFont(&defaultFont);
	this->m_nFlatStyle = style;
}

void CalculateButton::SetAlignment(CMFCButton::AlignStyle style)
{
	this->m_nAlignStyle = style;
}

void CalculateButton::InsertImage(int nImageID)
{
	CPngImage pngImage;
	pngImage.Load(nImageID);
	HBITMAP bitmap = (HBITMAP)pngImage.Detach();
	this->m_bTransparent = TRUE;
	this->m_bDrawFocus = FALSE;
	this->SetImage(bitmap, TRUE);
	this->SizeToContent();
	this->nImageID = nImageID;
}


void CalculateButton::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (!m_bTrackMouse)
	{
		TRACKMOUSEEVENT tme;
		tme.cbSize = sizeof(tme);
		tme.hwndTrack = m_hWnd;
		tme.dwFlags = TME_HOVER | TME_LEAVE;
		tme.dwHoverTime = 1;
		if (TrackMouseEvent(&tme))
		{
			m_bTrackMouse = true;
		}
	}
	

	CMFCButton::OnMouseMove(nFlags, point);
}


void CalculateButton::OnMouseHover(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	
	if (m_bUseMouseBkGroundColorEvent)
	{
		this->SetFaceColor(m_hoverColor);
	}

	if (m_bUseMouseTextItalicEvent)
	{
		if (m_bClick)
		{
			this->CMFCButton::SetFont(&clickHoverFont);
		}
		else
		{
			this->CMFCButton::SetFont(&hoverFont);
		}
	}

	CMFCButton::OnMouseHover(nFlags, point);
}


void CalculateButton::OnMouseLeave()
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	
	if (m_bUseMouseBkGroundColorEvent)
	{
		this->SetFaceColor(m_defaultColor);
	}

	if (m_bUseMouseTextItalicEvent)
	{
		if (m_bClick)
		{
			this->CMFCButton::SetFont(&clickFont);
		}
		else
		{
			this->CMFCButton::SetFont(&defaultFont);
		}
	}

	m_bTrackMouse = false;
	CMFCButton::OnMouseLeave();
}



void CalculateButton::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	if (m_bUseMouseBkGroundColorEvent)
	{
		this->SetFaceColor(m_downColor);
	}

	if (m_bUseMouseTextBoldEvent)
	{
		m_bDown = true;
	}


	CMFCButton::OnLButtonDown(nFlags, point);
}


void CalculateButton::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	if (m_bUseMouseBkGroundColorEvent)
	{
		this->SetFaceColor(m_hoverColor);
	}

	if (m_bUseMouseTextBoldEvent)
	{
		if (m_bDown)
		{
			m_bDown = false;
			this->CMFCButton::SetFont(&clickFont);
		}
	}


	CMFCButton::OnLButtonUp(nFlags, point);
}

void CalculateButton::SetFont(FontFlag flag)
{
	if (flag == FontFlag::DEFAULT)
	{
		this->CMFCButton::SetFont(&defaultFont);
	}
	else if (flag == FontFlag::HOVER)
	{
		this->CMFCButton::SetFont(&hoverFont);
	}
	else if (flag == FontFlag::CLICK)
	{
		this->CMFCButton::SetFont(&clickFont);
	}
	else if (flag == FontFlag::CLICKHOVER)
	{
		this->CMFCButton::SetFont(&clickHoverFont);
	}

}