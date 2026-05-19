class Solution {
public:
    vector<int> maxValue(vector<int>& nums) {
        int n = nums.size();
        vector<int> ans(n);
        if (n == 0) return ans;

        // sufMin[i] = nums[i..n-1] 的最小值，用于判断分界两侧是否有逆序对
        vector<int> sufMin(n);
        sufMin[n - 1] = nums[n - 1];
        for (int i = n - 2; i >= 0; --i) {
            sufMin[i] = min(sufMin[i + 1], nums[i]);
        }

        int start = 0;
        int curMax = nums[0];
        for (int i = 0; i < n; ++i) {
            curMax = max(curMax, nums[i]);

            // curMax <= rightMin 说明该边界两侧不存在逆序对，可切成不同连通块
            bool canSplit = (i == n - 1) || (curMax <= sufMin[i + 1]);
            if (canSplit) {
                for (int j = start; j <= i; ++j) {
                    ans[j] = curMax;
                }
                start = i + 1;
                if (start < n) curMax = nums[start];
            }
        }

        return ans;
    }
};