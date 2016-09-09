sumTo :: Int -> Int
sumTo n = sum' 0 n where
    sum' acc 0 = acc
    sum' acc n = sum' (acc + n) (n - 1) 

sumSq :: Int -> Int
sumSq n = sum' 0 n where
    sum' acc 0 = acc
    sum' acc n = sum' (acc + n ^ 2) (n - 1)

sq :: Int -> Int
sq = \x -> x ^ 2

sumsqr :: Int -> Double
sumsqr n = (fromIntegral . sq . sumTo) n / (fromIntegral . sumSq) n