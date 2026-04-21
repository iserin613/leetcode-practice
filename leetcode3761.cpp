class Solution {
    public:
        int minMirrorPairDistance(vector<int>& nums) {
            unordered_map<int,int> map;

            int n=nums.size();
            int ans=1e9;
            auto rev=[&](int x){
                int rev=0;
                while(x>0){
                    rev=10*rev+x%10;
                    x=x/10;
                }
                return rev;
            };
            for(int i=0;i<n;i++){
                int temp=rev(nums[i]);
                if(map.find(nums[i])!=map.end()){
                    ans=min(ans,i-map[nums[i]]);
                }
               
                map[temp]=i;

            }
            return ans==1e9?-1:ans;

    }
};