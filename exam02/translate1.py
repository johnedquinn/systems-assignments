#!/usr/bin/env python3

import sys
import os

cat = os.popen("cat /etc/passwd").readlines()
matches = {}
for line in cat:
	line = line.split(':')[6]
	matches[line] = matches.get(line, 0) + 1
for key, value in sorted(matches.items(), key=lambda p: p[1], reverse=True):
	print("{:>7} {}".format(value, key), end='')
