//
// GdipButton.cpp : Version 1.0 - see article at CodeProject.com
//
// Author:  Darren Sessions
//          
//
// Description:
//     GdipButton is a CButton derived control that uses GDI+ 
//     to support alternate image formats
//
// History
//     Version 1.0 - 2008 June 10
//     - Initial public release
//
// License:
//     This software is released under the Code Project Open License (CPOL),
//     which may be found here:  http://www.codeproject.com/info/eula.aspx
//     You are free to use this software in any way you like, except that you 
//     may not sell this source code.
//
//     This software is provided "as is" with no expressed or implied warranty.
//     I accept no liability for any damage or loss of business that this 
//     software may cause.
//
///////////////////////////////////////////////////////////////////////////////

#include "pch.h"
#include "GdipButton.h"

#include "CGdiPlusBitmap.h"
#include "MemDC.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGdipButton

CGdipButton::CGdipButton()
{
	m_pStdImage = NULL;
	m_pHovImage = NULL;
	m_pAltImage = NULL;

	m_bHaveBitmaps = FALSE;
	//m_bHaveAltImage = FALSE;

	m_pCurBtn = NULL;

	m_bIsDisabled = FALSE;
	m_bIsToggle = FALSE;

	m_bIsHovering = FALSE;
	m_bIsTracking = FALSE;

	m_nCurType = STD_TYPE;

	m_pToolTip = NULL;

	m_bHaveMinSize = FALSE;
	m_bUseClickSoundEvent = FALSE;

	m_bUseMouseEvent = true;

	nStdImageID = 0;
	nHovImageID = 0;
	nAltImageID = 0;
}

CGdipButton::~CGdipButton()
{
	if(m_pStdImage) delete m_pStdImage;
	if(m_pAltImage) delete m_pAltImage;
	if(m_pHovImage) delete m_pHovImage;

	if(m_pToolTip)	delete m_pToolTip;
}


BEGIN_MESSAGE_MAP(CGdipButton, CButton)
	//{{AFX_MSG_MAP(CGdipButton)
	ON_WM_DRAWITEM()
	ON_WM_ERASEBKGND()
	ON_WM_CTLCOLOR_REFLECT()
	ON_WM_MOUSEMOVE()
	ON_MESSAGE(WM_MOUSELEAVE, OnMouseLeave)
	ON_MESSAGE(WM_MOUSEHOVER, OnMouseHover)
	//}}AFX_MSG_MAP
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()



//=============================================================================
//
// LoadStdImage()
//
// Purpose:     The LoadStdImage() Loads the image for the button.  This 
//				function must be called at a minimum or the button wont do 
//				anything.
//
// Parameters:  
//		[IN]	id
//				resource id, one of the resources already imported with the 
//				resource editor, usually begins with IDR_  
//
//		[IN]	pType
//				pointer to string describing the resource type
//				
// Returns:     BOOL
//				Non zero if successful, otherwise zero
//
//=============================================================================
BOOL CGdipButton::LoadStdImage(UINT id, LPCTSTR pType, BOOL bHavMinSize /* = FALSE*/)
{
	CPngImage png;
	png.Load(id);
	nStdImageID = id;
	this->m_bHaveMinSize = bHavMinSize;
	m_pStdImage = new CGdiPlusBitmapResource;
	return m_pStdImage->Load(id, pType);
}

//=============================================================================
//
// LoadAltImage()
//
// Purpose:     The LoadAltImage() Loads the altername image for the button.  
//				This function call is optional
// Parameters:  
//		[IN]	id
//				resource id, one of the resources already imported with the 
//				resource editor, usually begins with IDR_  
//
//		[IN]	pType
//				pointer to string describing the resource type
//				
// Returns:     BOOL
//				Non zero if successful, otherwise zero
//
//=============================================================================
BOOL CGdipButton::LoadAltImage(UINT id, LPCTSTR pType, BOOL bHavMinSize /* = FALSE*/)
{
	//m_bHaveAltImage = TRUE;
	nAltImageID = id;
	this->m_bHaveMinSize = bHavMinSize;
	m_pAltImage = new CGdiPlusBitmapResource;
	return (m_pAltImage->Load(id, pType));
}

