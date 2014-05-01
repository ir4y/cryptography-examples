import Encode
import Test.HUnit

test_caesar = TestCase (assertEqual "Assert caesar" (caesar 1 "abcdefg") "bcdefgh")
test_vigener = TestCase (do { assertEqual "Assert simple vigener" (vigener "a" "abcdefg") "bcdefgh"
                            ; assertEqual "Assert comlicated vigener" (vigener "abc" "abcdefg") "bdfegih"
                            })


tests = TestList [TestLabel "test_caesar" test_caesar,
                  TestLabel "test_vigener" test_vigener]

main = runTestTT tests
