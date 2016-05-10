function part (ar,l,r)
    pv = ar[l]
    i = l
    j = r+1
    while true  do
        i=i+1
        while ar[i] <= pv and i <= r do
            i= i+1
        end
        j=j-1
        while ar[j] > pv do
            j= j-1
        end
        if i>=j then break end
        ar[i],ar[j] = ar[j],ar[i]
    end
    ar[l],ar[j] = ar[j],ar[l]
    return j
end    

function quicksort(ar,l,r)
    if l>r then return end
    i = part(ar,l,r);
    quicksort(ar,l,i-1);
    quicksort(ar,i+1,r);
end
   
a={}

math.randomseed(os.time())
for i=1,10000 do
    a[i] = math.random(1,10000)
end

quicksort(a,1,9999);

print(" After sort:");
for i=1,10000 do
    io.write(a[i]);
end
