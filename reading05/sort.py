#!/usr/bin/env python3

import os
import sys

# Global Variables

rev = False

# Usage function

def usage(status=0):
		print('''Usage: {} files...

		-r  reverse the result of comparisons'''.format(os.path.basename(sys.argv[0])))
		sys.exit(status)

# Parse command line options

args = sys.argv[1:]
while len(args) and args[0].startswith('-') and len(args[0]) > 1:
	arg = args.pop(0)
	if arg == '-h':
		usage(0)
	elif arg == '-r':
		rev = True

if len(args) == 0:
	args.append('-')

# Main execution
for path in args:
	if path == '-':
		stream = sys.stdin
	else:
		stream = open(path)
	newStream = sorted(stream, reverse = rev)
	for line in newStream:
		line = line.rstrip()
		print(line)
	stream.close()
