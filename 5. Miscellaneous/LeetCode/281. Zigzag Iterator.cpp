class ZigzagIterator {
  private:
    deque<int> storage;

  public:
    ZigzagIterator(vector<int> &v1, vector<int> &v2) {
        for (int i = 0; i < v1.size() || i < v2.size(); i++) {
            if (i < v1.size()) {
                storage.push_back(v1[i]);
            }
            if (i < v2.size()) {
                storage.push_back(v2[i]);
            }
        }
    }

    int next() {
        int res = storage.front();
        storage.pop_front();
        return res;
    }

    bool hasNext() { return !storage.empty(); }
};

/**
 * Your ZigzagIterator object will be instantiated and called as such:
 * ZigzagIterator i(v1, v2);
 * while (i.hasNext()) cout << i.next();
 */