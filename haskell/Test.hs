module Main (main) where

import Encode
import Test.HUnit

test_caesar = TestCase (do{ assertEqual "Caesar encode" (caesar    1 "abcxyz 123") "bcdyza 123"
                          ; assertEqual "Caesar decode" (caesar (-1) "bcdyza 123") "abcxyz 123"
                          })
test_vigener = TestCase (do { assertEqual "Vigener encode" (vigener "abc" "xyz 123") "yac 123"
                            ; assertEqual "Vigener decode" (vigener "baz" "yac 123") "abc 123"
                            })


tests = TestList [TestLabel "test_caesar" test_caesar,
                  TestLabel "test_vigener" test_vigener]

main = runTestTT tests
