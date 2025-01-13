#include<bits/stdc++.h>
using namespace std;
// TC - O(n + nlogn + k klogk + k) = O(nlogn+klogk) 
// SC - O(n + 2k)  
class Solution {
public:
    vector<int> maxSubsequence(vector<int>& nums, int k) {
        int n = nums.size();
        vector<pair<int,int>>arr;
        for(int i=0;i<n;i++){
            arr.push_back({nums[i],i});
        }
        sort(arr.begin(),arr.end());
        vector<pair<int,int>>res;
        for(int i=n-1;i>=0 && k>0;i--,k--){
            res.push_back({arr[i].second,arr[i].first});
        }
        sort(res.begin(),res.end());
        vector<int>ans;
        for(int i=0;i<res.size();i++){
            ans.push_back(res[i].second);
        }
        return ans;
    }
};