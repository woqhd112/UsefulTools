#pragma once
#include "DragDialog.h"


class DragWrapper
{

public:

	DragWrapper(CWnd* dragUseWnd, CWnd* mainFrameParent);
	~DragWrapper();

	DragWrapper* GetInstance();
	BOOL DragActivation(CRect dragRect, POINT mousePoint);
	BOOL ExecuteDragEvent(CGdipButton* currentClickButton);
	void DeleteDragDlg();

	int GetDragButtonStdID();
	int GetDragButtonHovID();
	int GetDragButtonAltID();

private:

	CWnd* useWnd;
	CWnd* mainFrame;
	DragDialog* dragDlg;
	bool bUseDragDlg;
	bool bDragActivation;

	int nDragButtonStdID;
	int nDragButtonHovID;
	int nDragButtonAltID;

protected:

	virtual BOOL DragEventUp(HWND upHWND, CPoint upPoint);
	virtual BOOL DragEventDown(HWND downHWND, CPoint downPoint);
	virtual BOOL DragEventMove(HWND moveHWND, CPoint movePoint);


};

