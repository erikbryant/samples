#
# Copyright Erik Bryant (erikbryantology@gmail.com)
# Gnu All-Permissive http://www.gnu.org/philosophy/license-list.html#GNUAllPermissive
#

CC       = g++ -Wall -Werror -Weffc++ -O3 -D_GLIBCXX_USE_NANOSLEEP
CC_DEBUG = g++ -Wall -Werror -Weffc++ -D_GLIBCXX_DEBUG -g -fprofile-arcs -ftest-coverage -pg
C11      = -std=c++11
THREADS  = -pthread
CPPCHECK = ../cppcheck-1.58/cppcheck

EXECUTABLES = args concurrency prime sieve staticConstructor function tictactoe

.PHONY: all
all: $(EXECUTABLES)

.PHONY: clean
clean:
	rm -f perf.data perf.data.old
	rm -f *.gcov *.gcda *.gcno *.gprof \#*# gmon.out
	rm -f a.out $(EXECUTABLES)

args: args.c++
	$(CPPCHECK) $^
	$(CC_DEBUG) $@.c++ -o $@
	./$@
	gprof $@ gmon.out > $@.gprof
	gcov $@ > /dev/null

concurrency: concurrency.c++
	$(CPPCHECK) $^
	$(CC_DEBUG) $(C11) -D_GLIBCXX_USE_NANOSLEEP $(THREADS) $@.c++ -o $@
	./$@
	gprof $@ gmon.out > $@.gprof
	gcov $@ > /dev/null

function: function.c++
	$(CPPCHECK) $^
	$(CC_DEBUG) $(C11) $@.c++ -o $@
	./$@
	gprof $@ gmon.out > $@.gprof
	gcov $@ > /dev/null

prime: prime.c++
	$(CPPCHECK) $^
	$(CC_DEBUG) $@.c++ -o $@
	./$@
	gprof $@ gmon.out > $@.gprof
	gcov $@ > /dev/null

sieve: sieve.c++
	$(CPPCHECK) $^
	$(CC_DEBUG) $@.c++ -o $@
	./$@
	gprof $@ gmon.out > $@.gprof
	gcov $@ > /dev/null

staticConstructor: staticConstructor.c++
	$(CPPCHECK) $^
	$(CC_DEBUG) $@.c++ -o $@
	./$@
	gprof $@ gmon.out > $@.gprof
	gcov $@ > /dev/null

tictactoe: tictactoe.c++
	$(CPPCHECK) $^
	$(CC_DEBUG) $@.c++ -o $@
	./$@
	gprof $@ gmon.out > $@.gprof
	gcov $@ > /dev/null
