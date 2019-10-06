
// WeatherForecastDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "WeatherForecast.h"
#include "WeatherForecastDlg.h"
#include "afxdialogex.h"
#include <Python.h>
#include "Weather.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CWeatherForecastDlg 对话框



CWeatherForecastDlg::CWeatherForecastDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_WEATHERFORECAST_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CWeatherForecastDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CITY, CCity);
	/*DDX_Control(pDX, IDC_REGION, CGegion);
	DDX_Control(pDX, IDC_TIME, Ctime);*/
	DDX_Control(pDX, IDC_COMBO1, region);
}

BEGIN_MESSAGE_MAP(CWeatherForecastDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//ON_CBN_SELCHANGE(IDC_CITY, &CWeatherForecastDlg::OnCbnSelchangeCity)
	ON_BN_CLICKED(IDC_BUTTON1, &CWeatherForecastDlg::OnBnClickedButton1)
	ON_WM_CLOSE()
	ON_CBN_SELCHANGE(IDC_CITY, &CWeatherForecastDlg::OnCbnSelchangeCity)
END_MESSAGE_MAP()


// CWeatherForecastDlg 消息处理程序

BOOL CWeatherForecastDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	region1[0][0] = "海淀";
	region1[0][1] = "朝阳";
	region1[0][2] = "顺义";
	region1[0][3] = "怀柔";
	region1[0][4] = "通州";
	region1[0][5] = "昌平";
	region1[0][6] = "丰台";
	region1[0][7] = "石景山";
	region1[0][8] = "大兴";
	region1[0][9] = "房山";
	region1[0][10] = "门头沟";
	region1[0][11] = "平谷";
	region1[0][12] = "东城";
	region1[0][13] = "西城";
	region1[0][14] = "密云";
	region1[0][15] = "延庆";
	region1[1][0] = "番禺";
	region1[1][1] = "从化";
	region1[1][2] = "增城";
	region1[1][3] = "花都";
	region1[1][4] = "荔湾";
	region1[1][5] = "越秀";
	region1[1][6] = "海珠";
	region1[1][7] = "天河";
	region1[1][8] = "黄埔";
	region1[1][9] = "南沙";
	region1[1][10] = "萝岗";
	region1[1][11] = "贵阳白云";
	region1[2][0] = "闵行";
	region1[2][1] = "宝山";
	region1[2][2] = "嘉定";
	region1[2][3] = "金山";
	region1[2][4] = "青浦";
	region1[2][5] = "松江";
	region1[2][6] = "奉贤";
	region1[2][7] = "虹口";
	region1[2][8] = "黄浦";
	region1[2][9] = "长宁";
	region1[2][10] = "浦东";
	region1[2][11] = "崇明";
	region1[2][12] = "徐汇";
	region1[2][13] = "静安";
	region1[2][14] = "杨浦";
	region1[2][15] = "南汇";
	region1[2][16] = "徐家汇";
	region1[3][0] = "南山";
	region1[3][1] = "罗湖";
	region1[3][2] = "福田";
	region1[3][3] = "龙岗";
	region1[3][4] = "盐田";
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CWeatherForecastDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CWeatherForecastDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CWeatherForecastDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



//void CWeatherForecastDlg::OnCbnSelchangeCity()
//{
//	// TODO: 在此添加控件通知处理程序代码
//	//CCity.GETCURSEL() 
//	//0：北京 1：上海 2：广州 3：成都
//	int cursel;
//	switch (CCity.GetCurSel())
//	{
//	case 0:break;
//	case 1:break;
//	case 2:break;
//	case 3:break;
//	default:
//		break;
//	}
//}


void CWeatherForecastDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	int flag = 0;
	Py_Initialize();
	PyObject *pModule = NULL;
	PyObject *pFunc = NULL, *pFunc_PM = NULL;
	//PyObject *pName = NULL;
	PyRun_SimpleString("import sys");
	PyRun_SimpleString("sys.path.append('/')");
	/*PyRun_SimpleString("import urllib.request");
	PyRun_SimpleString("from bs4 import BeautifulSoup");
	PyRun_SimpleString("from bs4 import UnicodeDammit");
	PyRun_SimpleString("import re");*/
	pModule = PyImport_ImportModule("WeatherForecast");
	/*pModule_PM = PyImport_ImportModule("PM2.5");*/
	pFunc = PyObject_GetAttrString(pModule, "weatherList");
	pFunc_PM = PyObject_GetAttrString(pModule, "getData");
	//0：北京 1：上海 2：广州 3：深圳
	//cityCode = { "北京":"101010100","上海" : "101020100","广州" : "101280101","深圳" : "101280601" }
	int cityNo = CCity.GetCurSel();
	int regionNo = region.GetCurSel();
	//调用python模块
	PyObject *pArgs = PyTuple_New(1);//一个参数 WeatherForecast weatherList
	PyObject *pArgs_PM = PyTuple_New(1);//一个参数 城市编号
	PyTuple_SetItem(pArgs, 0, Py_BuildValue("s", region2[cityNo][regionNo]));//传参
	PyTuple_SetItem(pArgs_PM, 0, Py_BuildValue("i", cityNo));//传参，整数类型
	PyObject *pReturnList = PyObject_CallObject(pFunc, pArgs);//获取返回值
	PyObject *pReturnPMList = PyObject_CallObject(pFunc_PM, pArgs_PM);
	if (pReturnPMList != NULL)
	{
		char *affect, *action;
		PyObject *pList_PM_affect = PyList_GetItem(pReturnPMList, 0);
		PyObject *pList_PM_action = PyList_GetItem(pReturnPMList, 1);
		PyObject *pAffect = PyList_GetItem(pList_PM_affect, 0);
		PyObject *pAction = PyList_GetItem(pList_PM_action, 0);
		PyArg_Parse(pAffect,"s", &affect);
		pm.affect = UTF8ToGB(affect);
		PyArg_Parse(pAction, "s", &action);
		pm.action = UTF8ToGB(action);
		for (int i = 2; i < PyList_Size(pReturnPMList); i++)
		{
			char *data_PM;
			PyObject *pList_PM = PyList_GetItem(pReturnPMList, i);
			PyObject *pRegion = PyList_GetItem(pList_PM, 0);
			PyObject *pAQI = PyList_GetItem(pList_PM, 1);
			PyObject *pAir = PyList_GetItem(pList_PM, 2);
			PyObject *pPM = PyList_GetItem(pList_PM, 3);
			PyArg_Parse(pRegion, "s", &data_PM);
			pm.place[i - 2] = UTF8ToGB(data_PM);
			PyArg_Parse(pAQI, "s", &data_PM);
			pm.AQI[i - 2] = UTF8ToGB(data_PM);
			PyArg_Parse(pAir, "s", &data_PM);
			pm.Air[i - 2] = UTF8ToGB(data_PM);
			PyArg_Parse(pPM, "s", &data_PM);
			pm.PM25[i - 2] = UTF8ToGB(data_PM);
		}
		flag = flag + 1;
	}
	else
	{
		MessageBox(_T("爬取失败"));
	}
	if (pReturnList != NULL)//处理返回的列表
	{
		for (int i = 0; i < PyList_Size(pReturnList); i++)
		{
			char *data,*w,*a,*t1,*t2;
			PyObject *pList = PyList_GetItem(pReturnList, i);
			PyObject *pDate = PyList_GetItem(pList, 0);
			PyObject *pWeather = PyList_GetItem(pList, 1);
			PyObject *pAir = PyList_GetItem(pList, 2);
			/*PyObject *pTem = PyList_GetItem(pList, 3);*/
			PyObject *pTemHight = PyList_GetItem(pList, 3);
			PyObject *pTemLow = PyList_GetItem(pList, 4);
			PyArg_Parse(pDate, "s", &data);
			date[i] = UTF8ToGB(data);
			PyArg_Parse(pWeather, "s", &w);
			weather[i] = UTF8ToGB(w);
			PyArg_Parse(pAir, "s", &a);
			air[i] = UTF8ToGB(a);
			PyArg_Parse(pTemHight, "s", &t1);
			tem_hight[i] = UTF8ToGB(t1);
			PyArg_Parse(pTemLow, "s", &t2);
			tem_low[i] = UTF8ToGB(t2);
		}
		for (int i = 0; i < 7; i++)
		{
			tem1[i] = CStringToDouble(tem_hight[i]);
			tem2[i] = CStringToDouble(tem_low[i]);
		}
		flag = flag + 1;
	}
	else
		MessageBox(_T("爬取失败"));

	Py_DECREF(pModule);
	Py_DECREF(pFunc);
	//Py_DECREF(pName);
	Py_DECREF(pArgs);
	Py_DECREF(pReturnList);
	//PyGILState_STATE state = PyGILState_Ensure（）;
	Py_Finalize();
	if (flag == 2)
	{
		Weather *dlg;
		dlg = new Weather();
		dlg->DoModal();
	}
	
	//ofstream out;

}


void CWeatherForecastDlg::OnClose()
{
	// TODO: 在此添加消息处理程序代码
	CDialogEx::OnClose();
}


void CWeatherForecastDlg::OnCbnSelchangeCity()
{
	// TODO: 在此添加控件通知处理程序代码
	int no;
	no = CCity.GetCurSel();
	addRegion(no);
}


// 为各个城市添加各个区
int CWeatherForecastDlg::addRegion(int cityNo)
{
	// TODO: 在此处添加实现代码.
	for (int i = region.GetCount(); i > -1; i--)
		region.DeleteString(i);
	for (int i = 0; i < 20; i++)
		if (region1[cityNo][i] != "\0")
			region.InsertString(-1,region1[cityNo][i]);

	return 0;
}
