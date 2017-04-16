import System.IO
import Control.Monad
import qualified Data.Vector.Unboxed as VU
import Data.List.Split
import Debug.Trace
import Control.Monad.State
import Control.Applicative

type CostMatrix = VU.Vector Int
type Graph = VU.Vector Int

row = 80
col = 80
maxCost = maxBound :: Int

nodeIdFromGraphPos :: Int -> Int -> Int
nodeIdFromGraphPos r c = r * col + c -- zero indexed

graphPosFromNodeId :: Int -> (Int, Int)
graphPosFromNodeId id = (id `quot` col, id `mod` col)

getUpId :: Int -> Maybe Int
getUpId id
    | c <= 1 = Just $ nodeIdFromGraphPos r (c-1)
    | otherwise = Nothing
    where (r, c) = graphPosFromNodeId id

getDownId :: Int -> Maybe Int
getDownId id
    | c < (col-1) = Just $ nodeIdFromGraphPos r (c+1)
    | otherwise = Nothing
    where (r, c) = graphPosFromNodeId id

getRightId :: Int -> Maybe Int
getRightId id
    | r < (row-1) = Just $ nodeIdFromGraphPos (r+1) c
    | otherwise = Nothing
    where (r, c) = graphPosFromNodeId id

getLefttId :: Int -> Maybe Int
getLefttId id
    | r <= 1  = Just $ nodeIdFromGraphPos (r-1) c
    | otherwise = Nothing
    where (r, c) = graphPosFromNodeId id

-- CostMatrix stores cost to get to that node (including that node)
showCostMatrix :: CostMatrix -> String
showCostMatrix cm = "AYY:\n" ++ lineSep ++ "\n"
    where spaceSep = map (++ " ") $ map show $ VU.toList cm
          lineSep = concat $ (map (flip (++) "\n")) $ map concat $ chunk col spaceSep

traverseIfBetter :: Graph -> Int -> Int -> (Int -> Maybe Int) -> State CostMatrix Int
traverseIfBetter graph id parentCost successorFcn =
    do costMatrix <- get
       let oldCost = costMatrix VU.! id
       let newCost = (graph VU.! id) + parentCost
       let nextParentCost = min oldCost newCost
       if (newCost > oldCost)
           then do
               -- Early Prune
               return maxCost
           else do
               -- Update with new lower cost
               put (costMatrix VU.// [(id, newCost)])

               -- Reached end with better path
               if (id == row * col - 1)
               then do
                    return newCost

               -- Keep traversing if possible
               else do
                    case successorFcn id of
                        Just nextId -> findMinPathSumHelper graph nextParentCost nextId
                        Nothing     -> return maxCost


findMinPathSumHelper :: Graph -> Int -> Int -> State CostMatrix Int
findMinPathSumHelper graph parentCost id = liftA2 min down right
        where down = traverseIfBetter graph id parentCost getDownId
              right = traverseIfBetter graph id parentCost getRightId

findMinPathSum :: Graph -> Int
findMinPathSum graph = evalState (findMinPathSumHelper graph 0 0) initialCosts
    where initialCosts = (generateInitialCost row col)

generateInitialCost :: Int -> Int -> CostMatrix
generateInitialCost a b = VU.replicate (a * b) maxCost


-- For the types
readInt :: String -> Int
readInt = read

--main = (print . findMinPathSum . preprocess) =<< (readFile "./small.txt")
    --where preprocess = map readInt . filter (/= "") . concat . map (splitOn " ") . splitOn "\n"

main = (print . findMinPathSum . preprocess) =<< (readFile "./p081_matrix.txt")
    where preprocess = VU.fromList . map readInt . filter (/= "") . concat . map (splitOn ",") . splitOn "\n"
