class Solution {
  public:
    int uniqueMorseRepresentations(vector<string> &words) {
        std::vector<std::string> const morse_abc_ = {
            ".-",   "-...", "-.-.", "-..",  ".",    "..-.", "--.",
            "....", "..",   ".---", "-.-",  ".-..", "--",   "-.",
            "---",  ".--.", "--.-", ".-.",  "...",  "-",    "..-",
            "...-", ".--",  "-..-", "-.--", "--.."};
        string str;
        unordered_set<string> codes;
        for (auto &word : words) {
            str.clear();
            for (auto ch : word) {
                str += morse_abc_[ch - 'a'];
            }
            codes.insert(str);
        }
        return codes.size();
    }
};