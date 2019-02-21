#!/usr/bin/env python3

import os
import sys

# Global Variables

num = 10

# Usage function

def usage(status=0):
		print('''Usage: {} files...

		-n  NUM      print the first NUM lines instead of the first 10'''.format(os.path.basename(sys.argv[0])))
		sys.exit(status)

# Parse command line options

args = sys.argv[1:]
while len(args) and args[0].startswith('-') and len(args[0]) > 1:
	arg = args.pop(0)
	if arg == '-h':
		usage(0)
	elif arg == '-n':
		num = args.pop(0)

if len(args) == 0:
	args.append('-')

num = int(num)
currentLine = 0

# Main execution
for path in args:
	if path == '-':
		stream = sys.stdin
	else:
		stream = open(path)
	for line in stream:
		currentLine = currentLine + 1
		line = line.rstrip()
		if currentLine <= num:
			print(line)
	stream.close()
