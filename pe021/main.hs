import Debug.Trace

isDivisor :: Int -> Int -> Bool
isDivisor x y = x `mod` y == 0

listDivisors :: Int -> [Int]
listDivisors x = filter (isDivisor x) candidates
    where candidates = [1..x-1]

isAmicable :: Int -> Bool
isAmicable x = (sum $ listDivisors divisorSum) == x && divisorSum /= x
    where divisorSum = sum $ listDivisors x

main = do putStrLn $ show (sum $ trace ("Amicable list: \n" ++ show amicableList) amicableList)
    where amicableList = filter (isAmicable) [1..10000]
