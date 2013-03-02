CC       = g++ $(C11) -Wall -Werror -Weffc++ -O3 -D_GLIBCXX_USE_NANOSLEEP
CC_DEBUG = g++ $(C11) -Wall -Werror -Weffc++ -D_GLIBCXX_DEBUG -g -fprofile-arcs -ftest-coverage -pg
C11      = -std=c++11
CPPCHECK = ../cppcheck-1.58/cppcheck

.PHONY: all
all: concurrency

.PHONY: clean
clean:
	rm -f perf.data perf.data.old
	rm -f *.gcov *.gcda *.gcno *.gprof \#*# gmon.out

concurrency: concurrency.c++
	$(CPPCHECK) $^
	$(CC_DEBUG) -D_GLIBCXX_USE_NANOSLEEP -pthread $@.c++ -o $@
	./$@
	gprof $@ gmon.out > $@.gprof
	gcov $@ > /dev/null
