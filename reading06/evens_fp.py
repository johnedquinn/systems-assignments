#!/usr/bin/env python3

import sys

print(' '.join(
	list(filter(lambda b: int(b) % 2 == 0, map(lambda a : a, sys.stdin.read().split())))
))
