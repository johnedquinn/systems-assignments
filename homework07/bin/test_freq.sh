#!/bin/bash

FREQ=bin/freq
WORKSPACE=/tmp/freq.$(id -u)
FAILURES=0

export LC_ALL=C # Use POSIX locale

# Functions

error() {
    echo "$@"
    [ -s $WORKSPACE/test ] && (echo; cat $WORKSPACE/test; echo)
    FAILURES=$((FAILURES + 1))
}

cleanup() {
    STATUS=${1:-$FAILURES}
    rm -fr $WORKSPACE
    exit $STATUS
}

input() {
    cat <<EOF
I stay out too late, got nothing in my brain
That's what people say, that's what people say
I go on too many dates, but I can't make them stay
At least that's what people say, that's what people say
But I keep cruising
Can't stop, won't stop moving
It's like I got this music in my mind
Saying it's gonna be alright
Cause the players gonna play, play, play, play, play
And the haters gonna hate, hate, hate, hate, hate
Baby, I'm just gonna shake, shake, shake, shake, shake
I shake it off, I shake it off
Heartbreakers gonna break, break, break, break, break
And the fakers gonna fake, fake, fake, fake, fake
Baby, I'm just gonna shake, shake, shake, shake, shake
I shake it off, I shake it off
I never miss a beat, I'm lightning on my feet
And that's what they don’t see, that's what they don’t see
I'm dancing on my own, I make the moves up as I go
And that's what they don't know, that’s what they don’t know
But I keep cruising
Can't stop, won't stop grooving
It's like I got this music in my mind
Saying it's gonna be alright
Cause the players gonna play, play, play, play, play
And the haters gonna hate, hate, hate, hate, hate
Baby, I'm just gonna shake, shake, shake, shake, shake
I shake it off, I shake it off
Heartbreakers gonna break, break, break, break, break
And the fakers gonna fake, fake, fake, fake, fake
Baby, I'm just gonna shake, shake, shake, shake, shake
I shake it off, I shake it off
I, I shake it off, I shake it off
I, I shake it off, I shake it off
I, I shake it off, I shake it off
I, I shake it off, I shake it off
I, I shake it off, I shake it off
I, I shake it off, I shake it off
I, I shake it off, I shake it off
I, I shake it off, I shake it off
Hey, hey, hey!
Just think while you've been getting down and out about the liars
And dirty, dirty cheats of the world you could've been getting down to this sick beat
My ex-man brought his new girlfriend
She's like, “oh my God”, but I'm just gonna shake
And to the fella over there with the hella good hair
Won't you come on over, baby, we can shake, shake, shake
Cause the players gonna play, play, play, play, play
And the haters gonna hate, hate, hate, hate, hate
Baby, I'm just gonna shake, shake, shake, shake, shake
I shake it off, I shake it off
Heartbreakers gonna break, break, break, break, break
And the fakers gonna fake, fake, fake, fake, fake
Baby, I'm just gonna shake, shake, shake, shake, shake
I shake it off, I shake it off
I, I shake it off, I shake it off
I, I shake it off, I shake it off
I, I shake it off, I shake it off
I, I shake it off, I shake it off
I, I shake it off, I shake it off
I, I shake it off, I shake it off
I, I shake it off, I shake it off
I, I shake it off, I shake it off
EOF
}

output() {
    cat <<EOF
54	I
52	shake
44	it
26	shake,
22	off,
22	off
21	gonna
16	I,
14	the
12	play,
12	hate,
12	fake,
12	break,
10	And
9	I'm
8	what
7	just
6	that's
6	my
6	Baby,
4	they
4	people
4	on
3	this
3	players
3	play
3	in
3	haters
3	hate
3	got
3	fakers
3	fake
3	don’t
3	break
3	Heartbreakers
3	Cause
2	you
2	won't
2	too
2	to
2	stop,
2	stop
2	stay
2	say,
2	say
2	out
2	music
2	mind
2	make
2	like
2	keep
2	it's
2	go
2	getting
2	down
2	cruising
2	but
2	been
2	be
2	alright
2	Saying
2	It's
2	Can't
2	But
1	“oh
1	you've
1	world
1	with
1	while
1	we
1	up
1	think
1	there
1	them
1	that’s
1	sick
1	see,
1	see
1	own,
1	over,
1	over
1	of
1	nothing
1	new
1	never
1	moving
1	moves
1	miss
1	many
1	like,
1	lightning
1	liars
1	least
1	late,
1	know,
1	know
1	his
1	hey,
1	hey!
1	hella
1	hair
1	grooving
1	good
1	girlfriend
1	fella
1	feet
1	ex-man
1	don't
1	dirty,
1	dirty
1	dates,
1	dancing
1	could've
1	come
1	cheats
1	can't
1	can
1	brought
1	brain
1	beat,
1	beat
1	baby,
1	as
1	and
1	about
1	a
1	Won't
1	That's
1	She's
1	My
1	Just
1	Hey,
1	God”,
1	At
EOF
}

# Main Execution

export LD_LIBRARY_PATH=$LD_LIBRRARY_PATH:.

mkdir $WORKSPACE

trap "cleanup" EXIT
trap "cleanup 1" INT TERM

echo
echo "Testing freq..."

if [ ! -x $FREQ ]; then
    echo "Failure: $FREQ is not executable!"
    exit 1
fi

