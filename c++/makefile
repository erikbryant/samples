#
# Copyright Erik Bryant (erikbryantology@gmail.com)
# Gnu All-Permissive http://www.gnu.org/philosophy/license-list.html#GNUAllPermissive
#

CC       = g++ -Wall -Werror -Weffc++ -O3 -D_GLIBCXX_USE_NANOSLEEP
CC_DEBUG = g++ -Wall -Werror -Weffc++ -D_GLIBCXX_DEBUG -g -fprofile-arcs -ftest-coverage -pg
C11      = -std=c++11
THREADS  = -pthread

EXECUTABLES = args concurrency prime sieve staticConstructor function tictactoe boygirl hash STL interview01 \
	sorts

all: $(EXECUTABLES)

clean:
	rm -f a.out $(EXECUTABLES)
	rm -rf *.dSYM

args: args.cc
	$(CC_DEBUG) $@.cc -o $@

concurrency: concurrency.cc
	$(CC_DEBUG) $(C11) -D_GLIBCXX_USE_NANOSLEEP $(THREADS) $@.cc -o $@

function: function.cc
	$(CC_DEBUG) $(C11) $@.cc -o $@

prime: prime.cc
	$(CC_DEBUG) $@.cc -o $@

sieve: sieve.cc
	$(CC_DEBUG) $@.cc -o $@

staticConstructor: staticConstructor.cc
	$(CC_DEBUG) $@.cc -o $@

tictactoe: tictactoe.cc
	$(CC_DEBUG) $@.cc -o $@

boygirl: boygirl.cc
	$(CC_DEBUG) $@.cc -o $@

hash: hash.cc
	$(CC_DEBUG) $@.cc -o $@

STL: STL.cc
	$(CC_DEBUG) $@.cc -o $@

interview01: interview01.cc
	$(CC_DEBUG) $@.cc -o $@

sorts: sorts.cc
	$(CC_DEBUG) $@.cc -o $@

.PHONY: all clean
