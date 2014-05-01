module Main (main) where

import Encode
import System.Environment
import System.Exit
import Data.Char

usage   = putStrLn "Usage: encode [-cv] -k key -f file"
exit    = exitWith ExitSuccess

encript "-c" key content = caesar (read key) content
encript "-v" key content = vigener key content


parse [cipher, "-k", key, "-f", fs]
    | (cipher == "-c" && (and $ map isDigit key))
      ||
      (cipher == "-v" && (and $ map (`elem` alphabet) key)) = do { content <- readFile fs
                                                                 ; putStr (encript cipher key content)
                                                                 }
parse _                                                     = usage
 
main = getArgs >>= parse >> exit
