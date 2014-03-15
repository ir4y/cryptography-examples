import Data.Char
import Data.List
import System.Environment
import System.Exit

encode shift msg = map (chr . (+ shift) . ord) msg

usage   = putStrLn "Usage: encode -k key -f file"
exit    = exitWith ExitSuccess
die     = exitWith (ExitFailure 1)

parse ["-k", key, "-f", fs] = do { content <- readFile fs
                                 ; putStr (encode (read key) content)
                                 ; exit
                                 }
parse _                     = usage >> exit

main = getArgs >>= parse
