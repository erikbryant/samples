:- use_module(library(clpfd)).

lenHelper([_|T],A,L) :-
  Anew is A + 1,
  lenHelper(T,Anew,L).
lenHelper([],A,A).
len(List, Length) :- lenHelper(List, 0, Length).

add2(X,Y,R) :- R #= X+Y.
mul2(X,Y,R) :- R #= X*Y.

add(L,Z) :- foldl(add2, L, 0, Z).
mul(L,Z) :- foldl(mul2, L, 1, Z).
sub(X,Y,Z) :- X-Y #= Z; Y-X #= Z.
div(X,Y,Z) :- X//Y #= Z; Y//X #= Z.

keen(Rows) :-
    len(Rows, L),
    length(Rows, L), maplist(same_length(Rows), Rows),
    append(Rows, Vs), Vs ins 1..L,
    maplist(all_distinct, Rows),
    transpose(Rows, Columns),
    maplist(all_distinct, Columns).

board5h(Rows) :-
    Rows = [[A1,A2,A3,B1,C1],
            [D1,D2,E1,B2,C2],
            [F1,G1,E2,E3,E4],
            [F2,G2,H1,I1,J1],
            [K1,K2,H2,I2,J2]],
    mul([A1,A2,A3],10),
    sub(B1,B2,2),
    add([C1,C2],5),
    add([D1,D2],7),
    mul([E1,E2,E3,E4],24),
    mul([F1,F2],10),
    sub(G1,G2,2),
    sub(H1,H2,1),
    div(I1,I2,2),
    sub(J1,J2,3),
    add([K1,K2],5).

board5x(Rows) :-
    Rows = [[A1,A2,B1,B2,C1],
            [D1,E1,E2,F1,C2],
            [D2,D3,F2,F3,G1],
            [D4,H1,H2,F4,G2],
            [I1,I2,J1,J2,J3]],
    sub(A1,A2,2),
    div(B1,B2,2),
    sub(C1,C2,1),
    mul([D1,D2,D3,D4],60),
    add([E1,E2],6),
    mul([F1,F2,F3,F4],60),
    add([G1,G2],5),
    add([H1,H2],5),
    sub(I2,I1,1),
    mul([J1,J2,J3],6).

board4(Rows) :-
    Rows = [[A1,B1,B2,C1],
            [A2,D1,E1,C2],
            [F1,D2,E2,G1],
            [F2,H1,H2,G2]],
    add([A1,A2],3),
    sub(B1,B2,1),
    mul([C1,C2],12),
    sub(D1,D2,2),
    div(E1,E2,2),
    add([F1,F2],7),
    div(G1,G2,2),
    mul([H1,H2],4).

board3(Rows) :-
    Rows = [[A1,B1,B2],
            [A2,C1,C2],
            [D1,D2,C3]],
    sub(A1,A2,1),
    add([B1,B2],4),
    mul([C1,C2,C3],12),
    mul([D1,D2],3).

board2(Rows) :-
    Rows = [[A1,B1],
            [A2,B2]],
    add([A1,A2],3),
    add([B1,B2],3),
    add([A1,B2],2).

board1(Rows) :-
    Rows = [[A1]],
    mul([A1,A1],1).

%?- board1(Rows), keen(Rows), maplist(portray_clause, Rows).
%?- board2(Rows), keen(Rows), maplist(portray_clause, Rows).
%?- board3(Rows), keen(Rows), maplist(portray_clause, Rows).
%?- board4(Rows), keen(Rows), maplist(portray_clause, Rows).
?- board5h(Rows), keen(Rows), maplist(portray_clause, Rows).
%?- board5x(Rows), keen(Rows), maplist(portray_clause, Rows).
