
class nprimes {

    static boolean isprime(int n){
        if (n==1)
            return false;
        if (n==2)
            return true;
        if (n%2==0)
            return false;
        int c = (int)Math.sqrt(n)+1;
        for (int i=c;i>1;i--)
            if (n%i==0)
                return false;
        return true;
    }   

    public static void main(String args[]){
        int cnt=0;

        for (int i=0;i<10000;i++)
            if (isprime(i))
                cnt++;
        System.out.println(cnt);
    }
}
