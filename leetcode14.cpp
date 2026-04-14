#include <vector>
#include <string>
#include <algorithm>
#include<iostream>

using namespace std;


class Solution {
public:
    string longestCommonPrefix(vector<string>& strs) {
        string prefix=strs[0];
        for(int i=1;i<strs.size();i++){

           string temp="";
            for(int j=0;j<prefix.length() && j<strs[i].length();j++){
                    if(prefix[j]==strs[i][j]){
                        temp+=prefix[j];
                    }
                    else break;
                }
            prefix=temp;
            if(prefix.length()==0) return "";
     
       
}
 return prefix;
}};