class Solution {
  public:
    bool isValid(string s) {
        stack<char> st;
        for (auto ch : s) {
            if (ch == ')') {
                if (st.empty() || st.top() != '(')
                    return false;
                else
                    st.pop();
            } else if (ch == ']') {
                if (st.empty() || st.top() != '[')
                    return false;
                else
                    st.pop();
            } else if (ch == '}') {
                if (st.empty() || st.top() != '{')
                    return false;
                else
                    st.pop();
            } else
                st.push(ch);
        }
        return st.empty();
    }
};

class Solution2 {
public:
    bool isValid(string s) {
        stack<char> unpaired_parentheses;
        for(auto ch:s){
            switch(ch){
                case '(':
                case '[':
                case '{':
                    unpaired_parentheses.push(ch);
                    break;
                case ')':
                    if(unpaired_parentheses.empty() || unpaired_parentheses.top()!='(')
                        return false;
                    else
                        unpaired_parentheses.pop();
                    break;
                case ']':
                    if(unpaired_parentheses.empty() || unpaired_parentheses.top()!='[')
                        return false;
                    else
                        unpaired_parentheses.pop();
                    break;
                case '}':
                    if(unpaired_parentheses.empty() || unpaired_parentheses.top()!='{')
                        return false;
                    else
                        unpaired_parentheses.pop();
                    break;
                default:
                    return false;
                    break;
            }
        }
        return unpaired_parentheses.empty();
    }
};
