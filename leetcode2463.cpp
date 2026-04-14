#include <vector>
#include <algorithm>
#include <climits>
#include <cstdlib>
#include <iostream>
using namespace std;

class Solution {
    public:
        long long minimumTotalDistance(vector<int>& robot, vector<vector<int>>& factory) {
            sort(robot.begin(),robot.end());
            sort(factory.begin(),factory.end());
            int len1=robot.size();
            int len2=factory.size();
            const long long INF = 4000000000000000000LL;
            vector<vector<long long>> robot_factory(len1+1,vector<long long>(len2+1,INF));
            robot_factory[0][0]=0;
            for(int i=1;i<=len1;i++){
                robot_factory[i][0]=INF;
            }
            for(int j=1;j<=len2;j++){
               robot_factory[0][j]=0;
               for(int i=1;i<=len1;i++){
                robot_factory[i][j]=robot_factory[i][j-1];
               
               long long cost=0;
               for(int k=1;k<=min(i,factory[j-1][1]);++k){
                cost+=llabs(1LL*robot[i-k]-factory[j-1][0]);
                if(robot_factory[i-k][j-1]!=INF){
                    robot_factory[i][j]=min(robot_factory[i][j],robot_factory[i-k][j-1]+cost);
                }
               }
            }
            }
            return robot_factory[len1][len2];
        }
        
    };

int main(){
    Solution s;
    vector<int> robot={1,-1};
    vector<vector<int>> factory={{1,3},{2,2}};
    cout<<s.minimumTotalDistance(robot,factory)<<endl;
    return 0;
}