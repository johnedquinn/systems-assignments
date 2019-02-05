test:
	@$(MAKE) -sk test-all

test-all:	test-scripts test-caesar test-broify test-zipcode

test-scripts:
	curl -sLOk https://gitlab.com/nd-cse-20289-sp19/cse-20289-sp19-assignments/raw/master/homework03/test_caesar.sh
	curl -sLOk https://gitlab.com/nd-cse-20289-sp19/cse-20289-sp19-assignments/raw/master/homework03/test_broify.sh
	curl -sLOk https://gitlab.com/nd-cse-20289-sp19/cse-20289-sp19-assignments/raw/master/homework03/test_zipcode.sh
	chmod +x test_*.sh

test-caesar:
	./test_caesar.sh

test-broify:
	./test_broify.sh

test-zipcode:
	./test_zipcode.sh
