{-# OPTIONS_GHC -Wall #-}

-- Execrise 6: the optimal solution for Tower of hanoi Puzzle with 4 pegs
-- e.g. optimal sol for 15 stacks takes 129 moves

import Hanoi3p

hanoi4p :: Integer -> Peg -> Peg -> Peg -> Peg -> [Move]
hanoi4p n w x y z
    | n < 1 = []
    | n == 1 = [(w, x)]
    | n `mod` 2 == 0 = (hanoi4p (n `quot` 2) w y x z) ++ (hanoi (n `quot` 2) w x z) ++
                       (hanoi4p (n `quot` 2) y x w z)
    | otherwise = (hanoi4p (n `quot` 2) w y x z) ++ (hanoi (n `quot` 2 + 1) w x z) ++
                  (hanoi4p (n `quot` 2) y x w z)
