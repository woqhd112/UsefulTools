#include "pch.h"
#include "DragWrapper.h"

DragWrapper::DragWrapper()
{

}

DragWrapper::DragWrapper(CWnd* dragUseWnd, CWnd* mainFrameParent)
{
	useWnd = dragUseWnd;
	mainFrame = mainFrameParent;

	nDragButtonStdID = 0;
	nDragButtonHovID = 0;
	nDragButtonAltID = 0;

	bUseDragDlg = false;
	ds = DRAG_STOP;
}

DragWrapper::~DragWrapper()
{

}

BOOL DragWrapper::DragEventUp(HWND upHWND, CPoint upPoint)
{
	upHWND; upPoint;

	return FALSE;
}

BOOL DragWrapper::DragEventDown(HWND downHWND, CPoint downPoint)
{
	downHWND; downPoint;

	return FALSE;
}

BOOL DragWrapper::DragEventMove(HWND moveHWND, CPoint movePoint)
{
	moveHWND; movePoint;

	return FALSE;
}

DragWrapper* DragWrapper::GetInstance()
{
	return this;
}

BOOL DragWrapper::DragActivation(CRect dragRect, POINT mousePoint)
{
	if (bUseDragDlg)
	{
		if (PtInRect(dragRect, mousePoint))
		{
			dragDlg->MoveWindow(mousePoint.x - 32, mousePoint.y - 32, targetDragRect.Width() / 2, targetDragRect.Width() / 2);
			dragDlg->newButton->DisConnect();
			return TRUE;
		}
	}
	return FALSE;
}

BOOL DragWrapper::ExecuteDragEvent(CGdipButton* currentClickButton)
{
	useWnd->SetCapture();

	ds = DRAG_MOVE;
	bUseDragDlg = true;

	nDragButtonStdID = currentClickButton->nStdImageID;
	nDragButtonHovID = currentClickButton->nHovImageID;
	nDragButtonAltID = currentClickButton->nAltImageID;
	strDragButtonName = currentClickButton->strButtonName;

	CGdipButton* hoverButton = currentClickButton;
	dragDlg = new DragDialog(hoverButton, mainFrame);

	dragDlg->Create(DragDialog::IDD);
	dragDlg->ShowWindow(SW_SHOW);

	return TRUE;
}

void DragWrapper::DeleteDragDlg()
{
	dragDlg->ShowWindow(SW_HIDE);
	delete dragDlg;
	dragDlg = nullptr;
	bUseDragDlg = false;
}

void DragWrapper::SetSizeDragDlg(CRect dragSizeRect)
{
	targetDragRect = dragSizeRect;
	dragDlg->MoveWindow(dragSizeRect);
}

int DragWrapper::GetDragButtonStdID()
{
	return nDragButtonStdID;
}

int DragWrapper::GetDragButtonHovID()
{
	return nDragButtonHovID;
}

int DragWrapper::GetDragButtonAltID()
{
	return nDragButtonAltID;
}

CString DragWrapper::GetDragButtonName()
{
	return strDragButtonName;
}

BOOL DragWrapper::IsDragging()
{
	return ds == DRAG_MOVE ? TRUE : FALSE;
}

BOOL DragWrapper::ExistDragDlg()
{
	if (bUseDragDlg)
	{
		ReleaseCapture();
		ds = DRAG_STOP;
	}
	return bUseDragDlg ? TRUE : FALSE;
}