#pragma once
#include "NotePadList.h"
#include "FolderList.h"
#include "NotePadRecycle.h"
#include "UsingManualDialog.h"
//#include "CustomXml.h"
//#include "NoteFile.h"
#include "NotePadManager.h"
#include "CalculateEdit.h"

// NotePad 대화 상자

class NotePad : public CDialogEx
{
	DECLARE_DYNAMIC(NotePad)

	friend class FolderList;
	friend class NotePadList;
	friend class NotePadRecycle;

public:
	NotePad(int nManualImageID, bool bUsingManual, ThemeData* currentTheme, CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~NotePad();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_NOTEPAD };
#endif

private:

	typedef std::vector<NoteItem*> ViewNoteList;
	typedef std::vector<FolderItem0*> ViewFolderList;

	CalculateButton m_btn_edit_bold;
	CalculateButton m_btn_edit_italic;
	CalculateButton m_btn_edit_underline;
	CalculateButton m_btn_create_note;
	CalculateStatic m_stt_notepad_list;
	CalculateStatic m_stt_folderlist;
	CGdipButton m_btn_report;
	CGdipButton m_btn_trash;
	CalculateButton m_btn_addfolder;
	CalculateButton m_btn_allfolder;
	CalculateButton m_btn_otherfolder;
	CRichEditCtrl m_richedit_note;
	CalculateEdit m_edit_lately_note;

	CFont thisFont;

	CWnd* pParent;
	ThemeData* currentTheme;
	UsingManualDialog* usingManual;
	bool bUsingManual;

	NotePadList* notepadlist;
	FolderList* folderlist;
	NotePadRecycle* notepadrecycle;
	NotePadManager* notePadManager;

	CBrush m_topBrush;
	CBrush m_bottomBrush;
	CRect wrapBorderRect;
	CRect wrapCenterRect;
	CRect otherButtonRect;
	CRect trashButtonRect;
	CString strLatelyNoteContent;

	void LoadNotePad();
	void InvalidateSame();
	void SetLatelyNote(CString strLatelyNote);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
	virtual void OnOK();
public:

	CRect dragRect;
	void LoadAllNote();
	void LoadOtherNote();

	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	virtual void PostNcDestroy();
	afx_msg void OnClose();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonEditBold();
	afx_msg void OnBnClickedButtonEditItalic();
	afx_msg void OnBnClickedButtonEditUnderline();
	afx_msg void OnBnClickedButtonNotepadReport();
	afx_msg void OnMove(int x, int y);
	afx_msg void OnPaint();
	afx_msg void OnBnClickedButtonAllNotefolder();
	afx_msg void OnBnClickedButtonOtherNotefolder();
	afx_msg void OnBnClickedButtonAddFolder();
	afx_msg void OnBnClickedButtonNotepadCreateNote();
	afx_msg void OnBnClickedButtonNotepadTrash();
};
