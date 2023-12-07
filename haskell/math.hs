module MathFuncs where

import Data.List

cube :: Integer -> Integer
cube n = n * n * n

triple :: Integer -> Integer
triple n = 3 * n

triple_cube :: Integer -> Integer
triple_cube n = triple ( cube n )

fib :: Integer -> [ Integer ]
fib 0 = []
fib 1 = [ 1 ]
fib 2 = [ 1, 1 ]
fib n =
  let
    a = fib ( n - 1 )
    b = last a
    c = last ( init a )
  in
    a ++ [ b + c ]

collatz :: Integer -> [ Integer ]
collatz 0 = []
collatz 1 = [ 1 ]
collatz n
  | even n    = n:collatz (n `div` 2)
  | otherwise = n:collatz (3 * n + 1)

sum_digits :: Integer -> Int
sum_digits n =
  let
    a = show n
    b = map fromEnum a
    c = map (subtract (fromEnum '0')) b
  in
    sum c

power_sum :: Double -> Int
power_sum n = sum_digits (floor (2.0 ** n))

sums :: Double -> [Int]
sums 1 = [ power_sum 1 ]
sums n = (power_sum n):(sums (n-1))

factorial :: Integer -> Integer
factorial 1 = 1
factorial n = n * factorial ( n - 1 )

perm [] = [ [] ]
perm xs = [ x:ps | x <- xs, ps <- perm (delete x xs) ]


primes = sieve [2..] where
    sieve (p:xs) =
        p : (sieve (remove p xs)) where
            remove what (a:as)  | a < what = a:(remove what as)
                                | a == what = (remove (what+p) as)
                                | a > what = a:(remove (what+p) as)
