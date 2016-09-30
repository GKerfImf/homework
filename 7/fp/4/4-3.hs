{- похоже, что это слишком медленно -}
(+++) xs x = xs ++ [x]

parts2 xs = if length xs `mod` 2 == 0 then ans else undefined where 

    isUp (x:y:xs) = if x < y then isUp (y:xs) else False
    isUp _ = True

    unzip acc1 acc2 [] = (acc1,acc2)
    unzip acc1 acc2 ((x,1):xs) = unzip (acc1 +++ x) (acc2) xs
    unzip acc1 acc2 ((x,2):xs) = unzip (acc1) (acc2 +++ x) xs

    part [] = undefined
    part (x:xs) = (x,1) : part' x xs where
        part' n [] = []
        part' n (x:xs) = if n < x then (x,0) : part' x xs else (x,2) : part' n xs 

    c m xs = c' m [] xs where
        c' 0 acc ((x,0):xs) = c' 0 (acc +++ (x,2)) xs
        c' 0 acc (x:xs) = c' 0 (acc +++ x) xs
        c' 0 acc [] = [acc]
        c' m acc [] = []
        c' m acc ((x,0):xs) = c' (m-1) (acc +++ (x,1)) xs ++ c' m (acc +++ (x,2)) xs 
        c' m acc (x:xs) = c' m (acc +++ x) xs

    t1 = c (length xs `div` 2 - 1) (part xs)
    t2 = map (unzip [] []) t1
    ans = (t2,filter (\(x,y) -> isUp y) t2)
