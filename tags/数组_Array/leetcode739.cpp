class Solution {
    public:
        vector<int> dailyTemperatures(vector<int>& temperatures) {
            int n=temperatures.size();
            vector <int> ans(n,0);
            stack<pair<int,int>> s;
            for(int i=0;i<n;i++){
                while(!s.empty()){
                    if(temperatures[i]>s.top().first){
                        ans[s.top().second]=i-s.top().second;
                        s.pop();
                    }
                    else{
                        s.push({temperatures[i],i});
                        break;
                    }
                }
                s.push({temperatures[i],i});
            }
            return ans;
            
        }
    };