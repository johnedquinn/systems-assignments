CC=             gcc
CFLAGS=         -g -Wall -Werror -std=gnu99
TARGETS=        ncat

all:            $(TARGETS)

test:
	        @$(MAKE) -sk test-all

test-all:	test-ncat

test-ncat:	ncat
	curl -sLOk https://gitlab.com/nd-cse-20289-sp19/cse-20289-sp19-assignments/raw/master/reading12/test_ncat.sh
	chmod +x test_ncat.sh
	./test_ncat.sh

clean:
	rm -f $(TARGETS)

.SUFFIXES:

ncat: ncat.c
	$(CC) $(CFLAGS) -o $@ $^
