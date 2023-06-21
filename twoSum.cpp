vector<int> twoSum(vector<int>& nums, int target) {         // nums -> the number list
    int len = nums.size();                                  // len -> length of the number list
    for (int i=0;i<len;i++) {                               // i: loop over the list
        for (int j=i+1;j<len;j++) {                         // j: loop over the list from current iteration
            if (nums[i] + nums[j] == target) return {i,j};  // check every possible combination for the target sum
        }
    }
    return {};                                              // if nothing is found, return empty list
}