CC=		gcc
CFLAGS=		-g -Wall -Werror -std=gnu99 -Iinclude
LD=		gcc
LDFLAGS=	-Llib
TARGETS=	bin/search

all:		$(TARGETS)

test:		
	@$(MAKE) -sk test-all

test-all:	test-search

test-search:	bin/search
	@curl -sLk https://gitlab.com/nd-cse-20289-sp19/cse-20289-sp19-assignments/raw/master/homework08/test_search.sh > bin/test_search.sh
	@chmod +x bin/test_search.sh
	@./bin/test_search.sh

clean:
	@echo Cleaning...
	@rm -f $(TARGETS) src/*.o

.SUFFIXES:

# TODO: Rules for bin/search and intermediate object files
