test:
	@$(MAKE) -sk test-all

test-all:	test-scripts test-extract test-crack

test-scripts:
	curl -sLOk https://gitlab.com/nd-cse-20289-sp19/cse-20289-sp19-assignments/raw/master/homework02/test_extract.sh
	curl -sLOk https://gitlab.com/nd-cse-20289-sp19/cse-20289-sp19-assignments/raw/master/homework02/test_crack.sh
	chmod +x test_extract.sh
	chmod +x test_crack.sh

test-extract:
	./test_extract.sh

test-crack:
	./test_crack.sh
