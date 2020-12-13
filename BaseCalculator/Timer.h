#pragma once


// Timer 대화 상자

class Timer : public CDialogEx
{
	DECLARE_DYNAMIC(Timer)

public:
	Timer(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~Timer();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_TIMER };
#endif

private:

	CWnd* pParent;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
	virtual void OnOK();
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnClose();
	virtual void PostNcDestroy();
};
