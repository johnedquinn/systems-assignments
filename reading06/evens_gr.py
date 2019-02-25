#!/usr/bin/env python3

import sys

def evens(stream):
	for i in stream.read().split():
		if int(i) % 2 == 0:
			yield i

print(' '.join(evens(sys.stdin)))

