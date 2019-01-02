// 45 ms solution
class Solution1 {
public:
    const static string THOUS[];
    const static string HUNDS[];
    const static string TENS[];
    const static string ONES[];
    string intToRoman(int num) {
        string result;
        result+=THOUS[(int)(num/1000)%10];
        result+=HUNDS[(int)(num/100)%10];
        result+=TENS[(int)(num/10)%10];
        result+=ONES[num%10];
        return result;
    }
};

const string Solution::THOUS[]={"","M","MM","MMM"};
const string Solution::HUNDS[]={"","C","CC","CCC","CD","D","DC","DCC","DCCC","CM"};
const string Solution::TENS[]={"","X","XX","XXX","XL","L","LX","LXX","LXXX","XC"};
const string Solution::ONES[]={"","I","II","III","IV","V","VI","VII","VIII","IX"};


// 135 ms solution
class Solution2 {
public:
    string intToRoman(int num) {
        static vector<string> ones = {"","I","II","III","IV","V","VI","VII","VIII","IX"};
        static vector<string> tens = {"","X","XX","XXX","XL","L","LX","LXX","LXXX","XC"};
        static vector<string> hundreds = {"","C","CC","CCC","CD","D","DC","DCC","DCCC","CM"};
        static vector<string> thousands = {"","M","MM","MMM"};
        stack<int> digits;
        while(num!=0){
            digits.push(num%10);
            num/=10;
        }
        string roman_num_str;
        while(!digits.empty()){
            switch(digits.size()){
                case 4:
                    roman_num_str+=thousands[digits.top()];
                    break;
                case 3:
                    roman_num_str+=hundreds[digits.top()];
                    break;
                case 2:
                    roman_num_str+=tens[digits.top()];
                    break;
                case 1:
                    roman_num_str+=ones[digits.top()];
                    break;
                default:
                    break;
            }
            digits.pop();
        }
        return roman_num_str;
    }
};
