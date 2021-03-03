#pragma once
#include "DragDialog.h"
#include <vector>


template<typename T>
class DragWrapper
{

public:

	DragWrapper()
	{
		bUseDragDlg = false;
		ds = DRAG_STOP;
		bd = BIND_REGULAR;
	}

	~DragWrapper()
	{
	
	}

	enum BindDialog
	{
		BIND_REGULAR = 1,
		BIND_HALF = 2,
	};

	enum DragMode
	{
		MODE_BUTTONVIEW	= 0,
		MODE_MOUSEPOINT = 1
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
	DragMode dm;
	T t;

	CRect targetDragRect;
	bool bUseDragDlg;

protected:

	BOOL ExecuteDragEvent(T t, CalculateStatic* tStatic = nullptr)
	{
		useWnd->SetCapture();

		ds = DRAG_MOVE;

		if (dm == MODE_BUTTONVIEW)
		{
			bUseDragDlg = true;
			bool bBind = (bd == BIND_HALF) ? true : false;
			dragDlg = new DragDialog((CGdipButton*)t, tStatic, 64, 64, bBind, mainFrame);

			dragDlg->Create(DragDialog::IDD, mainFrame);
			dragDlg->ShowWindow(SW_SHOW);
		}
		else if(dm == MODE_MOUSEPOINT)
		{
			this->t = t;
		}

		return TRUE;
	}

	void DeleteDragDlg()
	{
		if (dm == MODE_BUTTONVIEW)
		{
			dragDlg->ShowWindow(SW_HIDE);
			delete dragDlg;
			dragDlg = nullptr;
			bUseDragDlg = false;
		}
	}

	void SetSizeDragDlg(CRect dragSizeRect)
	{
		if (dm == MODE_BUTTONVIEW)
		{
			targetDragRect = dragSizeRect;
			dragDlg->MoveWindow(dragSizeRect);
		}
	}

	BOOL IsDragging(CRect dragRect, POINT mousePoint) 
	{
		BOOL bReturn = FALSE;
		if (ds == DRAG_MOVE)
		{
			if (dm == MODE_BUTTONVIEW)
			{
				if (bUseDragDlg)
				{
					if (PtInRect(dragRect, mousePoint))
					{
						dragDlg->MoveWindow(mousePoint.x - 32, mousePoint.y - 32, targetDragRect.Width() / (int)bd, targetDragRect.Height() / (int)bd);
						dragDlg->newButton->DisConnect();
						bReturn = TRUE;
					}
				}
			}
			else if (dm == MODE_MOUSEPOINT)
			{
				bReturn = TRUE;
			}
		}

		return bReturn;
	}

	BOOL ExistDragDlg()
	{
		if (ds == DRAG_MOVE)
		{
			ReleaseCapture();
			ds = DRAG_STOP;
		}
		return ds == DRAG_STOP ? TRUE : FALSE;
	}

	void Init(CWnd* dragUseWnd, CWnd* mainFrameParent, BindDialog bd, DragMode dm)
	{
		useWnd = dragUseWnd;
		mainFrame = mainFrameParent;
		this->bd = bd;
		this->dm = dm;
	}

	T GetItem()
	{
		return t;
	}

	virtual BOOL DragEventUp(HWND upHWND, CPoint upPoint, T t = nullptr)
	{
		upHWND; upPoint; t;

		return FALSE;
	}

	virtual BOOL DragEventDown(HWND downHWND, CPoint downPoint, T t = nullptr)
	{
		downHWND; downPoint; t;

		return FALSE;
	}

	virtual BOOL DragEventMove(HWND moveHWND, CPoint movePoint, T t = nullptr)
	{
		moveHWND; movePoint; t;

		return FALSE;
	}

};

