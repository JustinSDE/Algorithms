class Solution {
public:
    int climbStairs(int n) {
        if(n<=1)
            return 1;
        vector<int> ways(n+1);
        ways[0]=1;
        ways[1]=1;
        for(int i=2;i<=n;i++){
            ways[i]=ways[i-1]+ways[i-2];
        }
        return ways[n];
    }
};

/**
 * because we are using only the previous two values, we can optimize the memory usage
 */
class Solution2 {
public:
    int climbStairs(int n) {
        if(n<=1)
            return 1;
        int prev=1, prevprev = 1, cur;
        for(int i=2;i<=n;i++){
            cur = prev+prevprev;
            prevprev = prev;
            prev = cur;
        }
        return cur;
    }
};


