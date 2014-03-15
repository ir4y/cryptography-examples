import Data.Char
import Data.List
import System.Environment
import System.Exit

alphabet = "abcdefghijklmnopqrstuvwxyz"

do_plus shift char
    | (shift + char) > ord('z') = shift + char - 26
    | (shift + char) < ord('a') = shift + char + 26
    | otherwise = shift + char

do_shift shift char 
    | char `elem` map ord alphabet = shift `do_plus` char
    | otherwise = char

caesar shift msg = map (chr . (do_shift shift) . ord) msg

vigener key msg = msg

usage   = putStrLn "Usage: encode [-cv] -k key -f file"
exit    = exitWith ExitSuccess
die     = exitWith (ExitFailure 1)

parse ["-c", "-k", key, "-f", fs] = do { content <- readFile fs
                                       ; putStr (caesar (read key) content)
                                       ; exit
                                       }
parse ["-v", "-k", key, "-f", fs] = do { content <- readFile fs
                                       ; putStr (vigener key content)
                                       ; exit
                                       }
parse _                           = usage >> exit

main = getArgs >>= parse
