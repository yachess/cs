qs :: (Ord a) => [a] -> [a]
qs [] = []
qs [x] = [x]
qs (x:xs) =
    let sm = filter (x>=) xs
        lg = filter (x<) xs
    in qs sm ++ [x] ++ qs lg

main = do
    l <- getLine
    print ( qs (map (\x -> read [x]::Int) l))
