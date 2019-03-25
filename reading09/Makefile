CC = gcc
CFLAGS = -g -Wall -std=gnu99
TARGETS = str_title

all: $(TARGETS)

str_title: str_title.c
	$(CC) $(CFLAGS) -o $@ $<

test:
	@$(MAKE) -sk test-all

test-all:	test-str_title

test-str_title:	str_title
	curl -sLOk https://gitlab.com/nd-cse-20289-sp19/cse-20289-sp19-assignments/raw/master/reading09/test_str_title.sh
	chmod +x test_str_title.sh
	./test_str_title.sh

clean:
	rm -f $(TARGETS)

.SUFFIXES:
