{-# OPTIONS_GHC -Wall #-}
module Golf where

-- Exercise 1
-- | get every nth element of a list
every :: Int -> [a] -> [a]
every n xs = case drop (n-1) xs of  -- drop is a total function
    [] -> []
    (y:ys) -> y : every n ys

{-
 - use backslash ('\') to indicate lambda expression
 - e.g. (\x y -> x + y)  -- takes two variables and return the sum
-}
skips :: [a] -> [[a]]
skips x = map (\n -> every n x) [1..length x]

{- if we define the every function as "every xs n" (i.e. [a] -> Int -> [a]),
 - then we can also use function partial application in the skips as:
 -      skips x = map (every x) [1..length x]
 - which is equivalent to
 -      skips x = map (\n -> every x n) [1..length x]
 -}
