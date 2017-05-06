import Data.List
import Data.Ord
import Debug.Trace

longDivision :: Int -> Int -> [Int] -> [Int]
longDivision 0 d dec = dec
longDivision n d dec = dec ++ longDivision n' d ([newDigit] ++ dec)
    where newDigit = (10 * n) `quot` d
          n' = 10 * n - d * newDigit

-- 1 4 [ ]
-- nd = 10 / 4 = 2
-- n' = 10 * 1 - 4 * 2 = 8

-- 8 4 [2]
-- nd = 10 * 8 / 4 = 20
-- n' = 10 * 8 - 4 * 20 = 0

-- 8 4 [2 5]
-- nd = 10 * 8 / 4 = 20
-- n' = 10 * 8 - 4 * 20 = 0


findCycle :: Eq a => [a] -> ([a],[a])
findCycle xxs = fCycle xxs xxs
  where fCycle (x:xs) (_:y:ys)
         | x == y              = fStart xxs xs
         | otherwise           = fCycle xs ys
        fCycle _      _        = (xxs,[]) -- not cyclic
        fStart (x:xs) (y:ys)
         | x == y              = ([], x:fLength x xs)
         | otherwise           = let (as,bs) = fStart xs ys in (x:as,bs)
        fLength x (y:ys)
         | x == y              = []
         | otherwise           = y:fLength x ys

cycleLength :: [Int] -> Int
cycleLength a = 0 -- trace ((show $ fst $ findCycle a) ++ (show a)) 0

main = print $ length a
       where denominators = [2..20]
             digits = map (\d -> take 30 $ longDivision 1 d []) denominators
             a = map (\x -> (trace ((show $ fst x) ++ ": " ++ (show $ snd x)) 0)) $ zip denominators digits
             cycleLengths = map (cycleLength) digits
             denomsAndLengths = zip denominators cycleLengths
             maximizingDenom = fst $ maximumBy (comparing snd) denomsAndLengths


--n = 1, d = 7
--
--n / d = a0 / 1 + a1 / 10 | + a2 / 100 ...
--n / d = a1 / 10 | + a2 / 100 ...
--a1 = 10 / 7 = 1
--n / d = a1* / 10 + a2 / 100 | ...
--n / d - a1* / 10 = a2 / 100 | ...
--(10 n - d a1*) / (10 * d) = a2 / 100 | ...
--(10 n - d a1*) / (d) = a2 / 10 | ...
--n' = 10 * n_ - d * a1_
