class Solution {
  public:
    int totalFruit(vector<int> &tree) {
        int start, end, count, maxCount;
        unordered_map<int, int> m;

        start = end = 0;
        count = 0;
        maxCount = INT_MIN;

        while (start <= end && end < tree.size()) {
            if (m.find(tree[end]) == m.end()) {
                if (m.size() == 2) {
                    m[tree[start]] = m[tree[start]] - 1;

                    if (m[tree[start]] == 0) {
                        m.erase(tree[start]);
                    }

                    start++;
                    count--;
                } else {
                    m[tree[end]] = m[tree[end]] + 1;
                    end++;
                    count++;
                }
            } else {
                m[tree[end]] = m[tree[end]] + 1;
                count++;
                end++;
            }

            if (maxCount < count) {
                maxCount = count;
            }
        }
        return maxCount;
    }
};