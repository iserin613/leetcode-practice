class Solution {
    public:
        int closestTarget(vector<string>& words, string target, int startIndex) {
            int len=words.size();
            int ans=INT_MAX;
            for(int i=0;i<len;i++){
                if(words[(startIndex+i)%len]==target){
                    int ans0=min(i,len-i);
                    if(ans0<ans) ans=ans0;
                }

            }
            return ans==INT_MAX?-1:ans;
        }
    };