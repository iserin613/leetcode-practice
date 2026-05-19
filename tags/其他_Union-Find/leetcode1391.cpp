class Solution {
    public:
        
        bool dfs(vector<vector<int>>& grid,int x,int y,vector<vector<bool>>& visited){
            int m=grid.size();
            int n=grid[0].size();
            if(x==m-1 && y==n-1) return true;
            visited[x][y]=true;

            switch(grid[x][y]){
                case 1:
                if(y+1<n && (grid[x][y+1]==1 || grid[x][y+1]==3 || grid[x][y+1]==5)&& !visited[x][y+1]){
                    if(dfs(grid,x,y+1,visited)) return true;
                }
                if(y-1>=0 && (grid[x][y-1]==1 || grid[x][y-1]==4 || grid[x][y-1]==6)&& !visited[x][y-1]){
                    if(dfs(grid,x,y-1,visited)) return true;
                }
                return false;
                
                case 2:
                if(x+1<m && (grid[x+1][y]==2 || grid[x+1][y]==5 || grid[x+1][y]==6)&& !visited[x+1][y]){
                    if(dfs(grid,x+1,y,visited)) return true;
                }
                if(x-1>=0 && (grid[x-1][y]==2 || grid[x-1][y]==3 || grid[x-1][y]==4)&& !visited[x-1][y]){
                    if(dfs(grid,x-1,y,visited)) return true;
                }
                return false;
                case 3:
                if(y-1>=0 && (grid[x][y-1]==1 || grid[x][y-1]==4 || grid[x][y-1]==6)&& !visited[x][y-1]){
                    if(dfs(grid,x,y-1,visited)) return true;
                }
                if(x+1<m && (grid[x+1][y]==2 || grid[x+1][y]==5 || grid[x+1][y]==6)&& !visited[x+1][y]){
                    if(dfs(grid,x+1,y,visited)) return true;
                }
                return false;
                case 4:
                if(x+1<m && (grid[x+1][y]==2 || grid[x+1][y]==5 || grid[x+1][y]==6)&& !visited[x+1][y]){
                    if(dfs(grid,x+1,y,visited)) return true;
                }
                if(y+1<n && (grid[x][y+1]==1 || grid[x][y+1]==3 || grid[x][y+1]==5)&& !visited[x][y+1]){
                    if(dfs(grid,x,y+1,visited)) return true;
                }
                return false;
                case 5:
                if(x-1>=0 && (grid[x-1][y]==2 || grid[x-1][y]==3 || grid[x-1][y]==4)&& !visited[x-1][y]){
                    if(dfs(grid,x-1,y,visited)) return true;
                }
                if(y-1>=0 && (grid[x][y-1]==1 || grid[x][y-1]==4 || grid[x][y-1]==6)&& !visited[x][y-1]){
                    if(dfs(grid,x,y-1,visited)) return true;
                }
                return false;
                case 6:
                if(x-1>=0 && (grid[x-1][y]==2 || grid[x-1][y]==3 || grid[x-1][y]==4)&& !visited[x-1][y]){
                    if(dfs(grid,x-1,y,visited)) return true;
                }
                if(y+1<n && (grid[x][y+1]==1 || grid[x][y+1]==3 || grid[x][y+1]==5)&& !visited[x][y+1]){
                    if(dfs(grid,x,y+1,visited)) return true;
                }
                return false;
                
        }
        return false;


    }

    bool hasValidPath(vector<vector<int>>& grid) {
        int m=grid.size();
        int n=grid[0].size();
        vector<vector<bool>> visited(m,vector<bool>(n,false));
        return dfs(grid,0,0,visited);

       
        
    }
};