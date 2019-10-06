import requests
from bs4 import BeautifulSoup
import re
import os
def urlList(city):
	url = "http://www.tianqi.com/" + city
	headers = {"User-Agent":"Mozilla/5.0"}
	try:
		req = requests.get(url,headers = headers)
		req.raise_for_status()
		req.encoding = req.apparent_encoding
		req = req.text
		soup = BeautifulSoup(req,"html.parser")
		liList = soup.select("div[class='mainWeather'] ul li")
		# print(type(liList),len(liList))
		# print(liList)
		if os.path.isfile("weatherUrl.txt"):
			with open("weatherUrl.txt",'a') as f:
				f.write(city+"各区的url如下:\n")
				for i in range(len(liList)-1):
					region = liList[i].select("h5")[0].text
					href = liList[i].select("a")[0]["href"]
					href = "http://www.tianqi.com" + href +"7"					
					f.write(region+":"+href+"\n")
		else:
			with open("weatherUrl.txt",'w') as f:
				f.write(city+"各区的url如下:\n")
				for i in range(len(liList)-1):
					region = liList[i].select("h5")[0].text
					href = liList[i].select("a")[0]["href"]
					href = "http://www.tianqi.com" + href +"7"
					f.write(region+":"+href+"\n")
		print(city+"各区的url已保存到文件")
	except Exception as err:
		print(err)

cityList = ["guangzhou","shenzhen","beijing","shanghai"]
for city in cityList:
	urlList(city)


