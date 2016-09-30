{--

      | x < y | x = y | x > y |   []  |
______|_______|_______|_______|_______|
start |    up | False | False | False |
   up |    up | False |  down | False |
 down | False | False |  down |  True |
--}

upDown xs = start xs where
    start (x:y:xs) = if x < y then up (y:xs) else False
    start _ = False

    up (x:y:xs) 
        | x < y = up (y:xs)
        | x == y = False
        | x > y = down (y:xs)
    up _ = False

    down (x:y:xs) = if x > y then down (y:xs) else False
    down _ = True