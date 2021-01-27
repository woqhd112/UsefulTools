#pragma once
#include "DragDialog.h"


class DragWrapper
{

public:

	DragWrapper();
	DragWrapper(CWnd* dragUseWnd, CWnd* mainFrameParent);
	~DragWrapper();

	DragWrapper* GetInstance();
	BOOL DragActivation(CRect dragRect, POINT mousePoint);
	BOOL ExecuteDragEvent(CGdipButton* currentClickButton);
	void DeleteDragDlg();
	void SetSizeDragDlg(CRect dragSizeRect);

	int GetDragButtonStdID();
	int GetDragButtonHovID();
	int GetDragButtonAltID();
	CString GetDragButtonName();
	BOOL IsDragging();
	BOOL ExistDragDlg();



private:

	enum DragStatus
	{
		DRAG_MOVE = 0,
		DRAG_STOP = 1
	};

	DragStatus ds;
	CWnd* useWnd;
	CWnd* mainFrame;
	DragDialog* dragDlg;

	CRect targetDragRect;
	bool bUseDragDlg;

	int nDragButtonStdID;
	int nDragButtonHovID;
	int nDragButtonAltID;
	CString strDragButtonName;

protected:


	virtual BOOL DragEventUp(HWND upHWND, CPoint upPoint);
	virtual BOOL DragEventDown(HWND downHWND, CPoint downPoint);
	virtual BOOL DragEventMove(HWND moveHWND, CPoint movePoint);


};

