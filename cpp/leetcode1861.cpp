class Solution {
    public:
        vector<vector<char>> rotateTheBox(vector<vector<char>>& boxGrid) {
            int m=boxGrid.size();
            int n=boxGrid[0].size();
            vector<vector<char>> ans(n,vector<char>(m,'.'));
            for(int i=0;i<n;i++){
                for(int j=0;j<m;j++){
                    ans[i][j]=boxGrid[j][i];
                }
            }
            for(int i=0;i<n;i++){
                for(int j=0;j<m/2;j++){
                    char temp=ans[i][m-1-j];
                    ans[i][m-1-j]=ans[i][j];
                    ans[i][j]=temp;
    
                }
            }
            for(int j=0;j<m;j++){
                int obstacle=n;
                for(int i=n-1;i>=0;i--){
                    if(ans[i][j]=='#'){
                        if(i==obstacle-1) {
                            obstacle--;
                            continue;
                        };
                        else{
                        ans[obstacle-1][j]='#';
                        obstacle--;
                        ans[i][j]='.';}
                        
                    }
                    else if(ans[i][j]=='*'){
                        obstacle=i;
                    }
                    else continue;
                }
            }
            return ans;
            
        }
    };