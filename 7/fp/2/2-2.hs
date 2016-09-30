nseq n = nseq' 0 n where
    nseq' _ 0 = 1
    nseq' m n = if m >= n then 0 else 1 + (sum $ map (\x -> nseq' x (n - x)) [m+1 .. n `div` 2])
