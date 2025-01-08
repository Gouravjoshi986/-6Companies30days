#include<bits/stdc++.h>
using namespace std;
// it can be easily done using brute force (2 for loops) and can be optimally done using sliding window 

class Solution {
public:
    long long maximumSubarraySum(vector<int>& nums, int k) {
        int i=0,j=0;
        long long ans=0,sum=0;
        unordered_map<int,int>freq;
        int n = nums.size();
        while(j<n){
            // add to window 
            freq[nums[j]]++;
            sum+=nums[j]; 
            // if window<k move forwards
            if(j-i+1<k)j++;
            else{
                // if 3 distinct characters 
                if(freq.size()==3){
                    ans = max(ans,sum);
                }
                // moving window forward
                sum-=nums[i];
                freq[nums[i]]--;

                if(freq[nums[i]]==0)freq.erase(nums[i]);
                i++;
                j++;
            }
        }
        return ans;
    }
};