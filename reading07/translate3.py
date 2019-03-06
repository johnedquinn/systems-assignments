#!/usr/bin/env python3

import requests
import re

names = []
response = requests.get('http://yld.me/raw/Hk1').text
for line in response.splitlines():
	words = line.split(',')
	if re.findall('^B.*', words[1]):
		names.append(words[1])
names = sorted(names)
for name in names:
	print(name)
