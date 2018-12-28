class Solution {
  public:
    int hammingDistance(int x, int y) {
        int count = 0;
        while (x != 0 || y != 0) {
            if (x % 2 != y % 2)
                count++;
            x >>= 1;
            y >>= 1;
        }
        return count;
    }
};

class Solution2 {
public:
    int hammingDistance(int x, int y) {
        int z = x^y;
        int count = 0;
        while(z!=0){
            z&=z-1;
            count++;
        }
        return count;
    }
};
