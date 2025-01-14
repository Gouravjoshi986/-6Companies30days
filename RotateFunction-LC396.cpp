#include<bits/stdc++.h>
using namespace std;

// we can simulate this using two for loops 
// tc - O(n^2)

class Solution {
public:
    int maxRotateFunction(vector<int>& nums) {
        int k=0;
        int ans=INT_MIN;
        while(k<nums.size()){
            int i=k;
            int sum=0;
            int count=0;
            while(count<nums.size()){
                sum+=count*nums[i];
                i=(i+1)%nums.size();
                count++;
            }
            ans=max(ans,sum);
            k++;
        }
        return ans;
    }
};

// we can optimize it by finding formula // by observation : f(1) = f(0) + sum - n*lastElement
// tc - O(n)

class Solution {
public:
    int maxRotateFunction(vector<int>& nums) {
        int n = nums.size();
        long long sum = 0,dp = 0;
        for(int i=0;i<n;i++){
            sum+=nums[i];
            dp += i*nums[i];
        }

        long long maxi = dp;
        for(int i=n-1;i>=0;i--){
            dp = dp + (sum - (long long)nums[i]*(n));
            maxi = max(maxi,dp);
        }
        return maxi;
    }
};