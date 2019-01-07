class Vector2D {
  private:
    deque<int> vec;

  public:
    Vector2D(vector<vector<int>> &vec2d) {
        for (auto &ar : vec2d) {
            for (auto x : ar) {
                vec.push_back(x);
            }
        }
    }

    int next() {
        int res = vec.front();
        vec.pop_front();
        return res;
    }

    bool hasNext() { return !vec.empty(); }
};

/**
 * Your Vector2D object will be instantiated and called as such:
 * Vector2D i(vec2d);
 * while (i.hasNext()) cout << i.next();
 */