#!/usr/bin/env python3

import sys

print(' '.join(
	[x for x in sys.stdin.read().split() if int(x) % 2 == 0]
))
