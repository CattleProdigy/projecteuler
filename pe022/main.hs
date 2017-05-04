import System.IO
import Data.List.Split
import Data.List

-- newLinePrint :: Show a => [a] -> IO ()
-- newLinePrint x = putStrLn $ foldl (++) "" withNewLines
--     where withNewLines = map ((++ "\n") . show) x

characterNameScore :: [Char] -> Int
characterNameScore x = sum letterScores
    where letterScores = map (((-alphaStart) +) . fromEnum) x
          alphaStart = fromEnum 'A' - 1

nameScore :: [[Char]] -> [Int]
nameScore x = zipWith ((*) . characterNameScore ) x positions
    where positions = [1..]

main = (print . sum . nameScore . sort . preprocess ) =<< (readFile "./names.txt")
    where preprocess = splitOn "," . filter (/= '\"')
