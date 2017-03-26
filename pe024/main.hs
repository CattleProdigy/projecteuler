import Data.List

listDigitPermutations :: [Int] -> [[Int]]
listDigitPermutations x = permutations x

digitsToNum :: [Int] -> Int
digitsToNum [] = 0
digitsToNum (x:xs) = x + 10*digitsToNum xs

main = do putStrLn $ show $ perms!!(1000000-1)
    where digitsList = [0..9]
          perms = sort $ map digitsToNum (listDigitPermutations digitsList)
