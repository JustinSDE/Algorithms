class Solution {
public:
    double myPow(double x, int n) {
        if(n==0)
            return 1;
        if(n==1)
            return x;
        if(n==-1)
            return 1.0/x;
        if(n%2==0)
        {
            double temp = myPow(x, n/2);
            return temp*temp;
        }
        else{
            double temp=myPow(x,n/2);
            return temp*temp*myPow(x,n%2);
        }
    }
};

class Solution2 {
public:
    double myPow(double x, int n) {
        if(n==0)
            return 1;
        if(n==1)
            return x;
        if(n==-1)
            return 1.0/x;
        double temp=myPow(x,n/2);
        return temp*temp*myPow(x,n%2);
    }
};