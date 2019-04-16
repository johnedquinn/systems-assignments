test:
	@$(MAKE) -sk test-all

test-all:	test-scripts test-translations

test-scripts:
	curl -sLOk https://gitlab.com/nd-cse-20289-sp19/cse-20289-sp19-assignments/raw/master/reading07/test_translations.sh
	chmod +x test_translations.sh

test-translations:
	./test_translations.sh