BOOL CGdipButton::LoadHovImage(UINT id, LPCTSTR pType, BOOL bHavMinSize /* = FALSE*/)
{
	nHovImageID = id;
	this->m_bHaveMinSize = bHavMinSize;
	m_pHovImage = new CGdiPlusBitmapResource;
	return (m_pHovImage->Load(id, pType));
}

void CGdipButton::DisConnect()
{
	m_bHaveBitmaps = FALSE;
}

//=============================================================================
//
//	The framework calls this member function when a child control is about to 
//	be drawn.  All the bitmaps are created here on the first call. Every thing
//	is done with a memory DC except the background, which get's it's information 
//	from the parent. The background is needed for transparent portions of PNG 
//	images. An always on top app (such as Task Manager) that is in the way can 
//	cause it to get an incorrect background.  To avoid this, the parent should 
//	call the SetBkGnd function with a memory DC when it creates the background.
//				
//=============================================================================
HBRUSH CGdipButton::CtlColor(CDC* pScreenDC, UINT nCtlColor) 
{
	if(!m_bHaveBitmaps)
	{
		if(!m_pStdImage)
		{
			return NULL; // Load the standard image with LoadStdImage()
		}

		CBitmap bmp, *pOldBitmap;

		CRect rect;
		GetClientRect(rect);

		// do everything with mem dc
		CMyMemDC pDC(pScreenDC, rect);

		Gdiplus::Graphics graphics(pDC->m_hDC);

		// background
		if (m_dcBk.m_hDC != NULL)
		{
			m_dcBk.DeleteDC();
		}
		CRect rect1;
		CClientDC clDC(GetParent());
		GetWindowRect(rect1);
		GetParent()->ScreenToClient(rect1);

		m_dcBk.CreateCompatibleDC(&clDC);
		bmp.CreateCompatibleBitmap(&clDC, rect.Width(), rect.Height());
		pOldBitmap = m_dcBk.SelectObject(&bmp);
		m_dcBk.BitBlt(0, 0, rect.Width(), rect.Height(), &clDC, rect1.left, rect1.top, SRCCOPY);
		bmp.DeleteObject();

		// standard image
		if (m_dcStd.m_hDC != NULL)
		{
			m_dcStd.DeleteDC();
		}
		PaintBk(pDC);

		Gdiplus::ColorMatrix HotMat1 = { 1.05f, 0.00f, 0.00f, 0.00f, 0.00f,
								0.00f, 1.05f, 0.00f, 0.00f, 0.00f,
								0.00f, 0.00f, 1.05f, 0.00f, 0.00f,
								0.00f, 0.00f, 0.00f, 1.00f, 0.00f,
								0.05f, 0.05f, 0.05f, 0.00f, 1.00f };

		Gdiplus::ImageAttributes ia1;
		ia1.SetColorMatrix(&HotMat1);

		float width1 = (float)m_pStdImage->m_pBitmap->GetWidth();
		float height1 = (float)m_pStdImage->m_pBitmap->GetHeight();

		Gdiplus::RectF grect1; grect1.X = 0, grect1.Y = 0; grect1.Width = width1 / 2; grect1.Height = height1 / 2;

		graphics.DrawImage(*m_pStdImage, grect1, 0, 0, width1, height1, UnitPixel, &ia1);
		
		m_dcStd.CreateCompatibleDC(pDC);
		bmp.CreateCompatibleBitmap(pDC, rect.Width(), rect.Height());
		pOldBitmap = m_dcStd.SelectObject(&bmp);
		m_dcStd.BitBlt(0, 0, rect.Width(), rect.Height(), pDC, 0, 0, SRCCOPY);
		bmp.DeleteObject();

		// standard image pressed
		/*if (m_dcStdP.m_hDC == NULL)
		{
			PaintBk(pDC);

			graphics.DrawImage(*m_pStdImage, 1, 1);

			m_dcStdP.CreateCompatibleDC(pDC);
			bmp.CreateCompatibleBitmap(pDC, rect.Width(), rect.Height());
			pOldBitmap = m_dcStdP.SelectObject(&bmp);
			m_dcStdP.BitBlt(0, 0, rect.Width(), rect.Height(), pDC, 0, 0, SRCCOPY);
			bmp.DeleteObject();
		}*/

		// standard image hot
		if (m_dcStdH.m_hDC != NULL)
		{
			m_dcStdH.DeleteDC();
		}
		PaintBk(pDC);

		ColorMatrix HotMat2 = {	1.05f, 0.00f, 0.00f, 0.00f, 0.00f,
								0.00f, 1.05f, 0.00f, 0.00f, 0.00f,
								0.00f, 0.00f, 1.05f, 0.00f, 0.00f,
								0.00f, 0.00f, 0.00f, 1.00f, 0.00f,
								0.05f, 0.05f, 0.05f, 0.00f, 1.00f	};

		ImageAttributes ia2;
		ia2.SetColorMatrix(&HotMat2);

		float width2 = (float)m_pStdImage->m_pBitmap->GetWidth();
		float height2 = (float)m_pStdImage->m_pBitmap->GetHeight();

		RectF grect2; grect2.X=0, grect2.Y=0; grect2.Width = width2; grect2.Height = height2;

		graphics.DrawImage(*m_pStdImage, grect2, 0, 0, width2, height2, UnitPixel, &ia2);

		m_dcStdH.CreateCompatibleDC(pDC);
		bmp.CreateCompatibleBitmap(pDC, rect.Width(), rect.Height());
		pOldBitmap = m_dcStdH.SelectObject(&bmp);
		m_dcStdH.BitBlt(0, 0, rect.Width(), rect.Height(), pDC, 0, 0, SRCCOPY);
		bmp.DeleteObject();

		// grayscale image
		if (m_dcGS.m_hDC != NULL)
		{
			m_dcGS.DeleteDC();
		}
		PaintBk(pDC);

		ColorMatrix GrayMat = {	0.30f, 0.30f, 0.30f, 0.00f, 0.00f,
								0.59f, 0.59f, 0.59f, 0.00f, 0.00f,
								0.11f, 0.11f, 0.11f, 0.00f, 0.00f,
								0.00f, 0.00f, 0.00f, 1.00f, 0.00f,
								0.00f, 0.00f, 0.00f, 0.00f, 1.00f	};

		ImageAttributes ia3;
		ia3.SetColorMatrix(&GrayMat);

		float width3 = (float)m_pStdImage->m_pBitmap->GetWidth();
		float height3 = (float)m_pStdImage->m_pBitmap->GetHeight();

		RectF grect3; grect3.X=0, grect3.Y=0; grect3.Width = width3; grect3.Height = height3;

		graphics.DrawImage(*m_pStdImage, grect3, 0, 0, width3, height3, UnitPixel, &ia3);

		m_dcGS.CreateCompatibleDC(pDC);
		bmp.CreateCompatibleBitmap(pDC, rect.Width(), rect.Height());
		pOldBitmap = m_dcGS.SelectObject(&bmp);
		m_dcGS.BitBlt(0, 0, rect.Width(), rect.Height(), pDC, 0, 0, SRCCOPY);
		bmp.DeleteObject();

		// alternate image
		if ((m_dcAlt.m_hDC != NULL) /*&& m_bHaveAltImage*/)
		{
			m_dcAlt.DeleteDC();
		}

		PaintBk(pDC);

		Gdiplus::ColorMatrix HotMat3 = { 1.05f, 0.00f, 0.00f, 0.00f, 0.00f,
								0.00f, 1.05f, 0.00f, 0.00f, 0.00f,
								0.00f, 0.00f, 1.05f, 0.00f, 0.00f,
								0.00f, 0.00f, 0.00f, 1.00f, 0.00f,
								0.05f, 0.05f, 0.05f, 0.00f, 1.00f };

		Gdiplus::ImageAttributes ia4;
		ia4.SetColorMatrix(&HotMat3);

		float width4 = (float)m_pStdImage->m_pBitmap->GetWidth();
		float height4 = (float)m_pStdImage->m_pBitmap->GetHeight();

		Gdiplus::RectF grect4; grect4.X = 0, grect4.Y = 0; grect4.Width = width4 / 2; grect4.Height = height4 / 2;

		graphics.DrawImage(*m_pAltImage, grect4, 0, 0, width4, height4, UnitPixel, &ia4);
		
		m_dcAlt.CreateCompatibleDC(pDC);
		bmp.CreateCompatibleBitmap(pDC, rect.Width(), rect.Height());
		pOldBitmap = m_dcAlt.SelectObject(&bmp);
		m_dcAlt.BitBlt(0, 0, rect.Width(), rect.Height(), pDC, 0, 0, SRCCOPY);
		bmp.DeleteObject();

		// alternate image pressed
		/*if( (m_dcAltP.m_hDC == NULL) && m_bHaveAltImage )
		{
			PaintBk(pDC);

			graphics.DrawImage(*m_pAltImage, 1, 1);
			
			m_dcAltP.CreateCompatibleDC(pDC);
			bmp.CreateCompatibleBitmap(pDC, rect.Width(), rect.Height());
			pOldBitmap = m_dcAltP.SelectObject(&bmp);
			m_dcAltP.BitBlt(0, 0, rect.Width(), rect.Height(), pDC, 0, 0, SRCCOPY);
			bmp.DeleteObject();
		}*/

		// alternate image hot
		if (m_dcAltH.m_hDC != NULL)
		{
			m_dcAltH.DeleteDC();
		}
		PaintBk(pDC);

		Gdiplus::ColorMatrix HotMat4 = {	1.05f, 0.00f, 0.00f, 0.00f, 0.00f,
								0.00f, 1.05f, 0.00f, 0.00f, 0.00f,
								0.00f, 0.00f, 1.05f, 0.00f, 0.00f,
								0.00f, 0.00f, 0.00f, 1.00f, 0.00f,
								0.05f, 0.05f, 0.05f, 0.00f, 1.00f	};

		Gdiplus::ImageAttributes ia5;
		ia5.SetColorMatrix(&HotMat4);

		float width5 = (float)m_pStdImage->m_pBitmap->GetWidth();
		float height5 = (float)m_pStdImage->m_pBitmap->GetHeight(); 

		Gdiplus::RectF grect5; grect5.X=0, grect5.Y=0; grect5.Width = width5; grect5.Height = height5;

		graphics.DrawImage(*m_pAltImage, grect5, 0, 0, width5, height5, UnitPixel, &ia5);

		m_dcAltH.CreateCompatibleDC(pDC);
		bmp.CreateCompatibleBitmap(pDC, rect.Width(), rect.Height());
		pOldBitmap = m_dcAltH.SelectObject(&bmp);
		m_dcAltH.BitBlt(0, 0, rect.Width(), rect.Height(), pDC, 0, 0, SRCCOPY);
		bmp.DeleteObject();

		// hover image
		if ((m_dcHov.m_hDC != NULL))
		{
			m_dcHov.DeleteDC();
		}
		PaintBk(pDC);

		Gdiplus::ColorMatrix HotMat5 = { 1.05f, 0.00f, 0.00f, 0.00f, 0.00f,
								0.00f, 1.05f, 0.00f, 0.00f, 0.00f,
								0.00f, 0.00f, 1.05f, 0.00f, 0.00f,
								0.00f, 0.00f, 0.00f, 1.00f, 0.00f,
								0.05f, 0.05f, 0.05f, 0.00f, 1.00f };

		Gdiplus::ImageAttributes ia6;
		ia6.SetColorMatrix(&HotMat5);

		float width6 = (float)m_pStdImage->m_pBitmap->GetWidth();
		float height6 = (float)m_pStdImage->m_pBitmap->GetHeight();

		Gdiplus::RectF grect6; grect6.X = 0, grect6.Y = 0; grect6.Width = width6 / 2; grect6.Height = height6 / 2;

		graphics.DrawImage(*m_pHovImage, grect6, 0, 0, width6, height6, UnitPixel, &ia6);

		m_dcHov.CreateCompatibleDC(pDC);
		bmp.CreateCompatibleBitmap(pDC, rect.Width(), rect.Height());
		pOldBitmap = m_dcHov.SelectObject(&bmp);
		m_dcHov.BitBlt(0, 0, rect.Width(), rect.Height(), pDC, 0, 0, SRCCOPY);
		bmp.DeleteObject();

		// alternate image pressed
		/*if ((m_dcHovP.m_hDC == NULL))
		{
			PaintBk(pDC);

			graphics.DrawImage(*m_pHovImage, 1, 1);

			m_dcHovP.CreateCompatibleDC(pDC);
			bmp.CreateCompatibleBitmap(pDC, rect.Width(), rect.Height());
			pOldBitmap = m_dcHovP.SelectObject(&bmp);
			m_dcHovP.BitBlt(0, 0, rect.Width(), rect.Height(), pDC, 0, 0, SRCCOPY);
			bmp.DeleteObject();
		}*/

		// alternate image hot
		if (m_dcHovH.m_hDC != NULL)
		{
			m_dcHovH.DeleteDC();
		}
		PaintBk(pDC);

		Gdiplus::ColorMatrix HotMat6 = { 1.05f, 0.00f, 0.00f, 0.00f, 0.00f,
								0.00f, 1.05f, 0.00f, 0.00f, 0.00f,
								0.00f, 0.00f, 1.05f, 0.00f, 0.00f,
								0.00f, 0.00f, 0.00f, 1.00f, 0.00f,
								0.05f, 0.05f, 0.05f, 0.00f, 1.00f };

		Gdiplus::ImageAttributes ia7;
		ia7.SetColorMatrix(&HotMat6);

		float width7 = (float)m_pStdImage->m_pBitmap->GetWidth();
		float height7 = (float)m_pStdImage->m_pBitmap->GetHeight();

		Gdiplus::RectF grect7; grect7.X = 0, grect7.Y = 0; grect7.Width = width7; grect7.Height = height7;

		graphics.DrawImage(*m_pHovImage, grect7, 0, 0, width7, height7, UnitPixel, &ia7);

		m_dcHovH.CreateCompatibleDC(pDC);
		bmp.CreateCompatibleBitmap(pDC, rect.Width(), rect.Height());
		pOldBitmap = m_dcHovH.SelectObject(&bmp);
		m_dcHovH.BitBlt(0, 0, rect.Width(), rect.Height(), pDC, 0, 0, SRCCOPY);
		bmp.DeleteObject();

		if(m_pCurBtn == NULL)
		{
			m_pCurBtn = &m_dcStd;
		}

		m_bHaveBitmaps = TRUE;
	}

	return NULL;
}

