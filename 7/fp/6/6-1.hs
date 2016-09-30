distSq (x1,x2) (y1,y2) = (x1 - y1)^2 + (x2 - y2)^2

isosc x y z = 
    let xy = distSq x y in
    let yz = distSq y z in
    let zx = distSq z x in 

	xy == yz || yz == zx || zx == xy