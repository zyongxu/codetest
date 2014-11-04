{-# OPTIONS_GHC -Wall #-}

{-
  Execrise 6: Tower of Hanoi Puzzle with 4 pegs
  e.g. optimal sol for 15 stacks takes only 129 moves!
  Looks like the only way to find an/all optimal solution is by using BFS
  http://en.wikipedia.org/wiki/Tower_of_Hanoi#With_four_pegs_and_beyond
  which is not time and space efficient enough to handle a large number of disks
-}

import Hanoi3p

hanoi4p :: Integer -> Peg -> Peg -> Peg -> Peg -> [Move]
hanoi4p n w x y z
    | n < 1 = []
    | n == 1 = [(w, x)]
    | n `mod` 2 == 0 = (hanoi4p (n `quot` 2) w y x z) ++ (hanoi (n `quot` 2) w x z) ++
                       (hanoi4p (n `quot` 2) y x w z)
    | otherwise = (hanoi4p (n `quot` 2) w y x z) ++ (hanoi (n `quot` 2 + 1) w x z) ++
                  (hanoi4p (n `quot` 2) y x w z)
