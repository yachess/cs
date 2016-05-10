{- 8 queen puzzle solver -}

attack :: Int -> Int -> Bool
attack a b
    | (rem a 8) == (rem b 8) = True
    | (div a 8) == (div b 8) = True
    | (abs ((rem b 8)-(rem a 8))) == (abs ((div b 8)-(div a 8))) = True
    | otherwise = False

main = print (attack 0 25)
    
