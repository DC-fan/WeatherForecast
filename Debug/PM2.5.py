import requests
from bs4 import BeautifulSoup
import re

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


# table = getData(1)
# print(type(table),len(table),type(table[1]),len(table[1]))
# for t in table:
# 	for tr in t:
# 		print(tr,end="")
# 	print("")
