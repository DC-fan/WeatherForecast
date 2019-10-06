// Weather.cpp: 实现文件
//

#include "stdafx.h"
#include "WeatherForecast.h"
#include "Weather.h"
#include "afxdialogex.h"
#include <gdiplus.h>
#include <Python.h>

// Weather 对话框

IMPLEMENT_DYNAMIC(Weather, CDialogEx)

Weather::Weather(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG1, pParent)
{

}

Weather::~Weather()
{
}

void Weather::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST3, PM);
}


BEGIN_MESSAGE_MAP(Weather, CDialogEx)
	ON_WM_PAINT()
//	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST2, &Weather::OnLvnItemchangedList2)
ON_WM_CLOSE()
END_MESSAGE_MAP()


// Weather 消息处理程序


BOOL Weather::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	//设置样式风格
	PM.SetExtendedStyle(PM.GetExtendedStyle() | LVS_EX_FULLROWSELECT);
	//插入列表的标题
	CString head[] = { _T("监测点"),_T("AQI"),_T("空气质量指数类别"),_T("PM2.5细颗粒物(μg/m3)") };
	for (int i = 0; i < 4; i++)
		PM.InsertColumn(i, head[i], 0, 165);
	for (int i = 0; pm.place[i] != "\0"; i++)
	{
		PM.InsertItem(i, pm.place[i]);
		PM.SetItemText(i, 1, pm.AQI[i]);
		PM.SetItemText(i, 2, pm.Air[i]);
		PM.SetItemText(i, 3, pm.PM25[i]);
	}
	Weather::OnPaint();

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void Weather::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 在此处添加消息处理程序代码
					   // 不为绘图消息调用 CDialogEx::OnPaint()
	RECT clientRect;
	GetClientRect(&clientRect);//获取客户端区域
	RECT rect = { clientRect.left,clientRect.top,clientRect.right,clientRect.bottom / 2 };
	dc.SetBkMode(TRANSPARENT);//设置透明背景
	RECT rectDate[7],rectWea[7],rectAir[7];
	CFont font;
	font.CreatePointFont(90, TEXT("Arial"));//修改字体 Arial
	dc.SelectObject(&font);
	for (int i = 0; i < 7; i++)//日期,空气质量，天气的绘制区域
	{
		rectDate[i] = { rect.right / 9 * (i + 1),rect.bottom / 6 * 5 ,rect.right / 9 * (i + 2),rect.bottom };
		rectWea[i] = { rect.right / 9 * (i + 1),0,rect.right / 9 * (i + 2),rect.bottom / 12 };
		rectAir[i] = { rect.right / 9 * (i + 1),rect.bottom / 12 ,rect.right / 9 * (i + 2),rect.bottom / 6 };
		dc.DrawText(date[i], -1, &rectDate[i], DT_SINGLELINE | DT_CENTER | DT_VCENTER);
		dc.DrawText(weather[i], -1, &rectWea[i], DT_SINGLELINE | DT_CENTER | DT_VCENTER);
		dc.DrawText(air[i], -1, &rectAir[i], DT_SINGLELINE | DT_CENTER || DT_VCENTER);
	}
	CPen pen,penTem1,penTem2, *pOldPen;
	pen.CreatePen(PS_SOLID, 0, RGB(187, 66, 88));
	pOldPen = dc.SelectObject(&pen);
	//画坐标轴
	dc.MoveTo(rect.right / 9, (rect.top + rect.bottom) / 6 * 5);
	dc.LineTo(rect.right / 9 * 8, rect.bottom / 6 * 5);
	dc.MoveTo(rect.right / 9, rect.bottom / 6);
	dc.LineTo(rect.right / 9, rect.bottom / 6 * 5);
	dc.SelectObject(pOldPen);
	pen.DeleteObject();
	//画最高温  
	penTem1.CreatePen(PS_SOLID, 0, RGB(0, 0, 0));
	pOldPen = dc.SelectObject(&penTem1);
	dc.MoveTo(rect.right / 9 * 1.5, rect.bottom / 60 * (50 - tem1[0]));
	dc.TextOut(rect.right / 9 * 1.5-7, rect.bottom / 60 * (50 - tem1[0]), tem_hight[0]);
	/*dc.MoveTo(rect.right / 9 * 2.5, rect.bottom / 60 * (50 - tem1[1]));
	dc.TextOut(rect.right / 9 * 2.5 - 7, rect.bottom / 60 * (50 - tem1[1]), tem_hight[1]);*/
	for (int i = 1; i < 7; i++)
	{
		dc.LineTo(rect.right / 9 * (i + 1.5), rect.bottom / 60 * (50 - tem1[i]));
		dc.TextOut(rect.right / 9 * (i + 1.5) - 7, rect.bottom / 60 * (50 - tem1[i]), tem_hight[i]);
	}
	dc.SelectObject(pOldPen);
	penTem1.DeleteObject();
	//画最低温  
	penTem2.CreatePen(PS_SOLID, 0, RGB(21, 3, 23));
	pOldPen = dc.SelectObject(&penTem2);
	dc.MoveTo(rect.right / 9 * 1.5, rect.bottom / 60 * (50 - tem2[0]));
	dc.TextOut(rect.right / 9 * 1.5 - 7, rect.bottom / 60 * (50 - tem2[0]), tem_low[0]);
	for (int i = 1; i < 7; i++)
	{
		dc.LineTo(rect.right / 9 * (i + 1.5), rect.bottom / 60 * (50 - tem2[i]));
		dc.TextOut(rect.right / 9 * (i + 1.5) - 7, rect.bottom / 60 * (50 - tem2[i]), tem_low[i]);
	}
	dc.SelectObject(pOldPen);
	penTem2.DeleteObject();
	//PM2.5
	RECT rectPM = { clientRect.left,clientRect.bottom / 2,clientRect.right,clientRect.bottom };
	//CBrush Brush(RGB(123, 32, 2));
	//dc.FillRect(&rectPM, &Brush);
	//affect action
	CPoint point = { clientRect.left,clientRect.bottom / 2 };
	dc.TextOut(point.x + 200, point.y, pm.affect);
	dc.TextOut(point.x + 200, point.y + 20, pm.action);
	//PM2.5
	//标头区域
	//CPoint point = { clientRect.left,clientRect.bottom / 2 };
	//dc.MoveTo(point);
	//dc.LineTo(point.x, point.y + clientRect.bottom / 10);
	//dc.LineTo(point.x + clientRect.right / 9 * 6, point.y + clientRect.bottom / 10);
	//dc.LineTo(point.x + clientRect.right / 9 * 6, point.y);
	//dc.LineTo(point);
	//RECT rectTou = { clientRect.left,clientRect.bottom / 2 ,point.x + clientRect.right / 9 * 6, point.y + clientRect.bottom / 10 };
	////dc.FillRect(&rectTou, &Brush);
	////表图区域
	//point = { clientRect.right / 9,clientRect.bottom / 2 + clientRect.bottom / 10 };
	//dc.MoveTo(point);
	//dc.LineTo(point.x, point.y + clientRect.bottom / 10 * 3);
	//dc.LineTo(point.x + clientRect.right / 9 * 5, point.y + clientRect.bottom / 10 * 3);
	//dc.LineTo(point.x + clientRect.right / 9 * 5, point.y);
	//dc.LineTo(point);
	//CFont font_num;//图两边的数字
	//font_num.CreatePointFont(100, TEXT("宋体"));
	//dc.SelectObject(&font_num);
	//int height = (point.y + clientRect.bottom / 10 * 3 - point.y) / 5;
	//dc.TextOut(point.x - 20, point.y - 5, _T("500"));
	//dc.TextOut(point.x - 20, point.y + height * 1 - 5, _T("400"));
	//dc.TextOut(point.x - 20, point.y + height * 2 - 5, _T("300"));
	//dc.TextOut(point.x - 20, point.y + height * 3 - 5, _T("200"));
	//dc.TextOut(point.x - 20, point.y + height * 4 - 5, _T("100"));
	//dc.TextOut(point.x - 20, point.y + height * 5 - 5, _T("0"));
	//dc.TextOut(point.x + clientRect.right / 9 * 5, point.y + height * 0 - 5, _T("500"));
	//dc.TextOut(point.x + clientRect.right / 9 * 5, point.y + height * 1 - 5, _T("400"));
	//dc.TextOut(point.x + clientRect.right / 9 * 5, point.y + height * 2 - 5, _T("300"));
	//dc.TextOut(point.x + clientRect.right / 9 * 5, point.y + height * 3 - 5, _T("200"));
	//dc.TextOut(point.x + clientRect.right / 9 * 5, point.y + height * 4 - 5, _T("100"));
	//dc.TextOut(point.x + clientRect.right / 9 * 5, point.y + height * 5 - 5, _T("0"));
	///*drawRetangle(point, clientRect.bottom / 10, clientRect.right / 9 * 6);*/
	////右侧区域
	//point = { clientRect.right / 24 * 18,clientRect.bottom / 2 + clientRect.bottom / 14 };
	//dc.MoveTo(point);
	//dc.LineTo(point.x, point.y + clientRect.bottom / 10 * 3);
	//dc.LineTo(point.x + clientRect.right / 7, point.y + clientRect.bottom / 10 * 3);
	//dc.LineTo(point.x + clientRect.right / 7, point.y);
	//dc.LineTo(point);

	
}


void Weather::OnLvnItemchangedList2(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}


void Weather::drawRetangle(CPaintDC dc,CPoint point,int h,int w)
{
	// TODO: 在此处添加实现代码.
	dc.MoveTo(point);
	dc.LineTo(point.x, point.y + h);
	dc.LineTo(point.x + w, point.y + h);
	dc.LineTo(point.x + w, point.y);
	dc.LineTo(point);
}


// 清空原先pm赋值的数据
void Weather::clearData()
{
	// TODO: 在此处添加实现代码.
	for (int i = 0; i < 20; i++)
	{
		pm.place[i] = "";
		pm.AQI[i] = "";
		pm.Air[i] = "";
		pm.PM25[i] = "";
	}
}


void Weather::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	clearData();
	CDialogEx::OnClose();
}
