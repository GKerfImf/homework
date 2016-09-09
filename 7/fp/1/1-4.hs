sumfact n = sum' 0 1 2 where 
    sum' acc fact m = 
        if m > n + 1 
            then acc 
            else sum' (acc + fact) (fact * m) (m + 1) 
