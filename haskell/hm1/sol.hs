{-# OPTIONS_GHC -Wall #-}

{-
  style guide:
    1. use camelCase for function and var names
    2. give every top-level function a type signature
    3. local functions and constants do NOT need type signature
    4. use -Wall: put {-# OPTIONS_GHC -Wall #-} at the 1st line
-}

-- |Takes an integer and returns its digits in the reversed order
toDigitsRev :: Integer -> [Integer]
toDigitsRev n
    | n <= 0 = []
    | otherwise = (n `mod` 10) : toDigitsRev (quot n 10)

toDigits :: Integer -> [Integer]
toDigits n
    | n <= 0 = []
    | otherwise = reverse (toDigitsRev n)
