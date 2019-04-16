#!/usr/bin/env python3

import os

args = {}

for line in os.popen('/bin/ls -l /etc'):
	arg = line.split()[1]
	if arg in args:
		args[arg] += 1
	else:
		args[arg] = 1

for key in sorted(args):
	print("{:7} {}".format(args[key], key))
