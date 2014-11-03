{-# OPTIONS_GHC -Wall #-}

module Hanoi3p where

-- Execrise 5: Recursivly Solving the Tower of Hanoi Puzzle

-- type declaration, like typedef in C++
type Peg = String
type Move = (Peg, Peg)

{- |
   Given the number of discs and names for the three pegs, hanoi
   should return a list of moves to be performed to move the stack of
   discs from the first peg to the second
   e.g. hanoi 2 "a" "b" "c" == [("a","c"), ("a","b"), ("c","b")]
-}
hanoi :: Integer -> Peg -> Peg -> Peg -> [Move]
hanoi n x y z
    | n < 1 = []
    | n == 1 = [(x, y)]
    | otherwise = (hanoi (n-1) x z y) ++ ((x, y) : (hanoi (n-1) z y x))
