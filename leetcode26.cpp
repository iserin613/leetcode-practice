#include <vector>
#include<algorithm>
using namespace std;




class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        vector<int> ans;
        ans.push_back(nums[0]);
        int index=0;
        int k=1;
        for(int i=1;i<nums.size();i++){
        if(nums[i]!=ans[index]){
            ans.push_back(nums[i]);
            index++;
            k++;
        }
        }
        for(int i=0;i<k;i++){
            nums[i]=ans[i];
        }
        return k;
    }
};