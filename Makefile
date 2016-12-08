#export DESTDIR=include/lcov
#OPTIONS

all: info

info:
	@echo "Available make targets:"
	@echo "  install   : build main program in /src/"
	@echo "  check     : build and run test unit test suite in /test/unit"
	@echo "  coverage  : build tests with coverage option, run lcov, and generate html in /test/unit/lcov_html"

install:
	$(MAKE) -C ./src/  

check: 
	$(MAKE) -C ./test/unit clobber
	$(MAKE)	-C ./test/unit
	$(MAKE) -C ./test/unit check

coverage: lcov
	$(MAKE) -C ./test/unit clobber
	$(MAKE) -C ./test/unit CFLAGS="-O0 -g -Wall --coverage" LDFLAGS="-L$$TACC_GSL_LIB -L$$TACC_GRVY_LIB --coverage"
	$(MAKE) -C ./test/unit check 
	./include/lcov/bin/lcov --capture -d . -o coverage.info
	./include/lcov/bin/genhtml coverage.info -o lcov_html/
	mv coverage.info test/unit/
	mv lcov_html test/unit/
	
lcov:
	$(MAKE)  -C include/lcov install DESTDIR=include/lcov/

love:
	@echo "not war?"

.PHONY: clobber 
clobber: clean 
	$(MAKE) -C ./src/ clobber
	$(MAKE) -C ./test/unit/ clobber

clean: 
	$(MAKE) -C ./test/unit/ clean
	$(MAKE) -C ./src/ clean

