{-# OPTIONS_GHC -Wall #-}
module LogAnalysis where

-- possible helpful functions: read, lines, words, unwords, take, drop, and .
import Log

buildMessage :: [String] -> LogMessage
buildMessage ("E":(x:(y:zs))) = LogMessage (Error (read x)) (read y) (unwords zs)
buildMessage (x:(y:zs))
    | x == "W" = LogMessage Warning (read y) (unwords zs)
    | x == "I" = LogMessage Info (read y) (unwords zs)
buildMessage xs = Unknown (unwords xs)

parseMessage :: String -> LogMessage
parseMessage str = buildMessage (words str)

-- file reading ref:
--   http://neilmitchell.blogspot.com/2010/01/haskell-io-without-monads.html
--   https://www.fpcomplete.com/school/starting-with-haskell/basics-of-haskell/3-pure-functions-laziness-io
-- syntax involved in the above:
--   https://www.fpcomplete.com/school/starting-with-haskell/basics-of-haskell/function-application#dollar-and-dot-notation
parse :: String -> [LogMessage]
