{-# OPTIONS_GHC -Wall #-}

{-
  style guide:
    1. use camelCase for function and var names
    2. give every top-level function a type signature
    3. local functions and constants do NOT need type signature
    4. use -Wall: put {-# OPTIONS_GHC -Wall #-} at the 1st line
-}

-- Execrise 1
-- |Takes an integer and returns its digits in the reversed order
toDigitsRev :: Integer -> [Integer]
toDigitsRev n     -- <- this is a "(pattern) matching"
    | n <= 0 = [] -- <- this is a "(pattern) guard", could be more readable than if
    | otherwise = (n `mod` 10) : toDigitsRev (quot n 10)

-- |Takes an integer and returns its digits in a list
toDigits :: Integer -> [Integer]
toDigits n
    | n <= 0 = []
    | otherwise = reverse (toDigitsRev n)

-- Execrise 2
-- |double every other element in a list starting from the right side
doubleEveryOther :: [Integer] -> [Integer]
doubleEveryOther [] = []
doubleEveryOther [x] = [x]
doubleEveryOther (x : (y : zs))
    | (length zs) `mod` 2 == 0 = 2*x : y : doubleEveryOther zs
    | otherwise = x : 2*y : doubleEveryOther zs

-- Execrise 3
-- |sum of digits of all elements in a list
sumDigits :: [Integer] -> Integer
sumDigits [] = 0
sumDigits (x:xs) = sum (toDigits x) + sumDigits xs

-- Execrise 4
-- |final validating function
validate :: Integer -> Bool
validate x = sumDigits (doubleEveryOther (toDigits x)) `mod` 10 == 0
