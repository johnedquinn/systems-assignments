#!/bin/sh

#
# File name: caesar.sh
# Author: John Quinn
# Description: This function takes in phrases and encrypts them by "rotating" their characters ...
# ... by a specific amount. This amount can be declared by the user as an integer argument. If no ...
# ... argument, rotates 13. Argument -h for help.
#
# NOTE: SET TABSTOP TO 2 FOR CORRECT INDENTATION.
#

##### FUNCTIONS #####
# Display a "help" message
usage() {
    cat <<EOF
Usage: $(basename $0) [rotation]

This program will read from stdin and rotate the text by the specified
rotation.  If none is specified, then the default value is 13.
EOF
    exit $1
}

# First argument for "tr" command
source_set() {
	echo $LOWERCASE$UPPERCASE
}

# Second argument for "tr" command
target_set() {
	FIRSTLOWER=$(echo $LOWERCASE | cut -b $((${ROT} + 1))-)					# 
	LASTLOWER=$(echo $LOWERCASE | cut -b -${ROT})
	TOTALLOWER=$(echo ${FIRSTLOWER}${LASTLOWER})
	TOTALUPPER=$(echo ${TOTALLOWER} | tr ${LOWERCASE} ${UPPERCASE})
	echo ${TOTALLOWER}${TOTALUPPER}
}


##### PARSE COMMAND-LINE OPTIONS #####
# Display a "help" message
if [ "$1" = "-h" ]
	then
	usage 0
fi

# Determine number of rotations based on arguments
if [ -z "$1" ]
	then
	ROT=13						# Set Rotations to 13 if no argument
	else
	ROT=$(($1 % 26))	# Set Rotations to whatever the user specifies. No need to go above 26, so use modulus.
fi


##### SET VARIABLES #####
LOWERCASE=abcdefghijklmnopqrstuvwxyz
UPPERCASE=ABCDEFGHIJKLMNOPQRSTUVWXYZ


##### FILTER PIPELINE #####
tr $(source_set) $(target_set)

