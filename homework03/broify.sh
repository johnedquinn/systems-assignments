#!/bin/sh

#
# File name: broify.sh
# Author: John Quinn
# Description: XXXXXXXXXXXXXXXXXXXXXXXXXX
#
# NOTE: SET TABSTOP TO 2 FOR CORRECT INDENTATION.
#

##### FUNCTIONS #####

usage() {
cat << EOF
Usage: broify.sh

  -d DELIM    Use this as the comment delimiter.
  -W          Don't strip empty lines.
EOF
	exit $1
}


##### PARSE COMMAND-LINE OPTIONS #####

BOOL='#'
DELIM='#'

while [ $# -gt 0 ]; do
    case $1 in
    	-h)
				usage 1
				;;
			-d)
				DELIM=$2
				shift
				;;
			-W)
				BOOL='W'
				;;
			*)
				usage 1
				;;
    esac
    shift
done


##### FILTER PIPELINE #####

if [ "${BOOL}" == 'W' ];
	then
	sed -e "s|${DELIM}.*$||g" | sed -r 's|\s*$||'
	else
	sed -e "s|${DELIM}.*$||g" | sed -r '/^\s*$/d' | sed -r 's|\s*$||g'
fi

