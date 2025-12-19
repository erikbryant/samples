% Factorial
% https://www.swi-prolog.org/pldoc/man?section=clpfd-factorial

:- use_module(library(clpfd)).

n_factorial(0, 1).
n_factorial(N, F) :-
        N #> 0,
        F #> 0,
        N1 #= N - 1,
        F #= N * F1,
        n_factorial(N1, F1).
