primesTo n = eratos [2..n] where
    eratos []     = []
    eratos (p:xs) = p : eratos (xs `minus` [p*p, p*p+p..n])

    minus (x:xs) (y:ys) = case (compare x y) of 
        LT -> x : minus  xs (y:ys)
        EQ ->     minus  xs    ys
        GT ->     minus (x:xs) ys
    minus  xs     _     = xs

data Maybe a = Some a | None deriving (Show)

sqrtn n = floor $ sqrt $ fromIntegral n 

findFirst p [] = None
findFirst p (x:xs) = if p x then Some x else findFirst p xs


g n = any (\i -> isSemiprime (n-i) && isSemiprime i) [1 .. n `div` 2] where
    primes = primesTo n
    isPrime n = elem n primes

    divisor n = findFirst (\m -> n `mod` m == 0) [2 .. sqrtn n]
    
    isSemiprime n = isSemiprime' n (divisor n) where
        isSemiprime' _ None = False
        isSemiprime' n (Some m) = isPrime (n `div` m) 
