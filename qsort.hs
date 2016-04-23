qsort ::(Ord a) => [a] -> [a]
qsort [] = []
qsort (x:xs) =
    let s = filter (x>=) xs
        l = filter (x<) xs
    in qsort s ++ [x] ++ qsort l

main = print (qsort [1,23,5,26,100,4,89])
