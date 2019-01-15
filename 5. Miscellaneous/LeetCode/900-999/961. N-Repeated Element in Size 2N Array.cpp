class Solution {
public:
    int repeatedNTimes(vector<int>& A) {
        unordered_set<int> seen;
        for(int a:A){
            if(seen.count(a))
                return a;
            seen.insert(a);
        }
        return A[0];
    }
};


/**
 * Pigeonhole principle
 * The longest distance between the same number is 2.
 * Also need to deal with corner case where there are only 4 elements.
 */
class Solution2 {
public:
    int repeatedNTimes(vector<int>& A) {
        int sz = A.size();
        for(int i=2; i<sz; i++){
            if(A[i]==A[i-1] || A[i]==A[i-2])
                return A[i];
        }
        return A[0];
    }
};

/**
 * randomized algorithm
 * chance to return is 1/4;
 */
class Solution2 {
public:
    int repeatedNTimes(vector<int>& A) {
        int sz =A.size();
        int i, j;
        while(true){
            i = rand() % sz;
            j = rand() % sz;
            while(j==i){
                j= rand()%sz;
            }
            if(A[i]==A[j])
                return A[i];
        }
    }
};
