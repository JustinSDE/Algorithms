class Solution {
public:
    int maxArea(vector<int>& height) {
        int area_max = 0;
        int minHeight = 0;
        int left_minHeight, right_minHeight;
        int leftIndex=0, rightIndex=height.size()-1;
        while(leftIndex<rightIndex){
            while(leftIndex<rightIndex && height[leftIndex]<=minHeight){
                leftIndex++;
            }
            left_minHeight = height[leftIndex];
            while(rightIndex>leftIndex && height[rightIndex]<=minHeight){
                rightIndex--;
            }
            right_minHeight = height[rightIndex];
            minHeight = min(left_minHeight, right_minHeight);
            area_max = max(area_max, minHeight*(rightIndex-leftIndex));
        }
        return area_max;
    }
};
