class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        int len1 = nums1.size();
       	int len2 = nums2.size();
        if (len1 < len2) return findMedianSortedArrays(nums2, nums1);

        int l = 0, r = len2 * 2;
        while (l <= r) {

            int mid2 = (l + r) / 2;
            int mid1 = len1 + len2 - mid2;

            double mid1_l = (mid1 == 0) ? INT_MIN : nums1[(mid1 - 1) / 2];
            double mid2_l = (mid2 == 0) ? INT_MIN : nums2[(mid2 - 1) / 2];
            double mid1_r = (mid1 == len1 * 2) ? INT_MAX : nums1[(mid1) / 2];
            double mid2_r = (mid2 == len2 * 2) ? INT_MAX : nums2[(mid2) / 2];

            if (mid1_l > mid2_r) l = mid2 + 1;
            else if (mid2_l > mid1_r) r = mid2 - 1;
            else return (max(mid1_l, mid2_l) + min(mid1_r, mid2_r)) / 2;

        }

        return -1;

    }
};