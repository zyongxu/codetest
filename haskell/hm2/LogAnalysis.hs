{-# OPTIONS_GHC -Wall #-}
module LogAnalysis where

import Log

{-
 - Exercise 1
 - possible helpful functions: read, lines, words, unwords, take, drop, and .
-}

buildMessage :: [String] -> LogMessage
buildMessage ("E":severity:timeStamp:msgs) = LogMessage (Error (read severity)) (read timeStamp) (unwords msgs)
buildMessage (msgType:timeStamp:msgs)
    | msgType == "W" = LogMessage Warning (read timeStamp) (unwords msgs)
    | msgType == "I" = LogMessage Info (read timeStamp) (unwords msgs)
buildMessage xs = Unknown (unwords xs)

-- | parse a single line of log into a LogMessage
parseMessage :: String -> LogMessage
parseMessage str = buildMessage (words str)

-- | parse the content of a log file into LogMessages
parse :: String -> [LogMessage]
parse content = map parseMessage (lines content)
