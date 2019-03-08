#!/usr/bin/env python3

import sys
import os
import requests

response = requests.get("https://yld.me/raw/Hk1")
#for line in response.text.splitlines():
for line in sorted(response.text.splitlines(), key=lambda p: p.split(',')[1]):
	word = line.split(',')[0]
	print(word.upper())
#	print(line)
	
