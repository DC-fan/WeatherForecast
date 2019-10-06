
// stdafx.cpp : 只包括标准包含文件的源文件
// WeatherForecast.pch 将作为预编译标头
// stdafx.obj 将包含预编译类型信息

#include "stdafx.h"


CString date[7];
CString weather[7];
CString air[7];
//CString tem[7];
CString tem_hight[7];
CString tem_low[7];
double tem1[7];
double tem2[7];
CString ww[7];
struct PM pm;
//0北京 1广州 2上海 3深圳
char region2[4][20][40] = { { "/ haidian /","/chaoyang/","/shunyi/","/huairou/","/tongzhou/","/changping/","/fengtai/","/shijingshan/","/daxing/","/fangshan/","/mentougou/","/pinggu/","/dongchengqu/","/xichengqu/","/miyun/","/yanqing/" },{"/panyu/","/conghua/","/zengcheng/","/huadu/","/liwan/","/yuexiuqu/","/haizhuqu/","/tianhequ/","/huangpuqu/","/nanshaqu/","/luogang/"},{"/minhang/","/baoshan/","/jiading/","/jinshan/","/qingpu/","/songjiang/","/fengxian/","/hongkou1/","/huangpu1/","/changningqu/","/pudong/","/chongming/","/xuhui/","/jinganqu/","/yangpuqu/","/nanhui/","/xujiahui/"},{"/nanshanqu/","/luohu/","/futianqu/","/baoanqu/","/longgang/","/yantianqu/"} };
CString region1[4][20];/* = { { "海淀","朝阳","顺义","怀柔","通州","昌平","丰台","石景山","大兴","房山",
"门头沟","平谷","东城","西城","密云","延庆" },
{ "番禺","从化","增城","花都","荔湾","越秀","海珠","天河","黄埔","南沙","萝岗","贵阳白云" },
{ "闵行","宝山","嘉定","金山","青浦","松江","奉贤","虹口","黄浦","长宁","浦东",
"崇明","徐汇","静安","杨浦","南汇","徐家汇" },
{ "南山","罗湖","福田","龙岗","盐田" } };*/
void CStringToChar(CString str, char * c)
{
	int n = str.GetLength();
	int len = WideCharToMultiByte(CP_ACP, 0, str, n, NULL, 0, NULL, NULL);
	WideCharToMultiByte(CP_ACP, 0, str, str.GetLength(), c, len, NULL, NULL);
	c[len] = 0;
}
CString UTF8ToGB(const char* str)
{
	CString result;
	WCHAR *strSrc;
	LPSTR szRes;

	//获得临时变量的大小
	int i = MultiByteToWideChar(CP_UTF8, 0, str, -1, NULL, 0);
	strSrc = new WCHAR[i + 1];
	MultiByteToWideChar(CP_UTF8, 0, str, -1, strSrc, i);

	//获得临时变量的大小
	i = WideCharToMultiByte(CP_ACP, 0, strSrc, -1, NULL, 0, NULL, NULL);
	szRes = new CHAR[i + 1];
	WideCharToMultiByte(CP_ACP, 0, strSrc, -1, szRes, i, NULL, NULL);

	result = szRes;
	delete[]strSrc;
	delete[]szRes;

	return result;
}

double CStringToDouble(CString str)
{
	char num[10];
	CStringToChar(str, num);
	return atof(num);
}
