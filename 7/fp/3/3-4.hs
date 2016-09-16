count x xs = count' 0 xs where
    count' acc [] = acc
    count' acc (y:xs) = 
        if x /= y 
            then count' acc xs
            else count' (acc + 1) xs

sameDigits xs = 
    if length xs > 10
        then True 
        else any (\x -> count x (map (\y -> mod y 10) xs) > 1) [0..9]