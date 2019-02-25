#!/usr/bin/env python3

import os
import sys
import pprint
import requests

# Globals

URL      = None
ISGD_URL = 'http://is.gd/create.php'

# Functions

def usage(status=0):
    ''' Display usage information and exit with specified status '''
    print('''Usage: {} [options] URL_OR_SUBREDDIT

    -s          Shorten URLs using (default: False)
    -n LIMIT    Number of articles to display (default: 10)
    -o ORDERBY  Field to sort articles by (default: score)
    -t TITLELEN Truncate title to specified length (default: 60)
    '''.format(os.path.basename(sys.argv[0])))
    sys.exit(status)

def load_reddit_data(url=URL):
	''' Load reddit data from specified URL into dictionary '''
	headers = { 'user-agent' : 'reddit-{}'.format(os.environ.get('USER', 'cse-20289-sp19')) }
	response = requests.get(URL, headers=headers)
	data = response.json()
	children = data['data']['children']
	return children

def dump_reddit_data(data, limit=10, orderby='score', titlelen=60, shorten=False):
	''' Dump reddit data based on specified attributes '''
	if orderby == 'score':
		data = sorted(data, key=lambda c: c['data'][orderby], reverse=True)
	else:
		data = sorted(data, key=lambda c: c['data'][orderby], reverse=False)
	for index, child in enumerate(data[:limit], 1):
		if index > 1:
			print()
		title = child['data']['title'][:titlelen]
		score = child['data']['score']
		url = child['data']['url']
		if shorten:
			url = shorten_url(url)
		print('{:4}.\t{} (Score: {})'.format(index, title, score))
		print('\t{}'.format(url))
	pass

def shorten_url(url):
	''' Shorten URL using yld.me '''
	url = requests.get(ISGD_URL, params={'format': 'json', 'url': url})
	url = url.json()
	url = url['shorturl']
	return url

##### VARIABLES #####

SHORTEN = False
LIMIT = 10
ORDERBY = 'score'
TITLELEN = 60

##### PARSE COMMAND-LINE OPTIONS #####

args = sys.argv[1:]
while len(args) and args[0].startswith('-') and len(args[0]) > 1:
	arg = args.pop(0)
	if arg == "-h":
		usage(0)
	elif arg == "-s":
		SHORTEN = True
	elif arg == "-n":
		LIMIT = int(args.pop(0))
	elif arg == "-o":
		ORDERBY = args.pop(0)
	elif arg == "-t":
		TITLELEN = int(args.pop(0))
	else:
		usage(1)

if len(args):
	URL = args.pop(0)
else:
	usage(1)

if URL.startswith('https') == False:
	URL = r'https://www.reddit.com/r/' + URL + r'/.json'

# Main Execution

DATA = load_reddit_data(URL)
dump_reddit_data(DATA, limit=LIMIT, orderby=ORDERBY, titlelen=TITLELEN, shorten=SHORTEN)
