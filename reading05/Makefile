test:
	@$(MAKE) -sk test-all

test-all:	test-scripts test-exists test-head test-sort

test-scripts:
	curl -sLOk https://gitlab.com/nd-cse-20289-sp19/cse-20289-sp19-assignments/raw/master/reading05/test_exists.sh
	curl -sLOk https://gitlab.com/nd-cse-20289-sp19/cse-20289-sp19-assignments/raw/master/reading05/test_head.sh
	curl -sLOk https://gitlab.com/nd-cse-20289-sp19/cse-20289-sp19-assignments/raw/master/reading05/test_sort.sh
	chmod +x test_*.sh

test-exists:
	./test_exists.sh

test-head:
	./test_head.sh

test-sort:
	./test_sort.sh
