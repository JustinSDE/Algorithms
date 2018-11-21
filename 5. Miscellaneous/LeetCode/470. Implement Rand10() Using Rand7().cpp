// The rand7() API is already defined for you.
// int rand7();
// @return a random integer in the range 1 to 7

class Solution {
  public:
    int rand10() {
        int a, b, c;
        do {
            a = rand7() - 1;
            b = rand7() - 1;
            c = a * 7 + b;
        } while (c > 39);
        return c / 4 + 1;
    }
};