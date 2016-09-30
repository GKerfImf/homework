isUp (x:y:xs) = if x < y then isUp (y:xs) else False
isUp _ = True

parts2 xs = f' [] [] xs where
    u_bound = length xs `div` 2

    f' a b [] = True
    f' a b (c:cs) =
        let n_a = a ++ [c] in
        let n_b = b ++ [c] in

        let b1 = isUp n_a && length n_a <= u_bound in
        let b2 = isUp n_b && length n_b <= u_bound in 

        let l = if b1 then f' n_a b cs else False in
        let r = if b2 then f' a n_b cs else False in

        l || r