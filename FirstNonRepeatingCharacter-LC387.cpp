#include<bits/stdc++.h>
using namespace std;
// Simple Question . Brute Force - just two loops - O(n^2) O(1) 
// Optimal - use a Hash Map or Frequency Array . In one passes store freq. In other if freq==1 -> return.   O(2*n) , O(26)    
class Solution{
public:
    int firstUniqChar(string s) {
        int m[26]={0};
        //adding values in map to mark no of occurences 
        for(int i=0;i<s.length();i++){
            m[s[i]-'a']++;
        }
        
        for(int i=0;i<s.length();i++){
            if(m[s[i]-'a']==1){
                return i;
            }
        }
        return -1;
    }
};