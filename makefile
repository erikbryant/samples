#
# Copyright Erik Bryant (erikbryantology@gmail.com)
# Gnu All-Permissive http://www.gnu.org/philosophy/license-list.html#GNUAllPermissive
#

CC       = g++ -Wall -Werror -Weffc++ -O3 -D_GLIBCXX_USE_NANOSLEEP
CC_DEBUG = g++ -Wall -Werror -Weffc++ -D_GLIBCXX_DEBUG -g -fprofile-arcs -ftest-coverage -pg
C11      = -std=c++11
THREADS  = -pthread
CPPCHECK = ../cppcheck-1.58/cppcheck

EXECUTABLES = args concurrency prime sieve staticConstructor function tictactoe boygirl hash STL asana

.PHONY: all
all: $(EXECUTABLES)

.PHONY: clean
clean:
	rm -f perf.data perf.data.old
	rm -f *.gcov *.gcda *.gcno *.gprof \#*# gmon.out
	rm -f a.out $(EXECUTABLES)

args: args.cc
	$(CPPCHECK) $^
	$(CC_DEBUG) $@.cc -o $@
	./$@
	gprof $@ gmon.out > $@.gprof
	gcov $@ > /dev/null

concurrency: concurrency.cc
	$(CPPCHECK) $^
	$(CC_DEBUG) $(C11) -D_GLIBCXX_USE_NANOSLEEP $(THREADS) $@.cc -o $@
	./$@
	gprof $@ gmon.out > $@.gprof
	gcov $@ > /dev/null

function: function.cc
	$(CPPCHECK) $^
	$(CC_DEBUG) $(C11) $@.cc -o $@
	./$@
	gprof $@ gmon.out > $@.gprof
	gcov $@ > /dev/null

prime: prime.cc
	$(CPPCHECK) $^
	$(CC_DEBUG) $@.cc -o $@
	./$@
	gprof $@ gmon.out > $@.gprof
	gcov $@ > /dev/null

sieve: sieve.cc
	$(CPPCHECK) $^
	$(CC_DEBUG) $@.cc -o $@
	./$@
	gprof $@ gmon.out > $@.gprof
	gcov $@ > /dev/null

staticConstructor: staticConstructor.cc
	$(CPPCHECK) $^
	$(CC_DEBUG) $@.cc -o $@
	./$@
	gprof $@ gmon.out > $@.gprof
	gcov $@ > /dev/null

tictactoe: tictactoe.cc
	$(CPPCHECK) $^
	$(CC_DEBUG) $@.cc -o $@
	./$@
	gprof $@ gmon.out > $@.gprof
	gcov $@ > /dev/null

boygirl: boygirl.cc
	$(CPPCHECK) $^
	$(CC_DEBUG) $@.cc -o $@
	./$@
	gprof $@ gmon.out > $@.gprof
	gcov $@ > /dev/null

hash: hash.cc
	$(CPPCHECK) $^
	$(CC_DEBUG) $@.cc -o $@
	./$@
	gprof $@ gmon.out > $@.gprof
	gcov $@ > /dev/null

STL: STL.cc
	$(CPPCHECK) $^
	$(CC_DEBUG) $@.cc -o $@
	./$@
	gprof $@ gmon.out > $@.gprof
	gcov $@ > /dev/null

asana: asana.cc
	$(CPPCHECK) $^
	$(CC_DEBUG) $@.cc -o $@
	./$@
	gprof $@ gmon.out > $@.gprof
	gcov $@ > /dev/null

