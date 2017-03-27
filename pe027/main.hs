import Data.List
import Debug.Trace

dividesEvenly :: Int -> Int -> Bool
dividesEvenly x y = (x `mod` y) == 0

isPrime :: Int -> Bool
isPrime x
    | x <= 0 = False
    | x == 1 = False
    | x == 2 = True
    | x `mod` 2 == 0 = False -- shortcut for evens
    | x >= 3 =
        let result = case divisorIndex of
                     Just x -> False
                     Nothing -> True
            searchEnd = ceiling $ sqrt $ fromIntegral x
            divisorIndex = findIndex (dividesEvenly x) [3,5..searchEnd]
        in result

quadraticFormula :: Int -> Int -> Int -> Int
quadraticFormula a b n = n * n + a * n + b

-- Number of subsequent prime values of quardratic formula starting with n = 0
conseqPrimeCount :: Int -> Int -> Int
conseqPrimeCount a b =
    let res = case findIndex (== False) primeValues of
              Just x -> x-1
              Nothing -> -1
        formulaValues = map (quadraticFormula a b) [0..]
        primeValues = map isPrime formulaValues
    in res

main = do putStrLn $ show $ (\x -> (fst x) * (snd x)) $ snd maxCombo
    where primes = filter isPrime [1..10000]
          maxCombo = maximumBy (\x y -> compare (fst x) (fst y)) primeCountsAndIndicies
          aRange = [-999..999]
          bRange = [-1000..1000]
          primeCountsAndIndicies = [(conseqPrimeCount a b, (a, b)) | a <- aRange, b <- bRange]
