#include "pch.h"
#include "DragWrapper.h"


DragWrapper::DragWrapper(CWnd* dragUseWnd, CWnd* mainFrameParent)
{
	useWnd = dragUseWnd;
	mainFrame = mainFrameParent;

	nDragButtonStdID = 0;
	nDragButtonHovID = 0;
	nDragButtonAltID = 0;
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
			dragDlg->MoveWindow(mousePoint.x - 32, mousePoint.y - 32, 64, 64);
			dragDlg->newButton->DisConnect();
			return TRUE;
		}
	}
	return FALSE;
}

BOOL DragWrapper::ExecuteDragEvent(CGdipButton* currentClickButton)
{
	useWnd->SetCapture();

	bDragActivation = true;
	bUseDragDlg = true;

	nDragButtonStdID = currentClickButton->nStdImageID;
	nDragButtonHovID = currentClickButton->nHovImageID;
	nDragButtonAltID = currentClickButton->nAltImageID;

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