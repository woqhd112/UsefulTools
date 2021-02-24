#pragma once
#include "NoteItem.h"
#include "FolderItem.h"


// NotePadRecycle 대화 상자

class NotePad;
class NotePadRecycle : public CDialogEx
{
	DECLARE_DYNAMIC(NotePadRecycle)

public:

	typedef std::vector<NoteItem*> ViewNoteList;
	typedef std::vector<FolderItem0*> ViewFolderList;

	NotePadRecycle(ThemeData* currentTheme, CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~NotePadRecycle();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_NOTEPAD_RECYCLE };
#endif

private:

	ThemeData* currentTheme;
	CWnd* pParent;
	NotePad* notepad;

	ViewNoteList recycleNoteList;
	ViewFolderList recycleFolderList;


public:

	void LoadRecycleData();
	void Init(ViewNoteList recycleNoteList, ViewFolderList recycleFolderList);


protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnClose();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
