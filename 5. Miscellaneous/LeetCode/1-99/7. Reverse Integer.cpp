class Solution {
public:
    int reverse(int x) {
        long long res = 0;
        int sign=1;
        if(x<0){
            sign = -1;
            x=-x;
        }

        while(x!=0){
            res=res*10+x%10;
            x=x/10;
        }
        if(sign==-1)
            res = -res;
        if(res<INT_MIN || res>INT_MAX){
            return 0;
        }
        return res;
    }
};
