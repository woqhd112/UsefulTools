// CalculateButton.cpp: 구현 파일
//

#include "pch.h"
#include "GoCabinet.h"
#include "CalculateButton.h"


// CalculateButton

IMPLEMENT_DYNAMIC(CalculateButton, CMFCButton)

CalculateButton::CalculateButton()
{
	isImage = false;
	m_defaultColor = RGB(220, 220, 220);
	m_hoverColor = RGB(200, 200, 200);
	m_downColor = RGB(150, 150, 150);
	m_bUseMouseEvent = true;
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

void CalculateButton::Initialize(COLORREF color, FlatStyle style, CString strFontName /*= _T("고딕")*/)
{
	this->EnableWindowsTheming(FALSE);
	this->SetFaceColor(color);
	this->m_bDrawFocus = FALSE;

	nID = this->GetDlgCtrlID();
	int nFontFlag = 0;
	int nFontSize = 0;
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
		nFontSize = 15;
		m_defaultColor = color;
		m_hoverColor = RGB(nRv - 30, nGv - 30, nBv - 30);
		m_downColor = RGB(nRv - 80, nGv - 80, nBv - 80);
	}
	else
	{
		nFontFlag = FW_NORMAL;
		nFontSize = 10;
		m_defaultColor = color;
		m_hoverColor = RGB(nRv - 20, nGv - 20, nBv - 20);
		m_downColor = RGB(nRv - 70, nGv - 70, nBv - 70);
	}

	font.CreateFontW(nFontSize, 0, 0, 0, nFontFlag, FALSE, FALSE, 0, DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS,
		strFontName);
	this->SetFont(&font);
	this->m_nFlatStyle = style;
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
	isImage = true;
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
	
	if (m_bUseMouseEvent)
	{
		this->SetFaceColor(m_hoverColor);
	
		if (nImageID == IDB_PNG_TIMELINE_NOMAL)
		{
			CPngImage pngImage;
			pngImage.Load(IDB_PNG_TIMELINE_HOVER);
			HBITMAP bitmap = (HBITMAP)pngImage.Detach();
			this->m_bTransparent = TRUE;
			this->m_bDrawFocus = FALSE;
			this->SetImage(bitmap, TRUE);
			this->SizeToContent();
			this->Invalidate();
		}
		else if (nImageID == IDB_PNG_TRASH_NOMAL)
		{
			CPngImage pngImage;
			pngImage.Load(IDB_PNG_TRASH_HOVER);
			HBITMAP bitmap = (HBITMAP)pngImage.Detach();
			this->m_bTransparent = TRUE;
			this->m_bDrawFocus = FALSE;
			this->SetImage(bitmap, TRUE);
			this->SizeToContent();
			this->Invalidate();
		}
	}

	CMFCButton::OnMouseHover(nFlags, point);
}


void CalculateButton::OnMouseLeave()
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	
	if (m_bUseMouseEvent)
	{
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
			this->SetFaceColor(RGB(230, 230, 230));
		}
		else
		{
			this->SetFaceColor(m_defaultColor);
		}
	
		if (nImageID == IDB_PNG_TIMELINE_NOMAL)
		{
			CPngImage pngImage;
			pngImage.Load(IDB_PNG_TIMELINE_NOMAL);
			HBITMAP bitmap = (HBITMAP)pngImage.Detach();
			this->m_bTransparent = TRUE;
			this->m_bDrawFocus = FALSE;
			this->SetImage(bitmap, TRUE);
			this->SizeToContent();
			this->Invalidate();
		}
		else if (nImageID == IDB_PNG_TRASH_NOMAL)
		{
			CPngImage pngImage;
			pngImage.Load(IDB_PNG_TRASH_NOMAL);
			HBITMAP bitmap = (HBITMAP)pngImage.Detach();
			this->m_bTransparent = TRUE;
			this->m_bDrawFocus = FALSE;
			this->SetImage(bitmap, TRUE);
			this->SizeToContent();
			this->Invalidate();
		}
	}


	m_bTrackMouse = false;
	CMFCButton::OnMouseLeave();
}


void CalculateButton::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	
	if (m_bUseMouseEvent)
	{
		this->SetFaceColor(m_downColor);

		if (nImageID == IDB_PNG_TIMELINE_NOMAL)
		{
			CPngImage pngImage;
			pngImage.Load(IDB_PNG_TIMELINE_DOWN);
			HBITMAP bitmap = (HBITMAP)pngImage.Detach();
			this->m_bTransparent = TRUE;
			this->m_bDrawFocus = FALSE;
			this->SetImage(bitmap, TRUE);
			this->SizeToContent();
		}
		else if (nImageID == IDB_PNG_TRASH_NOMAL)
		{
			CPngImage pngImage;
			pngImage.Load(IDB_PNG_TRASH_DOWN);
			HBITMAP bitmap = (HBITMAP)pngImage.Detach();
			this->m_bTransparent = TRUE;
			this->m_bDrawFocus = FALSE;
			this->SetImage(bitmap, TRUE);
			this->SizeToContent();
			this->Invalidate();
		}
	}

	CMFCButton::OnLButtonDown(nFlags, point);
}


void CalculateButton::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	
	if (m_bUseMouseEvent)
	{
		this->SetFaceColor(m_hoverColor);
	
		if (nImageID == IDB_PNG_TIMELINE_NOMAL)
		{
			CPngImage pngImage;
			pngImage.Load(IDB_PNG_TIMELINE_HOVER);
			HBITMAP bitmap = (HBITMAP)pngImage.Detach();
			this->m_bTransparent = TRUE;
			this->m_bDrawFocus = FALSE;
			this->SetImage(bitmap, TRUE);
			this->SizeToContent();
		}
		else if (nImageID == IDB_PNG_TRASH_NOMAL)
		{
			CPngImage pngImage;
			pngImage.Load(IDB_PNG_TRASH_HOVER);
			HBITMAP bitmap = (HBITMAP)pngImage.Detach();
			this->m_bTransparent = TRUE;
			this->m_bDrawFocus = FALSE;
			this->SetImage(bitmap, TRUE);
			this->SizeToContent();
			this->Invalidate();
		}
	}

	CMFCButton::OnLButtonUp(nFlags, point);
}
