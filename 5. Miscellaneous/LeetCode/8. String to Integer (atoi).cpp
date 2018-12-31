class Solution {
public:
    int myAtoi(string str) {
        long long num=0;
        bool negative = false;
        int index = 0, sz = str.length();
        while(index<sz && str[index]==' '){
            index++;
        }
        if(index<sz){
            if(str[index]=='-'){
                negative = true;
                index++;
            }
            else if(str[index]=='+')
            {index++;}
        }
        
        while(index<sz && num <= INT_MAX){
            char c = str[index];
            index++;
            if(c>='0' && c<='9'){
                num=num*10+c-'0';
            }
            else{
                break;
            }
        }
        if(negative){
            num = -num;
        }
        if(num<INT_MIN)
            return INT_MIN;
        if(num>INT_MAX)
            return INT_MAX;
        return num;
    }
};
