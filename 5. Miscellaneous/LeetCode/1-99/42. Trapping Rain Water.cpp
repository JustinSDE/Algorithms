class Solution
{
  public:
    int trap(vector<int> &height)
    {
        if (height.empty())
            return 0;
        int indexleft = 0, indexright = height.size() - 1, sum = 0, maxleft = height[indexleft], maxright = height[indexright];
        while (indexleft < indexright)
        {
            if (maxleft <= maxright)
            {
                indexleft++;
                sum += max(0, maxleft - height[indexleft]);
                maxleft = max(maxleft, height[indexleft]);
            }
            else
            {
                indexright--;
                sum += max(0, maxright - height[indexright]);
                maxright = max(maxright, height[indexright]);
            }
        }
        return sum;
    }
};