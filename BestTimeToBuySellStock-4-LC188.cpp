#include<bits/stdc++.h>
using namespace std;
// we can go with a recursive approach as we can two options for any stock 
// we either buy it if we havent bought any before ->state to track buy 
// index of stock -state i 
// no of transactions left - decreases by 1 on sell - state cnt 
// TC - O(2^n) + O(n)
class Solution {
private:
    int rec(int index,int buy,int cnt,vector<int>&prices){
        if(index==prices.size() || cnt==0)return 0;   // nothing to buy or sell 

        int profit = 0;
        // not we can either buy or sell 
        if(buy){
            // buy or not buy 
            int pick = -prices[index] + rec(index+1,0,cnt,prices); // money out 
            int notPick = 0 + rec(index+1,1,cnt,prices);
            profit = max(pick,notPick);
        }
        else{
            // sell or not sell 
            int pick = prices[index] + rec(index+1,1,cnt-1,prices); // money in
            int notPick = 0 + rec(index+1,0,cnt,prices);
            profit = max(pick,notPick);
        }
        return profit;
    }
public:
    int maxProfit(int k, vector<int>& prices) {
        return rec(0,1,k,prices);  // index buy cnt prices
    }
};

// here we are tracking three changing states so we can memoize using a 3D dp table 
// TC - O(N*2*k)*(1+4) = O(2*N*k)   
// SC - O(N*2*k) + O(n)
class Solution {
private:
    int rec(int index,int buy,int cnt,vector<int>&prices,vector<vector<vector<int>>>&dp){
        if(index==prices.size() || cnt==0)return 0;   // nothing to buy or sell 
        if(dp[index][buy][cnt]!=-1)return dp[index][buy][cnt];
        int profit = 0;
        // not we can either buy or sell 
        if(buy){
            // buy or not buy 
            int pick = -prices[index] + rec(index+1,0,cnt,prices,dp); // money out 
            int notPick = 0 + rec(index+1,1,cnt,prices,dp);
            profit = max(pick,notPick);
        }
        else{
            // sell or not sell 
            int pick = prices[index] + rec(index+1,1,cnt-1,prices,dp); // money in
            int notPick = 0 + rec(index+1,0,cnt,prices,dp);
            profit = max(pick,notPick);
        }
        return profit;
    }
public:
    int maxProfit(int k, vector<int>& prices) {
        vector<vector<vector<int>>>dp(prices.size(),vector<vector<int>>(2,vector<int>(k+1,-1)));
        return rec(0,1,k,prices,dp);  // index buy cnt prices
    }
}; 

// we can do this in a tabulated way to save recursive stack space 
// here we need information about index+1 to calculate index. and for i==n result = 0 .
// so we iterate in reverse 
// TC - O(N*2*k)*(1+4) = O(2*N*k)   
// SC - O(N*2*k)
class Solution {
public:
    int maxProfit(int cnt, vector<int>& prices) {
        int n = prices.size();
        vector<vector<vector<int>>>dp(n+1,vector<vector<int>>(2,vector<int>(cnt+1,0)));
        // for no element 
        for(int j=0;j<2;j++){
            for(int k=0;k<cnt+1;k++){
                dp[n][j][k]=0;  
            }
        }
        // for no transaction 
        for(int i=0;i<=n;i++){
            for(int j=0;j<2;j++){
                dp[i][j][0]=0; 
            }
        }
        for(int i=n-1;i>=0;i--){
            for(int j=0;j<2;j++){
                for(int k=1;k<=cnt;k++){
                    int profit = 0;
                    if(j){
                        int pick = -prices[i]+dp[i+1][false][k];
                        int notPick = 0+dp[i+1][true][k];
                        profit = max(pick,notPick);
                    }
                    else{
                        int pick = prices[i]+dp[i+1][true][k-1];
                        int notPick = 0+dp[i+1][false][k];
                        profit = max(pick,notPick);
                    }
                    dp[i][j][k] = profit;
                }
            }
        }
        return dp[0][true][cnt];
    }
}; 

// we can optimize it further by using only two 2D rows . curr and prev as we only need information of index and index + 1
// TC - O(N*2*k)*(1+4) = O(2*N*k)   
// SC - O(2*k) + O(2*k)
class Solution {
public:
    int maxProfit(int cnt, vector<int>& prices) {
        int n = prices.size();
        vector<vector<int>>curr(2,vector<int>(cnt+1,0));
        vector<vector<int>>prev(2,vector<int>(cnt+1,0));
        
        for(int i=n-1;i>=0;i--){
            for(int j=0;j<2;j++){
                for(int k=1;k<=cnt;k++){
                    int profit = 0;
                    if(j){
                        int pick = -prices[i]+prev[false][k];
                        int notPick = 0+prev[true][k];
                        profit = max(pick,notPick);
                    }
                    else{
                        int pick = prices[i]+prev[true][k-1];
                        int notPick = 0+prev[false][k];
                        profit = max(pick,notPick);
                    }
                    curr[j][k] = profit;
                }
            }
            prev = curr;
        }
        return prev[true][cnt];
    }
}; 

// we can even do this by assigning transaction numbers. 
// 0 1 2 3 --> transaction = 0 - buy , 1 - sell , 2 - buy , 3 - sell so even-buy , odd-sell
class Solution {
public:
    int solve(int index,int tranNo,int k,int n,vector<int>&prices){
        if(index==n || tranNo==k*2){
            return 0;  
        }
        int profit = 0;
        if(tranNo%2==0){
            int pick = -prices[index]+solve(index+1,tranNo+1,k,n,prices);
            int notPick = solve(index+1,tranNo,k,n,prices);
            profit = max(pick,notPick);
        }
        else{
            int pick = prices[index]+solve(index+1,tranNo+1,k,n,prices);
            int notPick = solve(index+1,tranNo,k,n,prices);
            profit = max(pick,notPick);
        }
        return profit;
    }
    int maxProfit(int k, vector<int>& prices) {
        int n = prices.size();
        return solve(0,0,k,n,prices);
    }
};

// we can similarly memoize it further / the edge is that here we have reduced the number of states that we need to track (although not really we use 2D instead of 3D but we still have n*2*k elements). 


