# Bit Manipulation
> reference from [A summary: how to use bit manipulation to solve problems easily and efficiently](https://leetcode.com/problems/sum-of-two-integers/discuss/84278/a-summary-how-to-use-bit-manipulation-to-solve-problems-easily-and-efficiently)  by **LHearen**

## Introduction
Bit manipulation includes `& (and)`, `| (or)`, `~ (not)`, `^ (xor)`, and shift operators `>> (right shfit)` and `<< (left shift)`.

A lot of tasks can be done with these operations:

* Set union `A | B`
* Set intersection `A & B`
* Set subtraction `A & ~B`
* Set negation `0b1111111111...^A` or `~A`
* Set bit `A |= 1<<offset`
* Clear bit `A& ~(1<<offset)`
* Test bit  `(A&(1<<offset))!=0`
* Extract last bit `A&(-A)` or `A&~(A-1)` or `x^(x&(x-1))`
* Remove last bit `A&(A-1)`
* Get all 1-bits `~0`

## Examples
#### 1. Count the number of ones in the binary representation of the given number
##### Ordinary method
```C++
// This method takes 32 steps
int count_one(int n){
    int count=0;
    for(int i=0;i<32;i++){
        if(n&(1<<i))
            count++;
    }
    return count;
}
```
##### Improved method
```C++
// This method takes COUNT steps
int count_one(int n){
    int count = 0;
    while(n!=0){
        n=n&(n-1);
        count++;
    }
    return count;
}
```

#### 2. Is the power of four
##### Ordinary method
```C++
// use left shit instead of multiplication to potentially speed up the code
bool isPowerOfFour(int n){
    int x=1;
    while(x<n){
        x<<=2;
    }
    return x==n;
}
```
##### Improved method
```C++
bool isPowerOfFour(int n){
    return (n&(n-1))==0 && (n&0x55555555);
// make sure that there is only 1 set bit, and its position is correct;
}
```
#### 3. Sum of Two Integers
##### Ordinary method
```C++
int getSum(int a, int b){
    int result=0;
    int carry = 0;
    for(int i=0; i<32; i++){
        int ai = a & (1<<i);
        int bi = b & (1<<i);
        int resulti = carry^ai^bi;
        int newcarry = carry==0? (ai&bi):carry&(ai|bi);
        carry=newcarry;
        result|=resulti<<i;
    }
    return result;
}
```
##### Efficient Method
```C++
int getSum(int a, int b){
    return b==0? a:getSum(a^b,(a&B)<<1);
}
```
#### 4. Missing Number
Given an array containing `n` distinct numbers taken from 0,1,2,...,n, find the one that is missing from the array.
##### Efficient Method via `XOR`
```C++
int missingNumber(vector<int>& nums){
    int ret = 0;
    for(int i = 0; i < nums.size(); ++i){
        ret ^=i;
        ret ^= nums[i];
    }
    return ret^nums.size();
}
```
#### 4. Find the largest power of 2
Find the larget power of 2, which is less than or equal to the given number N
```C++
long largest_power(long N){
    // changing all right side bits to 1
    N=N|(N>>1);
    N=N|(N>>2);
    N=N|(N>>4);
    N=N|(N>>8);
    N=N|(N>>16);
    return (N+1)>>1;
}
```
#### 5. Reverse Bits
Reverse bits of a given 32 bits unsigned iteger.
##### Solution 1.
```C++
unsigned int reverseBits(unsigned int n){
    unsigned int mask = 1<<31, res = 0;
    for(int i=0;i<32; ++i){
        if(n&1) res|=mask;
        mask>>=1;
        n>>=1;
    }
    return res;
}
```
##### Solution 2.
```C++
unsigned int reverseBits(unsigned int n) {
    unsigned int mask = 1, ret = 0;
    for(int i = 0; i < 32; ++i){
        ret <<= 1;
        if(mask & n) ret |= 1;
        mask <<= 1;
	}
    return ret;
}
```
#### 6. Bitwise `AND` of Number Range
Given a range [m, n] where 0 <= m <= n <= 2147483647, return the bitwise `AND` of all numbers in this range, inclusive. For example, given the range [5,7], you should return 4.
```C++
int rangeBitwiseAnd(int m, int n){
    int a = 0;
    while(m!=n){
        m>>=1;
        n>>=1;
        a++;
    }
    return m<<a;
}
```

