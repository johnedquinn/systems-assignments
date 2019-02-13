#!/bin/bash

q1_answer() {
	# TODO: List only the last five first names in sorted order
	curl -sLk https://yld.me/raw/Hk1 | cut -d "," -f 3 | sort | tail -n 5
}

q2_answer() {
	# TODO: Count how many phone numbers end in an odd number
	curl -sLk https://yld.me/raw/Hk1 | cut -d "," -f 4 | grep "[13579]$" | wc -l
}

q3_answer() {
	# TODO: List the last names that contain at at least two of the same vowels
	curl -sLk https://yld.me/raw/Hk1 | cut -d "," -f 2 | grep -E "([aeiou]).*\1"
}

q4_answer() {
	# TODO: Count all the netids that are exactly 8 characters long
	curl -sLk https://yld.me/raw/Hk1 | cut -d "," -f 1 | grep -E ".{8}" | wc -l
}

q5_answer() {
	# TODO: List all the netids that contain all of the last name
	curl -sLk https://yld.me/raw/Hk1 | cut -d "," -f 1,2 | tr A-Z a-z | grep -E ".*([^,]+),\1$" | cut -d "," -f 1
}

q6_answer() {
	# TODO: List the first names of people who have both two consecutive
	# repeated letters in their netid and two consecutive repeated numbers in
	# their phone number
	curl -sLk https://yld.me/raw/Hk1 | cut -d "," -f 1,3,4 | grep -E ".*(.)\1[^,]*,[^,]+,.*(.)\2.*" | cut -d "," -f 2
}
