import System.Environment

box_sqrs    :: Int -> [Int]
box_sqrs a 
    | a>=0 && a<9 = row1 ++ row2 ++ row3
    | otherwise = []
    where   row1 = a:a+1:a+2:[]
            row2 = a+9:a+10:a+11:[]
            row3 = a+18:a+19:a+20:[]

sudoku_sol  :: [Int] -> [Int]
sudoku_sol [] = []
sudoku_sol (x:xs)
    | x==0 = 1: sudoku_sol xs
    | otherwise = x: sudoku_sol xs

fill    :: [Int] -> Int -> [Int]
fill [] a = []
fill (x:xs) a
    | x==0 = a : fill xs a
    | otherwise = x : fill xs a

which_box :: Int -> Int    -- get box from square
which_box sq = ((*3)(div row 3)) + (div col 3)
    where   col = mod sq 9
            row = div sq 9

main = do
    a <- getLine
    let l = map (\x -> read [x]::Int) a
    print l
    print $ fill l 5
    print $ which_box 11
    print $ which_box 24
    print $ which_box 36
    print $ which_box 79
    if (length l) /= 81
        then print "Length is not 81"
        else print $ fill l 5
    getArgs >>= print
