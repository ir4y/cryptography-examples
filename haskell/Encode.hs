module Encode (caesar, vigener, alphabet) where

import Data.Char
import Data.List

alphabet = "abcdefghijklmnopqrstuvwxyz"

do_plus shift char
    | (shift + char) > ord('z') = shift + char - 26
    | (shift + char) < ord('a') = shift + char + 26
    | otherwise = shift + char

do_shift shift char 
    | char `elem` map ord alphabet = shift `do_plus` char
    | otherwise = char

caesar shift msg = map (chr . (do_shift shift) . ord) msg

to_shift key = key - ord('a') + 1

vigener key msg = map (chr . uncurry do_shift) $ zip (map (to_shift . ord) $ (cycle key))
                                                     (map ord msg)
