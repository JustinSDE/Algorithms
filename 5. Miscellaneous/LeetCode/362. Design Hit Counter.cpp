class HitCounter {
  public:
  public:
    /** Initialize your data structure here. */
    queue<int> q;
    HitCounter() {}

    /** Record a hit.
        @param timestamp - The current timestamp (in seconds granularity). */
    void hit(int timestamp) {
        while (!q.empty() and timestamp - q.front() >= 300)
            q.pop();
        q.push(timestamp);
    }

    /** Return the number of hits in the past 5 minutes.
        @param timestamp - The current timestamp (in seconds granularity). */
    int getHits(int timestamp) {
        while (!q.empty() and timestamp - q.front() >= 300)
            q.pop();
        return q.size();
    }
};

/**
 * Your HitCounter object will be instantiated and called as such:
 * HitCounter obj = new HitCounter();
 * obj.hit(timestamp);
 * int param_2 = obj.getHits(timestamp);
 */