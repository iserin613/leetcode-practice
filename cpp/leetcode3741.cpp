#include <vector>
#include <algorithm>
#include<unordered_map>
#include<iostream>
using namespace std;


class Solution {
public:
    int minimumDistance(vector<int>& nums) {
        vector<int> appeared;
        int len=nums.size();
        unordered_map<int,vector<int>> hash;
        unordered_map<int,bool> visited;
        for(int i=0;i<len;i++){
            hash[nums[i]].push_back(i);
            if(visited[nums[i]]==false){
                appeared.push_back(nums[i]);
                visited[nums[i]]=true;
            }
        }
        int len2=appeared.size();
        int ans=INT_MAX;
        for(int i=0;i<len2;i++){
            if(hash[appeared[i]].size()>2){
                for(int j=0;j<hash[appeared[i]].size()-2;j++){
                    
                        int left=hash[appeared[i]][j];
                        int right=hash[appeared[i]][j+2];
                        if(2*(right-left)<ans) 
                        ans=2*(right-left);
                    
                }
            }
                
               
        }
        if(ans==INT_MAX) return -1;
        return ans;
    }
        
};

int main(){
    Solution s;
    vector<int> nums={5,5,5,2,5};
    cout<<s.minimumDistance(nums)<<endl;
    
}
