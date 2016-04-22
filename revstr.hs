
{- Revert a given string -}

revchar ::String -> String
revchar [] = []
revchar [x] = [x]
revchar (x:xs) = revchar xs ++ [x]

main = do
    l <- getLine
    print (revchar l)