//=============================================================================
// paint the background
//=============================================================================
void CGdipButton::PaintBk(CDC *pDC)
{
	CRect rect;
	GetClientRect(rect);
	pDC->BitBlt(0, 0, rect.Width(), rect.Height(), &m_dcBk, 0, 0, SRCCOPY);
}

//=============================================================================
// paint the bitmap currently pointed to with m_pCurBtn
//=============================================================================
void CGdipButton::PaintBtn(CDC *pDC)
{
	CRect rect;
	GetClientRect(rect);
	pDC->BitBlt(0, 0, rect.Width(), rect.Height(), m_pCurBtn, 0, 0, SRCCOPY);
}

//=============================================================================
// enables the toggle mode
// returns if it doesn't have the alternate image
//=============================================================================
void CGdipButton::EnableToggle(BOOL bEnable)
{
	//if(!m_bHaveAltImage) return;

	m_bIsToggle = bEnable; 

	// this actually makes it start in the std state since toggle is called before paint
	if(bEnable)	m_pCurBtn = &m_dcAlt;
	else		m_pCurBtn = &m_dcStd;

}

//=============================================================================
// sets the image type and disabled state then repaints
//=============================================================================
void CGdipButton::SetImage(int type)
{
	m_nCurType = type;

	(type == DIS_TYPE) ? m_bIsDisabled = TRUE : m_bIsDisabled = FALSE;

	Invalidate();
}

