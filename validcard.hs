evensum :: (Integral a) => [a] -> a
evensum [] = 0
evensum (x:y:xs)
    | x*2<10 = x * 2 + evensum xs
    | otherwise = x*2-10 + 1 + evensum xs

oddsum :: (Integral a)=> [a]-> a
oddsum [] = 0
oddsum (x:y:xs) = y + oddsum xs

main = do
    putStrLn "Enter card number (w/o space):" 
    ln <- getLine
    let l = map (\x -> read [x]::Int) ln
    let rm = rem ((evensum l)+(oddsum l)) 10
    print (rm)
    if (rm == 0)
        then print "Valid."
        else print "Not valid."
       

