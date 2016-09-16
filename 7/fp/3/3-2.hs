sumprod [] = undefined
sumprod [x] = undefined
sumprod xs = sumprod' 0 xs where
    sumprod' acc (x:y:xs) = sumprod' (acc + x * y) (y:xs)
    sumprod' acc _ = acc
