test:
	@$(MAKE) -sk test-all

test-all:	test-scripts test-demographics test-reddit

test-scripts:
	curl -sLOk https://gitlab.com/nd-cse-20289-sp19/cse-20289-sp19-assignments/raw/master/homework04/test_demographics.sh
	curl -sLOk https://gitlab.com/nd-cse-20289-sp19/cse-20289-sp19-assignments/raw/master/homework04/test_reddit.sh
	chmod +x test_*.sh

test-demographics:
	./test_demographics.sh

test-reddit:
	./test_reddit.sh
