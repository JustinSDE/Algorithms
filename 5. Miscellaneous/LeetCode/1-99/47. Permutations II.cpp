class Solution {
public:
	void findpermutation(vector<vector<int>> &res, vector<int> input, int start,
			     int sz) {
	    if (start == sz - 1) {
		res.push_back(move(input));
		return;
	    }
	    for (int i = start; i < sz; i++) {
		if (i != start && input[i] == input[start])
		    continue;
		swap(input[start], input[i]);
		findpermutation(res, input, start + 1, sz);
	    }
	}

	vector<vector<int>> permuteUnique(vector<int> &input) {
	    sort(input.begin(), input.end());
	    int sz = input.size();
	    vector<vector<int>> res;
	    findpermutation(res, input, 0, sz);
	    return res;
	}
};
