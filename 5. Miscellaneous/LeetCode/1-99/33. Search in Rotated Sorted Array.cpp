class Solution {
  public:
    int search(vector<int> &nums, int target) {
        int left = 0, right = nums.size() - 1, mid;
        int left_val, right_val, mid_val;
        while (left <= right) {

            mid = left + (right - left) / 2;
            left_val = nums[left];
            right_val = nums[right];
            mid_val = nums[mid];

            if (mid_val == target) {
                return mid;
            }
            if (target == left_val)
                return left;
            if (target == right_val)
                return right;

            // 3 different cases for the mid value;
            if (left_val <= mid_val && mid_val < right_val) {
                if (target > mid_val) {
                    left = mid + 1;
                } else {
                    right = mid - 1;
                }
            } else if (left_val <= mid_val && mid_val > right_val) {
                if (target > mid_val) {
                    left = mid + 1;
                } else if (target >= left_val) {
                    right = mid - 1;
                } else {
                    left = mid + 1;
                }
            } else { // left_val > mid_val && mid_val < right_val
                if (target < mid_val) {
                    right = mid - 1;
                } else if (target >= left_val) {
                    right = mid - 1;
                } else {
                    left = mid + 1;
                }
            }
        }
        return -1;
    }
};

class Solution2 {
  public:
    int search(vector<int> &nums, int target) {
        int left = 0, right = nums.size() - 1, mid;
        int left_val, right_val, mid_val;
        while (left <= right) {

            mid = left + (right - left) / 2;
            left_val = nums[left];
            right_val = nums[right];
            mid_val = nums[mid];

            if (mid_val == target) {
                return mid;
            }

            // condition for left = mid +1;
            if (left_val <= mid_val && target > mid_val ||
                target < left_val && left_val <= mid_val &&
                    mid_val > right_val ||
                target > mid_val && target < left_val)
                left = mid + 1;
            else
                right = mid - 1;

            /*
            rewrite to simplify the cases
            // 3 different cases for the mid value;
            if(left_val <= mid_val && mid_val<right_val ){
                if(target > mid_val){
                    left = mid+1;
                }
                else{
                    right = mid-1;
                }
            }
            else if(left_val<= mid_val && mid_val > right_val){
                if(target > mid_val){
                    left = mid+1;
                }
                else if(target >=left_val){
                    right = mid-1;
                }
                else{
                    left = mid+1;
                }
            }
            else{   // left_val > mid_val && mid_val < right_val
                if(target < mid_val){
                    right = mid - 1;
                }
                else if(target >= left_val){
                    right = mid-1;
                }
                else{
                    left = mid + 1;
                }
            } */
        }
        return -1;
    }
};
