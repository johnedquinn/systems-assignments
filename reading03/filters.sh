#!/bin/bash

q1_answer() {
    # TODO: Complete pipeline
		echo "All your base are belong to us" | tr [a-z] [A-Z]
}

q2_answer() {
    # TODO: Complete pipeline
		echo "monkeys love bananas" | sed 's/monkeys/gorillaz/g'
}

q3_answer() {
    # TODO: Complete pipeline
    echo "     monkeys love bananas" | sed 's/^ *//g'
}

q4_answer() {
    # TODO: Complete pipeline
		curl -sLk https://yld.me/raw/yWh | grep "root" | awk -F ':' '{ if($1 == "root") print $7}'
}

q5_answer() {
    # TODO: Complete pipeline
		curl -sLk https://yld.me/raw/yWh | sed 's+/bin/bash+/usr/bin/python+g; s+/bin/csh+/usr/bin/python+g; s+/bin/tcsh+/usr/bin/python+g' | grep python
}

q6_answer() {
    # TODO: Complete pipeline
		curl -sLk https://yld.me/raw/yWh | awk -F ":" '(($3~/^4/)&&($3~/7$/))||(($4~/^4/)&&($4~/7$/))'
}
