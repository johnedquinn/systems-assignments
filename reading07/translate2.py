#!/usr/bin/env python3

import os
import re

count = 0
for line in open('/etc/passwd'):
	line = line.split(':')
	if re.findall("[Uu]ser", line[4]):
		count += 1
print(count)

