{-# OPTIONS_GHC -Wall #-}

{-
  style guide:
    1. use camelCase for function and var names
    2. type and data constructor names must always start with
       a capital letter;
       variables (including names of functions) must always
       start with a lowercase letter
    3. give every top-level function a type signature
    4. local functions and constants do NOT need type signature
    5. use -Wall: put {-# OPTIONS_GHC -Wall #-} at the 1st line
-}

-- Execrise 1
-- |Takes an integer and returns its digits in the reversed order
toDigitsRev :: Integer -> [Integer]
toDigitsRev n     -- <- this is a "(pattern) matching"
    | n <= 0 = [] -- <- this is a "(pattern) guard", could be more readable than if
    | otherwise = (n `mod` 10) : toDigitsRev (quot n 10)

{-
 - pattern matching is a syntax sugar for the `case` expression:
 -      case exp of
 -          pat1 -> exp1
 -          pat2 -> exp2
 - patterns are examed from top to bottom, only the exp corresponding
 - to the FIRST matched pattern will be evaluated
-}

-- |Takes an integer and returns its digits in a list
toDigits :: Integer -> [Integer]
toDigits n
    | n <= 0 = []
    | otherwise = reverse (toDigitsRev n)

{-
 - a list ([...]) in haskell is a singly linked list!
 - lists concatenation: ++ (e.g. [1, 2, 3] ++ [4])
 - prepend an element to a list: : (e.g. 1 : [2, 3, 4])
 - get element by index: !! (e.g. ([1, 2, 3] !! 1) == 2)
 - other useful functions: head, tail, last, init, length,
 -                         null, reverse, take, drop,
 -                         maximum, minimum, sum, product
 -                         elem (actually for search)
-}

-- Execrise 2
-- |double every other element in a list starting from the right side
doubleEveryOther :: [Integer] -> [Integer]
doubleEveryOther [] = []
doubleEveryOther [x] = [x]
doubleEveryOther (x : (y : zs)) -- this is the equivalent to (x : y : zs)
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
