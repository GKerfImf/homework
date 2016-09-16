minlist [] = undefined
minlist (x:xs) = minlist' x xs where
    minlist' acc [] = acc
    minlist' acc (x:xs) = minlist' (min acc x) xs 