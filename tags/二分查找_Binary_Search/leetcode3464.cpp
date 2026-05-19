class Solution {
    public:
        int maxDistance(int side, vector<vector<int>>& points, int k) {
            using ll = long long;
            int len = points.size();
            ll S = (ll)side;
            auto dist = [&](ll x1, ll y1, ll x2, ll y2) {
                return llabs(x1 - x2) + llabs(y1 - y2);
            };
            auto to_t = [&](ll x, ll y) -> ll {
                if (y == 0) return x;
                if (x == S) return S + y;
                if (y == S) return 3LL * S - x;
                return 4LL * S - y;
            };
            vector<array<ll, 3>> a; // {t, x, y}
            a.reserve(len);
            for (auto &p : points) {
                ll x = p[0], y = p[1];
                a.push_back({to_t(x, y), x, y});
            }
            sort(a.begin(), a.end());
            ll L = 4LL * S;
            vector<array<ll, 3>> b(2 * len);
            for (int i = 0; i < len; ++i) {
                b[i] = a[i];
                b[i + len] = {a[i][0] + L, a[i][1], a[i][2]};
            }
            auto buildNext = [&](ll D) {
                // next[i]: 从 i 往后第一个满足“弧长差 >= D”的位置
                // 若不存在，置为 2n（哨兵）
                vector<int> nxt(2 * len, 2 * len);
            
                int r = 0;
                for (int i = 0; i < 2 * len; ++i) {
                    if (r < i + 1) r = i + 1;
            
                    // 只在一圈范围内找：i+n-1 是最后可用位置
                    while (r < 2 * len && r < i + len && b[r][0] - b[i][0] < D) {
                        ++r;
                    }
            
                    if (r < 2 * len && r < i + len) nxt[i] = r;
                    // else 保持 2n
                }
                return nxt;
            };

            auto check = [&](long long D) -> bool {
                int n = len;
                auto nxt = buildNext(D);

                for (int s = 0; s < n; ++s) {
                    vector<int> picked;
                    picked.push_back(s);

                    for (int i = nxt[s]; i < s + n && (int)picked.size() < k; i = nxt[i]) {
                        bool ok = true;
                        for (int id : picked) {
                            ll d = dist(b[i][1], b[i][2], b[id][1], b[id][2]);
                            if (d < D) { ok = false; break; }
                        }
                        if (ok) picked.push_back(i);
                    }

                    if ((int)picked.size() >= k) return true;
                }
                return false;
            };

            ll lo = 0, hi = 2LL * S;
            while (lo < hi) {
                ll mid = (lo + hi + 1) / 2;
                if (check(mid)) lo = mid;
                else hi = mid - 1;
            }
            return (int)lo;
        }
    };