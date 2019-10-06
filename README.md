# WeatherForecast
一个简单的天气预报爬取软件
项目是基于MFC中的，数据是通过调用python爬虫爬取的
其中python的文件是32位，因此MFC中的版本也应该是32位，若运行提示无法打开python.h文件
C++调用Python主要使用到Python安装路径下的include、libs（文件已包含）、该目录下相关dll。，将include文件路径添加到VS工程属性的 “包含目录” ，将libs文件夹路径添加到VS工程属性的 “库目录” ，并在工程属性 -> 链接器 -> 附件依赖项 中添加libs文件夹中相关lib文件（）。
