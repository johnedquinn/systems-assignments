#!/usr/bin/env python3

import collections
import os
import sys

import requests
from collections import defaultdict

########## GLOBALS ##########

URL     = 'https://yld.me/raw/MtP'
GENDERS = ('M', 'F')
ETHNICS = ('B', 'C', 'N', 'O', 'S', 'T', 'U')

########## FUNCTIONS ##########

def usage(status=0):
    ''' Display usage information and exit with specified status '''
    print('''Usage: {} [options] URL

    -y  YEARS   Which years to display (default: all)
    -p          Display data as percentages.
    -G          Do not include gender information.
    -E          Do not include ethnic information.
    '''.format(os.path.basename(sys.argv[0])))
    sys.exit(status)

def load_demo_data(url=URL):
	''' Load demographics from specified URL into dictionary '''
	data = collections.defaultdict(dict)
	response = requests.get(url)
	for index, line in enumerate(response.text.rsplit()):
		if not index:
			continue
		line = line.rstrip()
		year, sex, ethnic = line.split(',')
		data[year][sex] = data[year].get(sex, 0) + 1
		data[year][ethnic] = data[year].get(ethnic, 0) + 1
	return data

def dump_demo_data(data, years=None, percent=False, gender=True, ethnic=True):
	''' Dump demographics data for the specified years and attributes '''
	dump_demo_years(years)
	if gender:
		dump_demo_gender(data, years, percent)
	if ethnic:
		dump_demo_ethnic(data, years, percent)
	pass

def dump_demo_separator(years, char='='):
	''' Dump demographics separator '''
	print(char*(years + 1)*8)
	pass

def dump_demo_years(years):
	''' Dump demographics years information '''
	print('\t', end='')
	for year in years:
		print('{:<4}\t'.format(year), end='')
	print('')
	dump_demo_separator(len(years), char='=')
	pass

def dump_demo_fields(data, years, fields, percent=False):
	''' Dump demographics information (for particular fields) '''
	totalAmt = 0
	for field in fields:
		print('{:>4}\t'.format(field), end='')
		for year in years:
			totalAmt = 0
			for field2 in fields:
				if field2 in data[year]:
					totalAmt += int(data[year][field2])
			if percent:
				print('{:>4.1f}%\t'.format(100*float(data[year].get(field, 0))/totalAmt), end='')
			else:
				print('{:>4}\t'.format(data[year].get(field, 0)), end='')
		print('')
	dump_demo_separator(len(years), char='-')
	pass

def dump_demo_gender(data, years, percent=False):
	''' Dump demographics gender information '''
	fields = ['M', 'F']
	dump_demo_fields(data, years, fields, percent)
	pass

def dump_demo_ethnic(data, years, percent=False):
	''' Dump demographics ethnic information '''
	fields = ['B', 'C', 'N', 'O', 'S', 'T', 'U']
	dump_demo_fields(data, years, fields, percent)
	pass

########## INITIALIZE VARIABLES ##########

years = None
percent = False
gender = True
ethnic = True

########## PARSE COMMAND-LINE OPTIONS ##########

args = sys.argv[1:]
while len(args) and args[0].startswith('-') and len(args[0]) > 1:
	arg = args.pop(0)
	if arg == '-h':			# Display years
		usage()
	elif arg == '-y':		# Display years
		years = args.pop(0).split(',')
		years.sort()
	elif arg == '-p':		# Display percentages
		percent = True
	elif arg == '-G':		# Do NOT include gender info
		gender = False
	elif arg == '-E':		# Do NOT include ethnicity info
		ethnic = False
	else:
		usage(1)

if len(args):
	URL = args.pop(0)

data = load_demo_data(URL)		# Dictionary of information
if years == None:
	years = []								# List of years
	for key in data:
		years.append(key)

numYears = len(data)			# Total number of years

########## MAIN EXECUTION ##########

dump_demo_data(data, years, percent, gender, ethnic)
