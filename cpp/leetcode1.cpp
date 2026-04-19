#include <vector>
#include <unordered_map>
using namespace std;

class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        vector<int> twoSum;
        unordered_map<int,int> hash;
        for(int i=0;i<nums.size();i++){
            auto it=hash.find(target-nums[i]);
            if(it!=hash.end()){
                twoSum.push_back(it->second);
                twoSum.push_back(i);
                return twoSum; 

            }
            hash[nums[i]]=i;
        }
        
    }
};