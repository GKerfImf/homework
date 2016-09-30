repeatFunc f 0 = id
repeatFunc f n = f . repeatFunc f (n - 1)