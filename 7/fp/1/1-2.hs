b n = b' 0 where 
    b' m = if m >= n then m else m + 1 / b' (m + 1)