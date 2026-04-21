class Solution {
    public:
        int maxDistance(vector<int>& nums1, vector<int>& nums2) {
            int len1=nums1.size();
            int len2=nums2.size();
            int ans=0;
            int i=0,j=0;
            while(i<len1&&j<len2){
                if(nums1[i]<=nums2[j]){
                    ans=max(ans,j-i);
                    
                    j++;
                }
                else{
                    
                    i++;
                    }
                    
            }
            while(i<len1){
                if(nums2[len2-1]>=nums1[i]){
                    ans=max(ans,len2-i-1);
                    break;
                }
                i++;
            }
            while(j<len2&&nums1[len1-1]<=nums2[j]){
                j++;
                if(nums1[len1-1]>nums2[j]){
                    ans=max(ans,j-len1+1);

                   
                }
            }
            return ans;
            
        }
};