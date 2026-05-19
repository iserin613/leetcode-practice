class Solution {
    public:
        bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
            int n=numCourses;
            vector<vector<int>> graph(n,vector<int>(n,0));
            int m=prerequisites.size();
            vector<int> out_degree(n,0);
            for(int i=0;i<m;i++){
                graph[prerequisites[i][0]][prerequisites[i][1]]=1;
                out_degree[prerequisites[i][0]]++;
            }
            vector<int> visited(n,0);
            for(int i=0;i<n;i++){
                if(visited[i]==0){
                    if(!dfs(i,graph,out_degree,visited)){
                        return false;
                    }
                }
            }
            return true;
            
        }
    private:
    bool dfs(int node, vector<vector<int>>& graph, vector<int>& out_degree, vector<int>& visited){
        if(visited[node]==1) return false;
        if(visited[node]==2) return true;
        visited[node]=1;
        if(out_degree[node]==0) {
            visited[node]=2;
            return true;

        }
        for(int i=0;i<graph[node].size();i++){
            if(graph[node][i]==1){
                if(!dfs(i,graph,out_degree,visited)){
                    return false;
                }
            }
        }
        visited[node]=2;
        return true;
        }
       

    };