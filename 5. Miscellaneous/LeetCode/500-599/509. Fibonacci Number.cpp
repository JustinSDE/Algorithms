class Solution {
public:
    int fib(int N) {
        if(N ==0)
           return 0;
        if(N<=2)
            return 1;
        int prevprev = 1, prev = 1;
        int cur;
        int i = 3;
        while(i<=N){
            cur = prevprev+prev;
            prevprev = prev;
            prev = cur;
            i++;
        }
        return cur;
    }
};
