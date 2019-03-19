CC = gcc
CFLAGS = -g -Wall -std=gnu99
TARGETS = sort grep

all: $(TARGETS)

test:
	@$(MAKE) -sk test-all

test-all:	test-sort test-grep

test-sort:	sort
	curl -sLOk https://gitlab.com/nd-cse-20289-sp19/cse-20289-sp19-assignments/raw/master/reading08/test_sort.sh
	chmod +x test_sort.sh
	./test_sort.sh

test-grep:	grep
	curl -sLOk https://gitlab.com/nd-cse-20289-sp19/cse-20289-sp19-assignments/raw/master/reading08/test_grep.sh
	chmod +x test_grep.sh
	./test_grep.sh

sort:
	$(CC) $(CFLAGS) -o sort sort.c

grep:
	$(CC) $(CFLAGS) -o grep grep.c

clean:
	rm -f $(TARGETS)

.SUFFIXES:
