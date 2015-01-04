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

{-
 - Exercise 2
 - pattern-matching is about taking apart a value by finding out which constructor it was built with
 - This information can be used as the basis for deciding what to do—indeed, in Haskell, this is
 - the only way to make a decision.
-}

-- | insert a LogMessage into a MessageTree (BST based on time stamp)
--   Unknown messages should be ignored
--   use pattern mathcing (x@pat) to extract members in a data type
--   TODO: handle error patterns, e.g. Node l UnKnown r
insert :: LogMessage -> MessageTree -> MessageTree
insert (Unknown _) msgTree = msgTree
insert msg Leaf = Node Leaf msg Leaf
insert msg@(LogMessage _ ts _) root@(Node l rootMsg@(LogMessage _ rootTs _) r)
    | ts < rootTs = Node (insert msg l) rootMsg r
    | ts > rootTs = Node l rootMsg (insert msg r)
    | otherwise = root

-- Exercise 3
-- | build MessageTree
build :: [LogMessage] -> MessageTree
build [] = Leaf
build [x] = Node Leaf x Leaf
build (x : xs) = insert x (build xs)

-- Exercise 4
-- | Message BST in-order traversal
inOrder :: MessageTree -> [LogMessage]
inOrder Leaf = []
inOrder (Node l n r) = (inOrder l) ++ (n : (inOrder r))

-- Exercise 5
filterBySeverity :: [LogMessage] -> [String]
filterBySeverity [] = []
filterBySeverity ((LogMessage (Error lv) _ str) : xs)
    | lv >= 50 = str : (filterBySeverity xs)
    | otherwise = filterBySeverity xs
filterBySeverity (_ : xs) = filterBySeverity xs

-- | extract out msgs whose severity level >= 50
whatWentWrong :: [LogMessage] -> [String]
whatWentWrong msgs = filterBySeverity (inOrder (build msgs))
