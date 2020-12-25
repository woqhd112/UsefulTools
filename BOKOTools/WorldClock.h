#pragma once


// WorldClock 대화 상자

class WorldClock : public CDialogEx
{
	DECLARE_DYNAMIC(WorldClock)

public:
	WorldClock(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~WorldClock();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_WORLD_CLOCK };
#endif

private:

	CWnd* pParent;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnClose();
	virtual void PostNcDestroy();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
