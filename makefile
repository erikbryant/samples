CC       = g++ $(C11) -Wall -Werror -Weffc++ -O3 -D_GLIBCXX_USE_NANOSLEEP
CC_DEBUG = g++ $(C11) -Wall -Werror -Weffc++ -D_GLIBCXX_DEBUG -g -fprofile-arcs -ftest-coverage -pg
C11      = -std=c++11
THREADS  = -pthread
CPPCHECK = ../cppcheck-1.58/cppcheck

EXECUTABLES = concurrency staticConstructor

.PHONY: all
all: $(EXECUTABLES)

.PHONY: clean
clean:
	rm -f perf.data perf.data.old
	rm -f *.gcov *.gcda *.gcno *.gprof \#*# gmon.out
	rm -f a.out $(EXECUTABLES)

concurrency: concurrency.c++
	$(CPPCHECK) $^
	$(CC_DEBUG) -D_GLIBCXX_USE_NANOSLEEP $(THREADS) $@.c++ -o $@
	./$@
	gprof $@ gmon.out > $@.gprof
	gcov $@ > /dev/null

staticConstructor: staticConstructor.c++
	$(CPPCHECK) $^
	$(CC_DEBUG) $@.c++ -o $@
	./$@
	gprof $@ gmon.out > $@.gprof
	gcov $@ > /dev/null
