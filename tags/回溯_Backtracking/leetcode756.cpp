#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
using namespace std;


class Solution {
public:
    unordered_map<string,vector<char>> hash;
    unordered_set<string> bad;
    bool pyramidTransition(string bottom, vector<string>& allowed) {
        hash.clear();
        bad.clear();

        for(int i=0;i<(int)allowed.size();i++){
            string key=allowed[i].substr(0,2);
            char value=allowed[i][2];
            hash[key].push_back(value);
        }

        return dfs(bottom);
    }

private:
    bool dfs(const string& row) {
        if(row.size()==1) return true;
        if(bad.count(row)) return false;

        string nextRow(row.size()-1, ' ');
        if(buildNext(0, row, nextRow)) return true;

        bad.insert(row);
        return false;
    }

    bool buildNext(int pos, const string& row, string& nextRow) {
        if(pos==(int)nextRow.size()){
            return dfs(nextRow);
        }

        string key=row.substr(pos,2);
        auto it=hash.find(key);
        if(it==hash.end()) return false;

        const vector<char>& cand=it->second;
        for(char c: cand){
            nextRow[pos]=c;
            if(buildNext(pos+1, row, nextRow)) return true;
        }
        return false;
    }

};