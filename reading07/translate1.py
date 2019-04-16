#!/usr/bin/env python3

import os
import re

count = 0
for line in open('/etc/passwd'):
	for instance in re.findall("9\d*9", line):
		count += 1
print(count)

