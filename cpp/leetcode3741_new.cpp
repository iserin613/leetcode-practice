class Solution {
    public:
        int minimumDistance(vector<int>& nums) {
            int len=nums.size();
            vector<int> next(len,-1);
            unordered_map<int,int> appear;
            for(int i=len-1;i>=0;i--){
                if(appear.count(nums[i])!=0){
                    next[i]=appear[nums[i]];
                }
                appear[nums[i]]=i;
            }
            int ans=INT_MAX;
            for(int i=0;i<len;i++){
                if(next[i]!=-1 && next[next[i]]!=-1){
                    int left=i;
                    int right=next[next[i]];
                    if(2*(right-left)<ans) 
                    ans=2*(right-left);
                }
            }
            return ans==INT_MAX?-1:ans;
    
        }
    };