//=============================================================================
// set the control to owner draw
//=============================================================================
void CGdipButton::PreSubclassWindow()
{
	// Set control to owner draw
	ModifyStyle(0, BS_OWNERDRAW, SWP_FRAMECHANGED);

	CButton::PreSubclassWindow();
}

//=============================================================================
// disable double click 
//=============================================================================
BOOL CGdipButton::PreTranslateMessage(MSG* pMsg) 
{
	if (pMsg->message == WM_LBUTTONDBLCLK)
		pMsg->message = WM_LBUTTONDOWN;

	if (m_pToolTip != NULL)
	{
		if (::IsWindow(m_pToolTip->m_hWnd))
		{
			m_pToolTip->RelayEvent(pMsg);		
		}
	}
	

	return CButton::PreTranslateMessage(pMsg);
}


//=============================================================================
// overide the erase function
//=============================================================================
BOOL CGdipButton::OnEraseBkgnd(CDC* pDC) 
{
	return TRUE;
}

//=============================================================================
// Paint the button depending on the state of the mouse
//=============================================================================
void CGdipButton::DrawItem(LPDRAWITEMSTRUCT lpDIS) 
{
	CDC* pDC = CDC::FromHandle(lpDIS->hDC);

	// handle disabled state
	if(m_bIsDisabled)
	{
		m_pCurBtn = &m_dcGS;
		PaintBtn(pDC);
		return;
	}

	BOOL bIsPressed = (lpDIS->itemState & ODS_SELECTED);

	// handle toggle button
	if(m_bIsToggle && bIsPressed)
	{
		(m_nCurType == STD_TYPE) ? m_nCurType = ALT_TYPE : m_nCurType = STD_TYPE;
	}

	if(bIsPressed)
	{
		if (m_nCurType == STD_TYPE)
		{
			if (m_bHaveMinSize) m_pCurBtn = &m_dcAlt; 
			else m_pCurBtn = &m_dcAltH; 
		}
		else
		{
			if (m_bHaveMinSize) m_pCurBtn = &m_dcStd;
			else m_pCurBtn = &m_dcStdH;
		}
	}
	else if(m_bIsHovering)
	{
		if (m_nCurType == STD_TYPE)
		{
			if (m_bHaveMinSize) m_pCurBtn = &m_dcHov;
			else m_pCurBtn = &m_dcHovH;
		}
		else
		{
			if (m_bHaveMinSize) m_pCurBtn = &m_dcAlt;
			else m_pCurBtn = &m_dcAltH;
		}
	}
	else
	{
		if (m_nCurType == STD_TYPE)
		{
			if (m_bHaveMinSize) m_pCurBtn = &m_dcStd;
			else m_pCurBtn = &m_dcStdH;
		}
		else
		{
			if (m_bHaveMinSize) m_pCurBtn = &m_dcAlt;
			else m_pCurBtn = &m_dcAltH;
		}
	}

	// paint the button
	PaintBtn(pDC);
}

