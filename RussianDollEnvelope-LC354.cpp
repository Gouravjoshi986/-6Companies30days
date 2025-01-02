#include<bits/stdc++.h>
using namespace std;
// this question is just like lis where we have to create a sequence of increasing numbers
// we can use dp[i] - biggest sequence ending at that index 
// transition - dp[i] - max(dp[i],dp[j]+1) where j=0 to i

// we will first sort array  
class Solution{
private: 
    int helper(int i,vector<vector<int>>&envelopes){
        if(i==envelopes.size())return 0;  // no item to pick 

        int ans = 1; // single element 
        for(int prev=0;prev<i;prev++){
            if((envelopes[prev][0]<envelopes[i][0] && envelopes[prev][1]<envelopes[i][1]) || (envelopes[prev][0]==envelopes[i][0] && envelopes[prev][1]<envelopes[i][1])){
                ans = max(ans,1+helper(prev,envelopes));
            }
        }
        return ans;
    }
public:
    int maxEnvelopes(vector<vector<int>>&envelopes){
        sort(envelopes.begin(),envelopes.end());
        int ans  = 1;
        for(int i=0;i<envelopes.size();i++){
            ans = max(ans,helper(i,envelopes));
        }
        return ans;
    }
};


//memoization        
// TC - O(no of states * (1 + no of transitions)) = O(n * (1+n-1)) = O(n^2)
// SC - O(n) (not counting envelopes array) 
class Solution{
private: 
    int helper(int i,vector<vector<int>>&envelopes,vector<int>&dp){
        if(i==envelopes.size())return 0;  // no item to pick 
        if(dp[i]!=-1)return dp[i];

        int ans = 1; // single element 
        for(int prev=0;prev<i;prev++){
            if((envelopes[prev][0]<envelopes[i][0] && envelopes[prev][1]<envelopes[i][1]) || (envelopes[prev][0]==envelopes[i][0] && envelopes[prev][1]<envelopes[i][1])){
                ans = max(ans,1+helper(prev,envelopes,dp));
            }
        }
        return dp[i] = ans;
    }
public:
    int maxEnvelopes(vector<vector<int>>&envelopes){
        sort(envelopes.begin(),envelopes.end());
        int ans  = 1;
        vector<int>dp(envelopes.size(),-1);
        for(int i=0;i<envelopes.size();i++){
            ans = max(ans,helper(i,envelopes,dp));
        }
        return ans;
    }
};

// tabulation 
// TC - O(no of states * (1 + no of transitions)) = O(n * (1+n-1)) = O(n^2)
// SC - O(n) (not counting envelopes array) 
class Solution{
public:
    int maxEnvelopes(vector<vector<int>>&envelopes){
        sort(envelopes.begin(),envelopes.end());
        vector<int>dp(envelopes.size(),1); // all single elements 
        for(int i=0;i<envelopes.size();i++){
            for(int prev=0;prev<i;prev++){
                if((envelopes[prev][0]<envelopes[i][0] && envelopes[prev][1]<envelopes[i][1]) || (envelopes[prev][0]==envelopes[i][0] && envelopes[prev][1]<envelopes[i][1])){
                    dp[i] = max(dp[i],1+dp[prev]);
                }
            }
        }
        return dp[envelopes.size()-1];
    }
};

// AS the array is sorted by ascending weight and height. we can work with ((envelopes[prev][0]<envelopes[i][0] && envelopes[prev][1]<envelopes[i][1]) || (envelopes[prev][0]==envelopes[i][0] && envelopes[prev][1]<envelopes[i][1])) 

// and also (envelopes[prev][0]<envelopes[i][0] && envelopes[prev][1]<envelopes[i][1]) as the case of equal envelopes are already taken care of. 

// Binary search solution 
// TC - O(nlogn)
// SC - O(n) 
class Solution {
private:
    class compare{
    public:
        bool operator()(vector<int>&a,vector<int>&b){
            if(a[0]!=b[0]){
                return a[0]<b[0];  // increasing in height 
            }
            else return a[1]>b[1]; // decreasing height as we will prefer bigger height for same width 
        }
    };
public:
    int maxEnvelopes(vector<vector<int>>& envelopes) {
        sort(envelopes.begin(),envelopes.end(),compare());
        vector<int>lis;
        lis.push_back(envelopes[0][1]);
        for(int i=1;i<envelopes.size();i++){
            if(lis.back()<envelopes[i][1]){
                lis.push_back(envelopes[i][1]);
            }
            else{
                auto index = lower_bound(lis.begin(),lis.end(),envelopes[i][1])-lis.begin();
                lis[index] = envelopes[i][1];
            }
        }
        return lis.size();
    }
};
