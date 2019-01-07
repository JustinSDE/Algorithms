using namespace std;

class MovingAverage {
  private:
    queue<double> q;
    int n;
    double sum;

  public:
    /** Initialize your data structure here. */
    MovingAverage(int size) : n(size), sum(0) {}

    double next(int val) {
        q.push(val);
        sum += val;
        if (q.size() > (size_t)n) {
            sum -= q.front();
            q.pop();
        }

        return sum / q.size();
    }
};

/**
 * Your MovingAverage object will be instantiated and called as such:
 * MovingAverage obj = new MovingAverage(size);
 * double param_1 = obj.next(val);
 */

#if DEBUG
int main(int argc, char **argv) { return 0; }
#endif

/**
 * Your MovingAverage object will be instantiated and called as such:
 * MovingAverage obj = new MovingAverage(size);
 * double param_1 = obj.next(val);
 */