#include <vector>
using namespace std;


class Solution {
public:
    int countNegatives(vector<vector<int>>& grid) {
        int m=grid.size();
        int n=grid[0].size();
        int i=m-1;
        int count=0;
        for(int j=0;j<n;j++){
            
            while(i>=0 && grid[i][j]<0){
                i--;
            }
            count+=m-1-i;

        }
        return count;

        
    }
};