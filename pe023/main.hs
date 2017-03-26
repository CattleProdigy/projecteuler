import Debug.Trace
import Data.Set hiding (filter)

isDivisor :: Int -> Int -> Bool
isDivisor x y = x `mod` y == 0

listDivisors :: Int -> [Int]
listDivisors x = filter (isDivisor x) candidates
    where candidates = [1..x-1]

isPerfect :: Int -> Bool
isPerfect x = (sum $ listDivisors x) == x

isAbundant :: Int -> Bool
isAbundant x = (sum $ listDivisors x) > x

isDeficient :: Int -> Bool
isDeficient x = (sum $ listDivisors x) < x

listAbundantNumbersLessThan :: Int -> [Int]
listAbundantNumbersLessThan x = filter isAbundant [1..x]

main = do putStrLn $ show $ sum $ toList nonSumsOfAbudants
    where abundantNumbers = listAbundantNumbersLessThan 28123
          sumsOfAbundantNumbersList = [x + y | x <- abundantNumbers, y <- abundantNumbers, x + y < 28123];
          sumsOfAbundantNumbersSet = fromList sumsOfAbundantNumbersList
          nonSumsOfAbudants = (fromList [1..28123]) \\ sumsOfAbundantNumbersSet
