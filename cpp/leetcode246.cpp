#include <string>
#include<unordered_map>
using namespace std;


class Solution {
public:
    bool isAnagram(string s, string t) {
        if(s.length()!=t.length()) return false;
        unordered_map<char,int> hash;
        for(int i=0;i<s.length();i++){
            hash[s[i]]++;
            hash[t[i]]--;
        }
        for(auto it:hash){
            if(it.second!=0) return false;
        }
        return true;

        
        
    }
};