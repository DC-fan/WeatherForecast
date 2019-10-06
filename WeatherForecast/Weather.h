#pragma once


// Weather 对话框

class Weather : public CDialogEx
{
	DECLARE_DYNAMIC(Weather)

public:
	Weather(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~Weather();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnLvnItemchangedList2(NMHDR *pNMHDR, LRESULT *pResult);
	void drawRetangle(CPaintDC dc, CPoint point, int h, int w);

	// PM2.5
	CListCtrl PM;
	// 清空原先pm赋值的数据
	void clearData();
	afx_msg void OnClose();
};
