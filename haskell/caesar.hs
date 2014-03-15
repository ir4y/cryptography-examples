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

to_shift key = 1 + ord('a') - key

vigener key msg = map (chr . uncurry do_shift) (zip (map (to_shift . ord) (intercalate "" (repeat key)))
                                                    (map ord msg))

usage   = putStrLn "Usage: encode [-cv] -k key -f file"
exit    = exitWith ExitSuccess
die     = exitWith (ExitFailure 1)

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
