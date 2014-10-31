{-# OPTIONS_GHC -Wall #-}

-- Execrise 6: the Tower of Hanoi Puzzle with 4 pegs

type Peg = String
type Move = (Peg, Peg)

hanoi4p :: Integer -> Peg -> Peg -> Peg -> Peg -> [Move]
hanoi4p n w x y z
    | n < 1 = []
    | n == 1 = [(w, x)]
    | otherwise = 

