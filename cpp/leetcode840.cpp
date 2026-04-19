#include <vector>
#include <unordered_map>
using namespace std;


class Solution {
private:
    bool ismagicsquare(vector<vector<int>> &grid){
        int sum=grid[0][0]+grid[0][1]+grid[0][2];
        unordered_map<int,int> hash;
        for(int i=0;i<3;i++){
            int rowsum=0;
            int colsum=0;
            for(int j=0;j<3;j++){
                rowsum+=grid[i][j];
                colsum+=grid[j][i];
                hash[grid[i][j]]++;
                
            }
            if(rowsum!=sum||colsum!=sum) return false;
        }
        int diag1=grid[0][0]+grid[1][1]+grid[2][2];
        int diag2=grid[0][2]+grid[1][1]+grid[2][0];
        if(diag1!=sum||diag2!=sum) return false;
        for(int i=1;i<=9;i++){
            if(hash[i]!=1) return false;
        }
        return true;
    }
public:
    int numMagicSquaresInside(vector<vector<int>>& grid) {
        int row=grid.size();
        int col=grid[0].size();
        int count=0;
        for(int i=0;i<=row-3;i++){
            for(int j=0;j<=col-3;j++){
                vector<vector<int>> subgrid(3,vector<int>(3,0));
                for(int x=0;x<3;x++){
                    for(int y=0;y<3;y++){
                        subgrid[x][y]=grid[i+x][j+y];
                    }
                }
                if(ismagicsquare(subgrid)){
                    count++;
                }
            }
        }
        
        return count;
    }
};