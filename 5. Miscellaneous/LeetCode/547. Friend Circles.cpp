class Solution {
public:
    int findCircleNum(vector<vector<int>>& M) {
        int sz=M.size();
        if(sz==0)
            return 0;
        vector<int> disJntSet(sz);
        for(int i=0;i<sz;i++)
            disJntSet[i]=i;
        for(int i=0;i<sz;i++){
            for(int j=0;j<=i;j++){
                if(M[i][j]==1){
                    int a=disJntFind(disJntSet, i);
                    int b=disJntFind(disJntSet, j);
                    if(a<b){
                        disJntSet[b]=a;
                    }
                    else if(a>b){
                        disJntSet[a]=b;
                    }
                }
            }
        }
        unordered_set<int> cnt;
        for(int i=0;i<sz;i++){
            cnt.insert(disJntFind(disJntSet, i));
        }
        return cnt.size();
    }
    
    int disJntFind(vector<int>& disJntSet, int index){
        if(disJntSet[index]==index)
            return index;
        stack<int> tempIndex;
        while(disJntSet[index]!=index){
            tempIndex.push(index);
            index=disJntSet[index];
        }
        while(!tempIndex.empty()){
            disJntSet[tempIndex.top()]=index;
            tempIndex.pop();
        }
        return index;
    }
};