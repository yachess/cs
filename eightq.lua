function attack(a,b)
    if math.floor(a/8)==math.floor(b/8) or 
        a%8 == b%8 or
        math.abs(math.floor(a/8)-math.floor(b/8))==math.abs(a%8-b%8) then
        return true
    end
    return false
end

queens = {}
tries = 0

function member(queens,sq)
    for i=1,#queens do
        if queens[i]==sq then
            return true
        end
    end
    return false
end

function collide(queens, sq)
    for i=1,#queens do
        if attack(queens[i]-1,sq-1) then
            return true
        end
    end
    return false
end

function print_board(queens)
    for i=1,64 do
        if member(queens,i) then
            io.write(" Q")
        else
            io.write(" .")
        end
        if i%8==0 then
            io.write("\n")
        end
    end
end

function solve(queens, row)
    if row == 9 then
        tries = tries + 1
        print ("Solution#: ",tries)
        print_board(queens)
    else
        for col=0,7 do
            sq = (row-1)*8 + col +1
            if not collide(queens,sq) then
                queens[row] = sq;
                solve(queens,row+1)
                queens[#queens] = nil
            end
        end
    end
end

solve(queens,1);
