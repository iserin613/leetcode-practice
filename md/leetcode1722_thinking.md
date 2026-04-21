# 最小汉明距离

- allow数组实际上是在连通两个下标对应的节点 通过加载allow数组我们能够构造连通的子图，其中的元素可以任意排列
- 这样 我们可以将下表分为不同的集合 并通过一个父节点来标记该集合 这就是并查集 
## 并查集

- 构造
```c++
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
```
find函数可通过递归回溯找到父节点
union函数可将节点加入子图 并且将小的图并入大的图

# 在本题中
定义哈希表`unordered_map<int,unordered_map<int,int>>`
第一个int位是该下标对应的根节点下标 第二个是source[i] 最后一个记录source[i]在该子图中出现的次数
遍历target时若`hash[DSU.find(i)][target[i]]>0`则将该数字的次数减一 否则直接将汉明距离加一

