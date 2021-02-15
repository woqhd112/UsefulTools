#pragma once
#include "NotePadList.h"
#include "FolderList.h"
#include "UsingManualDialog.h"
#include "CustomXml.h"
#include "NoteFile.h"

// NotePad 대화 상자
#define TAG_COLOR_1		RGB(245, 85, 79)
#define TAG_COLOR_2		RGB(252, 184, 74)
#define TAG_COLOR_3		RGB(115, 215, 108)
#define TAG_COLOR_4		RGB(131, 94, 224)
#define TAG_COLOR_5		RGB(160, 160, 160)
#define TAG_COLOR_6		RGB(224, 153, 94)
#define TAG_COLOR_7		RGB(94, 165, 224)

class NotePad : public CDialogEx
{
	DECLARE_DYNAMIC(NotePad)

	friend class FolderList;
	friend class NotePadList;

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

	CFont thisFont;

	CWnd* pParent;
	ThemeData* currentTheme;
	UsingManualDialog* usingManual;
	bool bUsingManual;

	NotePadList* notepadlist;
	FolderList* folderlist;

	std::vector<ViewNoteList> allNoteList;
	ViewNoteList otherNoteList;
	ViewFolderList allFolderList;
	
	CBrush m_topBrush;
	CBrush m_bottomBrush;
	CRect wrapBorderRect;
	CRect wrapCenterRect;

	struct NoteSaveData
	{
		int nNoteName;
		int nLock;
		int nFolderSequence;
	};

	struct FolderSaveData
	{
		int nFolderSequence;
		int nSize;
		CString strFolderName;
		COLORREF folderTagColor;
	};

	void LoadNotePad();
	bool CreateDefaultNoteXml(CMarkup* markUp, CString strFullPath);
	void SaveNoteXml(NoteSaveData notedata);
	void CreateNoteXml(NoteSaveData notedata);
	void SaveFolderXml(FolderSaveData folderdata);
	void CreateFolderXml(FolderSaveData folderdata);
	void InvalidateSame();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
	virtual void OnOK();
public:

	CRect dragRect;
	COLORREF GetTagColorFromIndex(int nIndex);
	int GetIndexFromTagColor(COLORREF tagcolor);
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
};
