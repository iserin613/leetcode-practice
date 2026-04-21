class Solution {
    public:
        

        struct DSU{             //并查集，构造连通子图
            vector<int> parent,sz;
            DSU(int n):parent(n),sz(n,1){
                iota(parent.begin(),parent.end(),0);

            }
            int find(int x){    //找寻父节点
                if(parent[x]!=x){
                    parent[x]=find(parent[x]);
                }
                return parent[x];
            }
            void Union(int x,int y){
                int rootx=find(x);
                int rooty=find(y);
                if(rootx==rooty) return;
                if(sz[rootx]<sz[rooty]){
                    swap(rootx,rooty);
                }
                parent[rooty]=rootx;
                sz[rootx]+=sz[rooty];
            }
        };
        int minimumHammingDistance(vector<int>& source, vector<int>& target, vector<vector<int>>& allowedSwaps) {
            int n=source.size();
            int m=allowedSwaps.size();
            int ans=0;
            DSU DSU(n);
            for(int i=0;i<m;i++){
                DSU.Union(allowedSwaps[i][0],allowedSwaps[i][1]);
            }

        
            unordered_map<int,unordered_map<int,int>> hash;
            for(int i=0;i<n;i++){
            hash[DSU.find(i)][source[i]]++;
            }
            for(int i=0;i<n;i++){
                if(hash[DSU.find(i)][target[i]]>0){
                   hash[DSU.find(i)][target[i]]--;
                }
            else ans++;
            }   
        return ans;
        }

        
};