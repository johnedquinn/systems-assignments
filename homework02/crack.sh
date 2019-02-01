#!/bin/bash

# Check if there are no arguments
if [ $# -eq 0 ]
then
	echo "Usage: crack.sh executable"
	exit 1
fi

# Check if there is more than 1 argument
if [ ! $# -eq 1 ]
then
	echo "ERROR: Inappropriate number of arguments"
	exit 1
fi

# Check if argument is readable
if [ ! -r $1 ]
then
	echo $1 " is not readable !"
	exit 1
fi

# Check if argument is executable
if [ ! -x $1 ]
then
	echo $1 " is not executable ! "
	exit 1
fi

FoundPassword=1

for i in $(strings $1)
do
	if [ $($1 $i) ]
	then
		echo "Password is $i"
		echo "Token    is $($1 $i)"
		FoundPassword=0
	fi
done

if [ $FoundPassword -eq 1 ]
then
	echo "Unable to crack uncrackable"
	exit 1
fi