printf " %-40s ... " "freq -h"
$FREQ -h < /dev/null 2>&1 | grep -q -i 'usage' &> $WORKSPACE/test
if [ $? -ne 0 ]; then
    cat > $WORKSPACE/test <<EOF
FAILURE: You kept cruising, didn't stop and inform about using. Shake it off!"
REASON:  Didn't display usage message
EOF
    error "Failure"
else
    echo "Success"
fi

printf " %-40s ... " "freq"
diff -y <(input | $FREQ | sort -rn) <(output) &> $WORKSPACE/test
if [ $? -ne 0 ]; then
    error "Failure"
    echo "FAILURE: Probably stayed out too late and got nothing in your brain. Shake it off!"
    echo "REASON:  Output doesn't match"
    echo
else
    echo "Success"
fi

printf " %-40s ... " "freq (valgrind)"
input | valgrind --leak-check=full $FREQ &> $WORKSPACE/test
if [ $? -ne 0 ] || [ $(awk '/ERROR SUMMARY:/ {print $4}' $WORKSPACE/test) -ne 0 ]; then
    error "Failure"
    echo "FAILURE: They'll tell you I'm insane, But I've got a blank space, baby"
    echo "REASON:  Memory error"
    echo
else
    echo "Success"
fi

printf " %-40s ... " "freq -f KEY"
diff -y <(input | $FREQ -f KEY | sort) <(output | awk '{print $2}' | sort) &> $WORKSPACE/test
if [ $? -ne 0 ]; then
    error "Failure"
    echo "FAILURE: Heartbreakers gonna break, break, break, break, break. Shake it off!"
    echo "REASON:  Doesn't handle -f KEY properly"
    echo
else
    echo "Success"
fi

printf " %-40s ... " "freq -f KEY (valgrind)"
input | valgrind --leak-check=full $FREQ -f KEY &> $WORKSPACE/test
if [ $? -ne 0 ] || [ $(awk '/ERROR SUMMARY:/ {print $4}' $WORKSPACE/test) -ne 0 ]; then
    error "Failure"
    echo "FAILURE: You can tell me when it's over, If the high was worth the pain"
    echo "REASON:  Memory error"
    echo
else
    echo "Success"
fi

printf " %-40s ... " "freq -f KEY_VALUE"
diff -y <(input | $FREQ -f KEY_VALUE | sort) <(output | awk '{printf "%s\t%d\n", $2, $1}' | sort) &> $WORKSPACE/test
if [ $? -ne 0 ]; then
    error "Failure"
    echo "FAILURE: Cause the players gonna play, play, play, play, play. Shake it off!"
    echo "REASON:  Doesn't handle -f KEY_VALUE properly"
    echo
else
    echo "Success"
fi

printf " %-40s ... " "freq -f KEY_VALUE (valgrind)"
input | valgrind --leak-check=full $FREQ -f KEY_VALUE &> $WORKSPACE/test
if [ $? -ne 0 ] || [ $(awk '/ERROR SUMMARY:/ {print $4}' $WORKSPACE/test) -ne 0 ]; then
    error "Failure"
    echo "FAILURE: So it's gonna be forever, Or it's gonna go down in flames"
    echo "REASON:  Memory error"
    echo
else
    echo "Success"
fi

printf " %-40s ... " "freq -f VALUE"
diff -y <(input | $FREQ -f VALUE | sort) <(output | awk '{print $1}' | sort) &> $WORKSPACE/test
if [ $? -ne 0 ]; then
    error "Failure"
    echo "FAILURE: And the haters gonna hate, hate, hate, hate, hate. Shake it off!"
    echo "REASON:  Doesn't handle -f VALUE properly"
    echo
else
    echo "Success"
fi

printf " %-40s ... " "freq -f VALUE (valgrind)"
input | valgrind --leak-check=full $FREQ -f VALUE &> $WORKSPACE/test
if [ $? -ne 0 ] || [ $(awk '/ERROR SUMMARY:/ {print $4}' $WORKSPACE/test) -ne 0 ]; then
    error "Failure"
    echo "FAILURE: 'Cause we're young and we're reckless, We'll take this way too far"
    echo "REASON:  Memory error"
    echo
else
    echo "Success"
fi

printf " %-40s ... " "freq -f VALUE_KEY"
diff -y <(input | $FREQ -f VALUE_KEY | sort -rn) <(output | sort -rn) &> $WORKSPACE/test
if [ $? -ne 0 ]; then
    error "Failure"
    echo "FAILURE: And the fakers gonna fake, fake, fake, fake, fake. Shake it off!"
    echo "REASON:  Doesn't handle -f VALUE_KEY properly"
    echo
else
    echo "Success"
fi

printf " %-40s ... " "freq -f VALUE_KEY (valgrind)"
input | valgrind --leak-check=full $FREQ -f VALUE_KEY &> $WORKSPACE/test
if [ $? -ne 0 ] || [ $(awk '/ERROR SUMMARY:/ {print $4}' $WORKSPACE/test) -ne 0 ]; then
    error "Failure"
    echo "FAILURE: It'll leave you breathless, Or with a nasty scar"
    echo "REASON:  Memory error"
    echo
else
    echo "Success"
fi

TESTS=$(($(grep -c Success $0) - 1))
echo "   Score $(echo "scale=4; ($TESTS - $FAILURES) / $TESTS.0 * 1.5" | bc | awk '{ printf "%0.2f\n", $1 }' )"
