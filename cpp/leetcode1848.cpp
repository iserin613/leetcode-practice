#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

class Solution {
public:
    int getMinDistance(vector<int>& nums, int target, int start) {
        int i=0;
        int len=nums.size();
        while(start-i>=0 || start+i<len){
            if(start-i>=0 && nums[start-i]==target) return i;
            if(start+i<len && nums[start+i]==target) return i;
            i++;
        }
        return -1;
    }
};