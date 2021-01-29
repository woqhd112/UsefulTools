#pragma once
#include "DragDialog.h"
#include <vector>


class DragWrapper
{

public:
	typedef std::vector<CGdipButton*> ButtonVector;

	DragWrapper();
	~DragWrapper();

	enum BindDialog
	{
		BIND_REGULAR = 1,
		BIND_HALF = 2,
		BIND_THIRD_DIVIDE = 3
	};

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
	BindDialog bd;

	CRect targetDragRect;
	bool bUseDragDlg;

	int nDragButtonStdID;
	int nDragButtonHovID;
	int nDragButtonAltID;
	CString strDragButtonName;

protected:

	BOOL ExecuteDragEvent(CGdipButton* currentClickButton);
	void DeleteDragDlg();
	void SetSizeDragDlg(CRect dragSizeRect);
	BOOL FindButtonSame(ButtonVector findVector, HWND findTargetHWND, CGdipButton** returnButton);

	int GetDragButtonStdID();
	int GetDragButtonHovID();
	int GetDragButtonAltID();
	CString GetDragButtonName();
	BOOL IsDragging(CRect dragRect, POINT mousePoint);
	BOOL ExistDragDlg();

	void Init(CWnd* dragUseWnd, CWnd* mainFrameParent, BindDialog bd);

	virtual BOOL DragEventUp(HWND upHWND, CPoint upPoint);
	virtual BOOL DragEventDown(HWND downHWND, CPoint downPoint);
	virtual BOOL DragEventMove(HWND moveHWND, CPoint movePoint);


};

