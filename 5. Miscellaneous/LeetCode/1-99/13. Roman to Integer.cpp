/**
 * key idea: scan in the reverse order
 */
class Solution {
public:
    // convert single numeral to int
    int convertSingularToInt(const char c)
    {
        switch(c){
            case 'M':
                return 1000;
            case 'D':
                return 500;                
            case 'C':
                return 100;                
            case 'L':
                return 50;                
            case 'X':
                return 10;                
            case 'V':
                return 5;                
            case 'I':
                return 1;                
        }
        return 0;
    }
    
    // converts combination of roman numerals into the corresponding integer number
    int romanToInt(string s) {        
        int n = s.length(); 
        int prev = convertSingularToInt(s[0]), curr = 0, sum = 0;
        for(int i = 1; i < n; i++){
            curr = convertSingularToInt(s[i]);
            if(prev < curr)
                sum -= prev;
            else
                sum += prev;
            prev = curr;
        }
        sum += prev;

        return sum;
    }
};
