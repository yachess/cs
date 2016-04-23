elem' :: (Eq a)=>a->[a]->Bool
elem' a [] = False
elem' a (x:xs)
    | a==x  = True
    | otherwise = a `elem'` xs

main = print (elem' 9 [1,3..21])
