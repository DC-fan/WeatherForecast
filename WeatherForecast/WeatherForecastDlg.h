
// WeatherForecastDlg.h: 头文件
//

#pragma once


// CWeatherForecastDlg 对话框
class CWeatherForecastDlg : public CDialogEx
{
// 构造
public:
	CWeatherForecastDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_WEATHERFORECAST_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	//afx_msg void OnCbnSelchangeCity();
	// 城市控件
	CComboBox CCity;
	// 区域
	CComboBox CGegion;
	// 时间
	CComboBox Ctime;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnClose();
	// 城市各区
	CComboBox region;
	afx_msg void OnCbnSelchangeCity();
	int addRegion(int cityNo);
	// 为各个城市添加各个区
	//int addRegion();
};
