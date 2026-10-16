// 4. 寻找两个正序数组的中位数 (Median of Two Sorted Arrays) — 2026-10-16
// 思路：双指针归并，只走到中位位置（total/2）为止；奇数取 cur，偶数取 (prev+cur)/2
// 时间 O(m+n) / 空间 O(1)
// 提交结果：通过 2099/2099 用例，0 ms 击败 100.00%
class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        int m = nums1.size(), n = nums2.size();
        int total = m + n;
        int i = 0, j = 0, prev = 0, cur = 0;
        for (int k = 0; k <= total / 2; ++k) {
            prev = cur;
            if (i < m && (j >= n || nums1[i] <= nums2[j])) cur = nums1[i++];
            else cur = nums2[j++];
        }
        if (total % 2 == 1) return (double)cur;
        return (prev + cur) / 2.0;
    }
};