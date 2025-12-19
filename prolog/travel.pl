% https://lpn.swi-prolog.org/lpnpage.php?pagetype=html&pageid=lpn-htmlse12

byCar(auckland,hamilton).
byCar(hamilton,raglan).
byCar(valmont,saarbruecken).
byCar(valmont,metz).

byTrain(metz,frankfurt).
byTrain(saarbruecken,frankfurt).
byTrain(metz,paris).
byTrain(saarbruecken,paris).

byPlane(frankfurt,bangkok).
byPlane(frankfurt,singapore).
byPlane(paris,losAngeles).
byPlane(bangkok,auckland).
byPlane(singapore,auckland).
byPlane(losAngeles,auckland).

travel(X, Y) :-
    byCar(X, Y);
    byTrain(X, Y);
    byPlane(X, Y).
go(X, Y) :- travel(X, Y).
go(X, Y) :-
    travel(X, Z),
    go(Z, Y).
