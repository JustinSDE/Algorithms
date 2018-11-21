class Solution {
  public:
    vector<int> asteroidCollision(vector<int> &asteroids) {
        vector<int> res;
        for (auto x : asteroids) {
            if (x > 0)
                res.push_back(x);
            else {
                while (true) {
                    if (res.empty() || res.back() < 0) {
                        res.push_back(x);
                        break;
                    } else {
                        if (res.back() > -x)
                            break;
                        else if (res.back() == -x) {
                            res.pop_back();
                            break;
                        } else {
                            res.pop_back();
                        }
                    }
                }
            }
        }
        return res;
    }
};