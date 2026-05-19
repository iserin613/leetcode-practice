class Solution {
    public:
        int minJumps(vector<int>& nums) {
            int n = nums.size();
            unordered_map<int, vector<int>> hash;
            for (int i = 0; i < n; i++) {
                int x = nums[i];
                if (x == 1) continue;
                for (int j = 2; 1LL * j * j <= x; j++) {
                    if (x % j == 0) {
                        hash[j].push_back(i);
                        while (x % j == 0) x /= j;
                    }
                }
                if (x > 1) hash[x].push_back(i);
            }

            auto isPrime = [&](int x) -> bool {
                if (x < 2) return false;
                for (int d = 2; 1LL * d * d <= x; d++) {
                    if (x % d == 0) return false;
                }
                return true;
            };

            vector<bool> visited(n, false);
            queue<int> q;
            q.push(0);
            visited[0] = true;
            int steps = 0;

            while (!q.empty()) {
                int sz = q.size();
                while (sz--) {
                    int i = q.front();
                    q.pop();
                    if (i == n - 1) return steps;

                    if (i - 1 >= 0 && !visited[i - 1]) {
                        visited[i - 1] = true;
                        q.push(i - 1);
                    }
                    if (i + 1 < n && !visited[i + 1]) {
                        visited[i + 1] = true;
                        q.push(i + 1);
                    }

                    int val = nums[i];
                    if (isPrime(val) && hash.count(val)) {
                        for (int j : hash[val]) {
                            if (!visited[j]) {
                                visited[j] = true;
                                q.push(j);
                            }
                        }
                        hash.erase(val);
                    }
                }
                steps++;
            }

            return -1;
        }
    };