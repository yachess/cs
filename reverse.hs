reverse' :: [a] -> [a]
reverse' [] = []
reverse' [x] = [x]
reverse' (x:xs) = reverse' xs  ++ [x]

main = do
    print (reverse' [1,2,3,4,5])