void CGdipButton::UseHoverEvent()
{
	m_bIsHovering = TRUE;
	Invalidate();
	DeleteToolTip();

	// Create a new Tooltip with new Button Size and Location
	SetToolTipText(m_tooltext);

	if (m_pToolTip != NULL)
	{
		if (::IsWindow(m_pToolTip->m_hWnd))
		{
			//Display ToolTip
			m_pToolTip->Update();
		}
	}
}

void CGdipButton::UserLeaveEvent()
{
	m_bIsTracking = FALSE;
	m_bIsHovering = FALSE;
	Invalidate();
}

//=============================================================================
LRESULT CGdipButton::OnMouseHover(WPARAM wparam, LPARAM lparam) 
//=============================================================================
{
	if (m_bUseMouseEvent)
	{
		UseHoverEvent();
	}

	return 0;
}


//=============================================================================
LRESULT CGdipButton::OnMouseLeave(WPARAM wparam, LPARAM lparam)
//=============================================================================
{
	if (m_bUseMouseEvent)
	{
		UserLeaveEvent();
	}
	return 0;
}

//=============================================================================
void CGdipButton::OnMouseMove(UINT nFlags, CPoint point) 
//=============================================================================
{
	if (!m_bIsTracking)
	{
		TRACKMOUSEEVENT tme;
		tme.cbSize = sizeof(tme);
		tme.hwndTrack = m_hWnd;
		tme.dwFlags = TME_LEAVE|TME_HOVER;
		tme.dwHoverTime = 1;
		m_bIsTracking = _TrackMouseEvent(&tme);
	}
	
	CButton::OnMouseMove(nFlags, point);
}

