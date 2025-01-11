#include<bits/stdc++.h>
using namespace std;

// we can use a map (for sorting) and insert it in nuts and bolts
class Solution {
  public:
    void matchPairs(int n, char nuts[], char bolts[]) {
        if(n==1)return;
        map<char,int>mp;
        for(int i=0;i<n;i++){
            mp[nuts[i]]++;
        }
        
        int i=0;
        for(auto it=mp.begin();it!=mp.end();it++){
            nuts[i]=it->first;
            bolts[i]=it->first;
            i++;
        }
    }
};