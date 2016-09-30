{-- 
	А сейчас всё в порядке, извините, что отправил одно и то же решение несколько раз.
--}

parts xs = list_gcd (f xs) > 1 where
    list_gcd xs = foldl gcd 0 xs

    f [] = []
    f xs = let (l,r) = upm xs in l : f r  

    upm [] = (0,[])
    upm xs = up 1 xs where 
        up acc (x:y:xs) = if x < y then up (acc+1) (y:xs) else (acc,y:xs)
        up acc _ = (acc,[])
