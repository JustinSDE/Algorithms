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


