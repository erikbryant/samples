% https://lpn.swi-prolog.org/lpnpage.php?pagetype=html&pageid=lpn-htmlse7

% I copied from a Google search AI response. Seems like there should already
% be a mechanism for it, though.
all_different([]).
all_different([H|T]) :-
    \+ member(H, T), % H is not a member of the rest of the list
    all_different(T). % Recursively check the rest of the list

word(astante, a,s,t,a,n,t,e).
word(astoria, a,s,t,o,r,i,a).
word(baratto, b,a,r,a,t,t,o).
word(cobalto, c,o,b,a,l,t,o).
word(pistola, p,i,s,t,o,l,a).
word(statale, s,t,a,t,a,l,e).

crossword(V1, V2, V3, H1, H2, H3) :-
    word(V1, _, A22, _, A42, _, A62, _),
    word(V2, _, A24, _, A44, _, A64, _),
    word(V3, _, A26, _, A46, _, A66, _),

    word(H1, _, A22, _, A24, _, A26, _),
    word(H2, _, A42, _, A44, _, A46, _),
    word(H3, _, A62, _, A64, _, A66, _),

    all_different([H1, H2, H3, V1, V2, V3]).
