class Solution {
    public:
        vector<int> solveQueries(vector<int>& nums, vector<int>& queries) {
            int n = nums.size();
            unordered_map<int, vector<int>> pos;
            for (int i = 0; i < n; ++i) {
                pos[nums[i]].push_back(i);
            }

            vector<int> best(n, -1);
            for (auto& [_, v] : pos) {
                int m = v.size();
                if (m <= 1) {
                    continue;
                }
                for (int t = 0; t < m; ++t) {
                    int cur = v[t];
                    int pre = v[(t - 1 + m) % m];
                    int nxt = v[(t + 1) % m];
                    int d1 = abs(cur - pre);
                    int d2 = abs(cur - nxt);
                    best[cur] = min(min(d1, n - d1), min(d2, n - d2));
                }
            }

            vector<int> ans;
            ans.reserve(queries.size());
            for (int idx : queries) {
                ans.push_back(best[idx]);
            }

            return ans;
        }
};