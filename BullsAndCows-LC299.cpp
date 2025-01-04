#include<bits/stdc++.h>
using namespace std;
 
// A fairly simple problem which can be easily solved by keeping track of the frequency of chars in secret. 
// using bulls var to count chars which are present in accurate positions 
// keeping track of freq of secret char using map and inserting when they are not present at right places 
// also keeping a temp string to iterate on map for char which are at wrong place or not present in secret  ( this could have been easily done in a single loop if not for the duplicates )

class Solution {
public:
    string getHint(string secret, string guess) {
        unordered_map<char,int>mp;      // O(1) or O(n) worst case 
        string temp="";                         
        int bulls=0;
        for(int i=0;i<secret.size();i++){      // o(n)  * O(logn)
            if(secret[i]==guess[i]){
                bulls++;
            }
            else{
                temp+=guess[i];
                mp[secret[i]]++;            // o(logn) 
            }
        }
        int cows = 0;
        for(int i=0;i<temp.size();i++){         // (n*logn)
            if(mp.find(temp[i])!=mp.end()){
                cows++;
                mp[temp[i]]--;
                if(mp[temp[i]]==0)mp.erase(temp[i]);
            }
        }
        string ans ="";
        ans+=to_string(bulls);
        ans+='A';
        ans+=to_string(cows);
        ans+='B';
        return ans; 
    }
};

// TC - O(nlogn)  SC- O(n-bulls) 

