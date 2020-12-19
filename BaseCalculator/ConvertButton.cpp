// ConvertButton.cpp: 구현 파일
//

#include "pch.h"
#include "GojasTools.h"
#include "ConvertButton.h"


// ConvertButton

IMPLEMENT_DYNAMIC(ConvertButton, CMFCButton)

ConvertButton::ConvertButton()
{
}

ConvertButton::~ConvertButton()
{
}


BEGIN_MESSAGE_MAP(ConvertButton, CMFCButton)
	ON_WM_MOUSEMOVE()
	ON_WM_MOUSEHOVER()
	ON_WM_MOUSELEAVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()



// ConvertButton 메시지 처리기



void ConvertButton::Initialize(COLORREF color, FlatStyle style, CString strFontName /* = _T("고딕")*/, int nFontSize /* = 14*/)
{
	this->EnableWindowsTheming(FALSE);
	this->SetFaceColor(color);
	this->m_bDrawFocus = FALSE;
	
	defaultFont.CreateFontW(nFontSize, 0, 0, 0, FW_NORMAL, FALSE, FALSE, 0, DEFAULT_CHARSET,
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

void ConvertButton::SetAlignment(CMFCButton::AlignStyle style)
{
	this->m_nAlignStyle = style;
}

void ConvertButton::InsertImage(int nImageID)
{
	CPngImage pngImage;
	pngImage.Load(nImageID);
	HBITMAP bitmap = (HBITMAP)pngImage.Detach();
	this->m_bTransparent = TRUE;
	this->m_bDrawFocus = FALSE;
	this->SetImage(bitmap, TRUE);
	this->SizeToContent();
}


void ConvertButton::OnMouseMove(UINT nFlags, CPoint point)
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


void ConvertButton::OnMouseHover(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	if (m_bUseMouseEvent)
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


void ConvertButton::OnMouseLeave()
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	if (m_bUseMouseEvent)
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


void ConvertButton::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	if (m_bUseMouseEvent)
	{
		m_bDown = true;
	}

	CMFCButton::OnLButtonDown(nFlags, point);
}


void ConvertButton::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	if (m_bUseMouseEvent)
	{
		if (m_bDown)
		{
			m_bDown = false;
			this->CMFCButton::SetFont(&clickFont);
		}
	}

	CMFCButton::OnLButtonUp(nFlags, point);
}

void ConvertButton::SetFont(FontFlag flag)
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
