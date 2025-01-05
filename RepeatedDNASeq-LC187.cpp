#include<bits/stdc++.h>
using namespace std;

// a simple question where we can keep track of all the length 10 substrings in a frequency map and find strings where freq>1 
// Time complexity - O(n) (assuming O(1) for map)   Sc- O(n)

class Solution {
public:
    vector<string> findRepeatedDnaSequences(string s) {
        vector<string> v;
        unordered_map<string,int> mpp;
        for(int i=0;i+10 <= s.length();i++){
            mpp[s.substr(i,10)]++;
        }

        for(auto& i:mpp){
            if(i.second > 1){
                v.push_back(i.first);
            }
        }

        return v;
        
    }
};