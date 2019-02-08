#!/bin/sh

##### FUNCTIONS #####
usage() {
cat <<EOF
Usage: zipcode.sh

  -c      CITY    Which city to search
  -s      STATE   Which state to search (Indiana)
EOF
	exit $1
}

##### PARSE COMMAND-LINE OPTIONS #####

URL=https://www.zipcodestogo.com/
CITY=ALL
STATE=Indiana

while [ $# -gt 0 ]; do
	case $1 in
		-c) CITY=$2 shift;;
		-s) STATE=$2 shift;;
		-h) usage 1;;
		*) usage 1;;
	esac
	shift
done

##### FILTER PIPELINE #####

#echo "URL with state is: "${URL}${STATE}"/"

STATE=$(echo ${STATE} | sed "s| |%20|")

if [ "${CITY}" = "ALL" ]; then
	curl -sk "${URL}${STATE}/" | grep -Eo '/[0-9]{5}/' | grep -Eo '[0-9]{5}'
else
	curl -sk ${URL}${STATE}"/" | grep "/${CITY}/" | grep -Eo '/[0-9]{5}/' | grep -Eo '[0-9]{5}'
fi
