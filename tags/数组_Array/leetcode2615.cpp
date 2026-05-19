class Solution {
    public:
        vector<long long> distance(vector<int>& nums) {
            int len = nums.size();
            vector<long long> ans(len, 0);
            unordered_map<int, vector<int>> idx;
            unordered_map<int, vector<long long>> prefix;

            for (int i = 0; i < len; i++) {
                idx[nums[i]].push_back(i);
            }

            for (auto &kv : idx) {
                int val = kv.first;
                vector<int> &positions = kv.second;
                int m = positions.size();

                // prefix[val][k] 表示 positions 前 k 个下标之和
                prefix[val] = vector<long long>(m + 1, 0);
                for (int i = 0; i < m; i++) {
                    prefix[val][i + 1] = prefix[val][i] + positions[i];
                }

                for(int i=0;i<m;i++){
                    long long cur=positions[i];
                    long long left=cur*i-prefix[val][i];
                    long long right=(prefix[val][m]-prefix[val][i+1])-cur*(m-i-1);
                    ans[cur]=left+right;
                }
            }

            return ans;
        }
    };