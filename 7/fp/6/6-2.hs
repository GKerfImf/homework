sumprod [] = undefined
sumprod xs = foldl (\acc (x,y) -> acc + x * y) 0 (zip xs (tail xs))