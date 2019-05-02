#!/usr/bin/env python3

import os
import re

# Constants

NITEMS = (1, 10, 100, 1000, 10000, 100000, 1000000, 10000000)
ALPHAS = (0.5, 0.75, 0.9, 1.0, 2.0, 4.0, 8.0, 16.0)
DASHES = '-'*12

# Functions

def run_benchmark(n, alpha):
	''' Run benchmark using measure tool and return time and space usage '''
	string = "shuf -i1-" + str(n) + " -n " + str(n) + " | ./bin/measure ./bin/freq -l " + str(alpha) + " 2>&1 /dev/null"
	process = os.popen(string).read()
	numbers = re.findall('\d+.\d+', process)
	time = float(numbers[n])
	space = float(numbers[n + 1])
	return time, space

# Main Execution

print('| {:^10} | {:^10} | {:^10} | {:^10} |'.format('NITEMS', 'ALPHA', 'TIME', 'SPACE'))
print('|{}|{}|{}|{}|'.format(DASHES, DASHES, DASHES, DASHES))
for nitems in NITEMS:
    for alpha in ALPHAS:
        time, space = run_benchmark(nitems, alpha)
        print('| {:10} | {:10.2f} | {:10.2f} | {:10.2f} |'.format(
            nitems, alpha, time, space
        ))