//=============================================================================
//	
//	Call this member function with a memory DC from the code that paints 
//	the parents background.  Passing the screen DC defeats the purpose of 
//  using this function.
//
//=============================================================================
void CGdipButton::SetBkGnd(CDC* pDC)
{
	CRect rect, rectS;
	CBitmap bmp, *pOldBitmap;

	GetClientRect(rect);
	GetWindowRect(rectS);
	GetParent()->ScreenToClient(rectS);

	m_dcBk.DeleteDC();

	m_dcBk.CreateCompatibleDC(pDC);
	bmp.CreateCompatibleBitmap(pDC, rect.Width(), rect.Height());
	pOldBitmap = m_dcBk.SelectObject(&bmp);
	m_dcBk.BitBlt(0, 0, rect.Width(), rect.Height(), pDC, rectS.left, rectS.top, SRCCOPY);
	bmp.DeleteObject();
}


//=============================================================================
// Set the tooltip with a string resource
//=============================================================================
void CGdipButton::SetToolTipText(UINT nId, BOOL bActivate)
{
	// load string resource
	m_tooltext.LoadString(nId);

	// If string resource is not empty
	if (m_tooltext.IsEmpty() == FALSE)
	{
		SetToolTipText(m_tooltext, bActivate);
	}

}

//=============================================================================
// Set the tooltip with a CString
//=============================================================================
void CGdipButton::SetToolTipText(CString spText, BOOL bActivate)
{
	// We cannot accept NULL pointer
	if (spText.IsEmpty()) return;

	// Initialize ToolTip
	InitToolTip();
	m_tooltext = spText;

	// If there is no tooltip defined then add it
	if (m_pToolTip->GetToolCount() == 0)
	{
		CRect rectBtn; 
		GetClientRect(rectBtn);
		m_pToolTip->AddTool(this, m_tooltext, rectBtn, 1);
	}

	// Set text for tooltip
	m_pToolTip->UpdateTipText(m_tooltext, this, 1);
	m_pToolTip->SetDelayTime(2000);
	m_pToolTip->Activate(bActivate);
}

