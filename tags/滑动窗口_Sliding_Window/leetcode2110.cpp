#include<vector>
using namespace std;



class Solution {
public:
    long long getDescentPeriods(vector<int>& prices) {
        long long ans=0;
        long long count=1;
        for(int i=1;i<prices.size();i++){
            if(prices[i-1]-prices[i]==1){
                count++;
            }
            else{
                ans+= (count*(count+1))/2;
                count=1;
            }
            
        }
        ans+= (count*(count+1))/2;
        return ans;
    }
};