function isprime(n)
    if n==1 then
        return false
    end
    if n==2 then
        return true
    end
    if n%2==0 then
        return false
    end
    c = math.floor((math.sqrt(n))+1)
    while n%c  ~= 0 do
        c = c-1
        if c==1 then
            return true
        end
    end
    return false
end

cnt = 0
for i=1,10000 do
    if isprime(i) then
        cnt = cnt + 1
    end
end
print (cnt)