//=============================================================================
void CGdipButton::InitToolTip()
//=============================================================================
{
	if (m_pToolTip == NULL)
	{
		m_pToolTip = new CToolTipCtrl;
		// Create ToolTip control
		m_pToolTip->Create(this);
		m_pToolTip->Activate(TRUE);
	}
} 

//=============================================================================
void CGdipButton::DeleteToolTip()
//=============================================================================
{
	// Destroy Tooltip incase the size of the button has changed.
	if (m_pToolTip != NULL)
	{
		delete m_pToolTip;
		m_pToolTip = NULL;
	}
}

void CGdipButton::SetClickSound(CString strSoundPath)
{
	m_bUseClickSoundEvent = true;
	this->strSoundPath = strSoundPath;
}

void CGdipButton::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	if(m_bUseClickSoundEvent) m_soundThread = AfxBeginThread(thrLoadSound, this);

	CButton::OnLButtonDown(nFlags, point);
}


void CGdipButton::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CButton::OnLButtonUp(nFlags, point);
}

UINT CGdipButton::thrLoadSound(LPVOID method)
{
	CGdipButton* button = (CGdipButton*)method;
	button->StartSound();

	return 0;
}

void CGdipButton::StartSound()
{
	PlaySound(strSoundPath, 0, SND_ASYNC);
}
