{-# OPTIONS_GHC -Wall #-}
module Golf where

-- Exercise 1
-- | get every nth element of a list
every :: Int -> [a] -> [a]
every n xs = case drop (n-1) xs of  -- drop is a total function
    [] -> []
    (y:ys) -> y : every n ys

{-
 - use backslash ('\') to indicate lambda parameters
 - e.g. \x y -> x + y  -- takes two variables and return the sum
-}
skips :: [a] -> [[a]]
skips x = map (\n -> every n x) [1..length x]
