
# File name: Makefile
# Author: John Quinn

########## VARIABLES ##########

CC = gcc
CFLAGS = -Wall -std=gnu99 -g -Iinclude
LD = gcc
LDFLAGS = -Llib
AR = ar
ARFLAGS = rcs
TARGETS = bin/freq

########## MAKE ALL ##########

all: $(TARGETS)

%.o: %.c
	$(CC) -c $(CFLAGS) -o $@ $^

lib/libmap.a: src/entry.o src/fnv.o src/map.o
	$(AR) $(ARFLAGS) $@ $^

bin/unit_entry: tests/unit_entry.o lib/libmap.a
	$(LD) $(LDFLAGS) -o $@ $^

bin/unit_fnv: tests/unit_fnv.o lib/libmap.a
	$(LD) $(LDFLAGS) -o $@ $^

bin/unit_map: tests/unit_map.o lib/libmap.a
	$(LD) $(LDFLAGS) -o $@ $^

bin/freq: src/freq.o lib/libmap.a
	$(LD) $(LDFLAGS) -o $@ $^

bin/measure: src/measure.o lib/libmap.a
	$(LD) $(LDFLAGS) -o $@ $^

########## MAKE TEST ##########

test: test-entry test-fnv test-map test-freq

test-entry:	bin/unit_entry
	@bin/test_entry.sh

test-fnv:	bin/unit_fnv
	@bin/test_fnv.sh

test-map:	bin/unit_map
	@bin/test_map.sh

test-freq:	bin/test_freq.sh bin/freq
	@bin/test_freq.sh

benchmark:	bin/measure bin/freq bin/benchmark.py
	@echo Benchmarking
	@./bin/benchmark.py

clean:
	@echo Cleaning...
	@rm -f $(TARGETS) bin/unit_entry bin/unit_fnv bin/unit_map bin/measure lib/*.a src/*.o tests/*.o *.log *.input

.PHONY:		all test benchmark clean
