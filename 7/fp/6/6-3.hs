data Tree = Empty | Node Integer Tree Tree deriving Show

height Empty = 0
height (Node _ Empty Empty) = 0
height (Node _ l r) = 1 + max (height l) (height r)