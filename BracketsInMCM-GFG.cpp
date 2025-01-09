#include<bits/stdc++.h>
using namespace std;

// this is doable if you know about the LR dp(interval dp/mcm pattern) 
// We iterate between L......R  . and use a middle pointer k to divide the LR interval into 2 smaller intervals. These smaller intervals give answer and these answers are used to find the answer of bigger intervals .

// In classical MCM problem we find the cost of multiplying these matrices. Here we can keep track of the String along with the cost and update it when we get the correct partition point.(k)
// TC - O(n^2 * n) = O(n^3)
// SC - O(n) + O(n^2)
class Solution {
  private:
    pair<int,string> solve(vector<int>&arr,int i,int j,
    vector<vector<pair<int,string>>>&dp){
        if(i==j)return {0,string(1,static_cast<char>('A'+i-1))};
        if(dp[i][j].first!=-1)return dp[i][j];
        string temp="";
        int minCost = 1e9;
        for(int k=i;k<j;k++){
            pair<int,string> p1 = solve(arr,i,k,dp);
            pair<int,string> p2 = solve(arr,k+1,j,dp);
            int cost = p1.first + p2.first +(arr[i-1]*arr[k]*arr[j]);
            if(cost<minCost){
                minCost = cost;
                temp = "(" + p1.second + p2.second + ")";
            }
        }
        return dp[i][j] = {minCost,temp};
    }
  public:
    string matrixChainOrder(vector<int> &arr) {
        int n = arr.size();
        int i=1,j=n-1;  // as arr[i] and arr[i+1]
        vector<vector<pair<int,string>>>dp(n+1,
        vector<pair<int,string>>(n+1,{-1,""}));
        auto ans = solve(arr,i,j,dp); 
        return ans.second;
    }
};