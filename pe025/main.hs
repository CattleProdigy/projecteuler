import Data.List

fib :: [Integer]
fib = 1 : 1 : zipWith (+) fib (tail fib)

main = do putStrLn $ resultStr
    where resultStr = case (findIndex (>= 10^999) fib) of
                      Just x -> show (x+1)
                      Nothing -> "Error"
