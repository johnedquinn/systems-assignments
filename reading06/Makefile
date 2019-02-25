test:
	@$(MAKE) -sk test-all

test-all:	test-scripts test-evens_fp test-evens_lc test-evens_gr

test-scripts:
	curl -sLOk https://gitlab.com/nd-cse-20289-sp19/cse-20289-sp19-assignments/raw/master/reading06/test_evens.sh
	chmod +x test_evens.sh

test-evens_fp:
	./test_evens.sh evens_fp.py

test-evens_lc:
	./test_evens.sh evens_lc.py

test-evens_gr:
	./test_evens.sh evens_gr.py
