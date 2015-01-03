-- CIS 194 Homework 2

module Log where

import Control.Applicative

{-
  Define a data type:
      data TypeCtor = ValueCtor1
                    | ValueCtor2 Int String [String]
                    | ...
  Note: type ctor and value ctor could have the same name

  We use the "type ctor" to refer to the data type, and use
  "value ctor" to carete a value of that type, e.g.:
      myInfo :: TypeCtor
      myInfo = ValueCtor2 2 "hello" ["world1", "world2"]
-}

data MessageType = Info
                 | Warning
                 | Error Int
  deriving (Show, Eq)

type TimeStamp = Int

data LogMessage = LogMessage MessageType TimeStamp String
                | Unknown String
  deriving (Show, Eq)

data MessageTree = Leaf
                 | Node MessageTree LogMessage MessageTree
  deriving (Show, Eq)

{-
 - "functions" are pure and have no side effect. But "actions" have side effects,
 - e.g. IO is an action rather than a function
-}

-- | @testParse p n f@ tests the log file parser @p@ by running it
--   on the first @n@ lines of file @f@.
testParse :: (String -> [LogMessage])
          -> Int
          -> FilePath
          -> IO [LogMessage]
testParse parse n file = take n . parse <$> readFile file

-- | @testWhatWentWrong p w f@ tests the log file parser @p@ and
--   warning message extractor @w@ by running them on the log file
--   @f@.
testWhatWentWrong :: (String -> [LogMessage])
                  -> ([LogMessage] -> [String])
                  -> FilePath
                  -> IO [String]
testWhatWentWrong parse whatWentWrong file
  = whatWentWrong . parse <$> readFile file
