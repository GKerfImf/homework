f :: Int -> Double
f n = if n < 1 then 1 else 1 + 1/ f (n - 1)