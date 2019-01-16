class Solution {
public:
    string addBinary(string a, string b) {
        if(a.length()<b.length())
            return addBinary(b,a);
        string res=a;
        int indexa=a.size()-1;
        int indexb=b.size()-1;
        int sum;
        int carry=0;
        while(indexa>=0||indexb>=0)
        {
            sum=carry;
            if (a[indexa] == '1')
                sum++;
            if (indexb >= 0 && b[indexb] == '1')
                sum++;
            carry=sum/2;
            sum=sum%2;
            res[indexa]=(sum==1?'1':'0');
            indexa--;
            indexb--;
        }
        if(carry==1)
            res="1"+res;
        return res;
    }
};
