data Candy = Cake String Int | CandyPack String Int Double deriving Show

price (Cake _ c) = fromIntegral c
price (CandyPack _ c m) = (fromIntegral c) * m

totalPrice lst = sum $ map price lst

test = floor $ totalPrice [Cake "1" 100, CandyPack "2" 1000 0.5, Cake "3" 400]