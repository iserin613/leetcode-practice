#include<vector>
#include<string>
using namespace std;


class Solution {
public:
    int bestClosingTime(string customers) {
        int min=0;
        int ans=0;
        int count=0;
        
        for(int i=0;i<customers.size();i++){
            count++;
            if(customers[i]=='Y') count-=2;
            if(count<min){
                min=count;
                ans=i+1;
            }
            
        }
        return ans;
        
    }
};