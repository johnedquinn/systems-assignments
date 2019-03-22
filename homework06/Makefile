CC = gcc
CFLAGS = -g -Wall -std=gnu99
LD = gcc
LDFLAGS = -L.
AR = ar
ARFLAGS = rcs

TARGETS = str-static str-dynamic libstr.a libstr.so

#all: $(TARGETS)


########## MAKE TEST ##########
test:		
	@$(MAKE) -sk test-all
	
test-all: test-libstr test-str

test-libstr: libstr.so
	curl -sLOk https://gitlab.com/nd-cse-20289-sp19/cse-20289-sp19-assignments/raw/master/homework06/test_libstr.py
	chmod +x test_libstr.py
	./test_libstr.py -v

test-str:	str-static str-dynamic
	curl -sLOk https://gitlab.com/nd-cse-20289-sp19/cse-20289-sp19-assignments/raw/master/homework06/test_str.sh
	chmod +x test_str.sh
	./test_str.sh

########## MAKE CLEAN ##########
clean:
	rm -f $(TARGETS) *.o libstr.*

########## MAKE (LIBRARIES) ##########

all: $(TARGETS)

str-static: main.o libstr.a
	$(CC) $(LDFLAGS) -static -o $@ $< -lstr
	
str-dynamic: main.o libstr.so
	$(CC) $(LDFLAGS) -o $@ $< -lstr

libstr.a: library.o
	$(AR) $(ARFLAGS) $@ $<

libstr.so: library.o
	$(CC) -shared -o $@ $<

library.o: library.c str.h
	$(CC) $(CFLAGS) -fPIC -c -o $@ $<

main.o: main.c str.h
	$(CC) $(CFLAGS) -c -o $@ $<

