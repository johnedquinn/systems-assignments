test:
	@$(MAKE) -sk test-all

test-all:	test-scripts test-filters

test-scripts:
	curl -sLOk https://gitlab.com/nd-cse-20289-sp19/cse-20289-sp19-assignments/raw/master/exam01/test_filters.sh
	chmod +x test_filters.sh

test-filters:
	./test_filters.sh
