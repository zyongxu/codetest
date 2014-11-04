{-# OPTIONS_GHC -Wall #-}
module LogAnalysis where

import Log

buildMessage :: [String] -> LogMessage
buildMessage 'I':xs = Info (read xs[1]) xs[2]
buildMessage 'W':xs = Warning (read xs[1]) xs[2]
buildMessage 'E':xs = (Error (read xs[1])) (read xs[2]) xs[3]

parseMessage :: String -> LogMessage
    parseMessage str = buildMessage (words str)
