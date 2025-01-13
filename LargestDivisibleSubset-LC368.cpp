#include<bits/stdc++.h>
using namespace std;

// arr[i] % arr[j] = 0 or arr[j] % arr[i] = 0 - so we can sort it . and look for arr[j]/arr[i]=0 to look for all the subsets - so we can think of an LIS like pattern . 
// TC -  O(nlogn + n^2 + n) = O(n^2)  , SC - O(n)w
class Solution {
public:
    vector<int> largestDivisibleSubset(vector<int>& nums) {
        int n = nums.size();
        if(n==0)return {};
        sort(nums.begin(),nums.end());
        vector<int>dp(n,1); // single subset
        vector<int>prev(n,-1);

        int maxi = 0; // index of longest subarray
        for(int i=1;i<n;i++){
            for(int j=0;j<i;j++){
                if(nums[i]%nums[j]==0 && dp[i]<dp[j]+1){
                    dp[i]=dp[j]+1;
                    prev[i]=j;
                    if(dp[i]>dp[maxi]){
                        maxi = i;
                    }
                }
            }
        }
        vector<int>result;
        while(maxi>=0){
            result.push_back(nums[maxi]);
            maxi = prev[maxi];
        }
        return result;
    }
};