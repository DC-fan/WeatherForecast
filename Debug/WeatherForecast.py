import requests
from bs4 import BeautifulSoup
import re

def weatherList(region):
	weather = []
	url = "http://www.tianqi.com/"+ region +"/7"
	headers = {"User-Agent":"Mozilla/5.0"}
	try:
		req = requests.get(url,headers = headers)
		req.raise_for_status()
		req.encoding = req.apparent_encoding
		req = req.text
		soup = BeautifulSoup(req,"html.parser")
		aList = soup.select("div[class='weatherbox2'] a")
		# print(type(dlList),len(dlList))
		pattern = re.compile(r'["-"]?[\d]+')
		for i in range(len(aList)):
			w = []
			data = aList[i].select("dl dl")[0].text + "(" + aList[i].select("dl dd[class='week']")[0].text + ")"
			air = aList[i].select("dl dd[class='air']")[0].text
			temp = aList[i].select("dl dd[class='temp']")[0].text
			tem1 = aList[i].select("dl dd[class='txt']")[0].text
			tem1 = pattern.match(tem1)[0]
			tem2 = aList[i].select("dl dd[class='txt'] b")[0].text
			w.append(data)
			w.append(air)
			w.append(temp)
			w.append(tem1)
			w.append(tem2)
			weather.append(w)
		return weather
	except Exception as err:
		print(err)

cityList = ["beijing","guangzhou","shanghai","shenzhen"]
def getData(cityNo):
	url = "http://www.pm25.in/" + cityList[cityNo]
	headers = {"User-Agent":"Mozilla/5.0"}
	try:
		req = requests.get(url,headers = headers)
		req.raise_for_status()
		req.encoding = req.apparent_encoding
		req = req.text
		PMtable = []
		soup = BeautifulSoup(req,"html.parser")
		affect = []
		action = []
		affect.append(soup.select("div[class='affect'] p")[0].text)
		action.append(soup.select("div[class='action'] p")[0].text)
		PMtable.append(affect)
		PMtable.append(action)
		trList = soup.select("div[class='table'] tbody tr")
		# print(type(trList),len(trList))
		for tr in trList:
			PMtr = []
			td = tr.select("td")
			PMtr.append(td[0].text)
			PMtr.append(td[1].text)
			PMtr.append(td[2].text)
			PMtr.append(td[4].text)
			PMtable.append(PMtr)
		return PMtable
	except Exception as err:
		print(err)
# w = weatherList("/panyu/")
# print(type(w),len(w))
# print(type(w[0]),len(w[0]))