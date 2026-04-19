class Solution {
    public:
        int minimumDistance(string word) {
            const int INF = 1e9;
            vector<pair<int, int>> coord(26);
            for (int i = 0; i < 26; ++i) {
                coord[i] = {i / 6, i % 6};
            }

            auto dist = [&](int a, int b) {
                return abs(coord[a].first - coord[b].first) +
                       abs(coord[a].second - coord[b].second);
            };

            vector<vector<int>> dp(27,vector<int>(27,INF));
            dp[26][26]=0;

            auto movecost=[&](int from,int to){
                if(from==26) return 0;
                return dist(from,to);
            };

            for(int i=0;i<word.size();i++){
                int c=word[i]-'A';
                vector<vector<int>> ndp(27,vector<int>(27,INF));
                for(int a=0;a<=26;a++){
                    for(int b=0;b<=26;b++){
                        if (dp[a][b] == INF) continue;
                        ndp[c][b]=min(ndp[c][b],dp[a][b]+movecost(a,c));
                        ndp[a][c]=min(ndp[a][c],dp[a][b]+movecost(b,c));

                    }
                }
                dp.swap(ndp);
        }
        int ans=INF;
        for(int a=0;a<=26;a++){
            for(int b=0;b<=26;b++){
                ans=min(ans,dp[a][b]);
            }
        }
        return ans;
    }
};