#!/bin/bash

q1_answer() {
	# TODO: List only the names of the turtles in sorted order.
	curl -sLk https://yld.me/raw/lE8 | cut -d ":" -f 1 | sort
}

q2_answer() {
	# TODO: List only the colors of the turtles in all capitals.
	curl -sLk https://yld.me/raw/lE8 | cut -d ":" -f 2 | tr [a-z] [A-Z]
}

q3_answer() {
	# TODO: Replace all weapons with plowshares
	curl -sLk https://yld.me/raw/lE8 | sed 's|:[a-z]*$|:plowshare|g'
}

q4_answer() {
	# TODO: List only the turtles whose names end in lo.
	curl -sLk https://yld.me/raw/lE8 | cut -d ":" -f 1 | grep lo$
}

q5_answer() {
	# TODO: List only the turtles with names that have two consecutive vowels.
	curl -sLk https://yld.me/raw/lE8 | cut -d ":" -f 1 | grep '[aeiou][aeiou]'
}

q6_answer() {
	# TODO: Count how many colors don't begin with a vowel
	curl -sLk https://yld.me/raw/lE8 | cut -d ":" -f 2 | grep -c -v "^[aeiou]"
}

q7_answer() {
	# TODO: List only the turtles names whose name ends with a vowel and whose weapon ends with a vowel.
	curl -sLk https://yld.me/raw/lE8 | grep "[aeiou]$" | cut -d ":" -f 1 | grep "[aeiou]$"
}

q8_answer() {
	# TODO: List only the turtles names with two of the same consecutive letter (i.e. aa, bb, etc.)
	curl -sLk https://yld.me/raw/lE8 | grep "^.*\([a-z]\)\1.*:.*:.*$" | cut -d ":" -f 2
}
