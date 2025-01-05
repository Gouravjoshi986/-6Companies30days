#include<bits/stdc++.h>
using namespace std;
// Here we have to count based on the no of odd numbers in subarray .
// the no doesnt matter so we will treat odd = 1 and even = 0 . 
// so finding k odd number means subarray having sum = k
// TC - O(N)  , SC- O(N) 
class Solution {
public:
    int numberOfSubarrays(vector<int>& nums, int k) {
        // using unordered_map for prefix sum 
        unordered_map<int,int>prefixSum;
        int ans = 0;
        int currSum = 0;
        prefixSum[0] = 1;  // marking no element array
        for(int i=0;i<nums.size();i++){
            currSum+=(nums[i]%2);  // 0 for even, 1 for odd
            if(prefixSum.find(currSum-k)!=prefixSum.end()){
                ans += prefixSum[currSum-k];
            }
            prefixSum[currSum]++;
        }
        return ans; 
    }
};

// As all the numbers are positive we can also use a sliding window approach to tackle this problem .  

// we can do this by converting it into :
// no of subarrays with at most k odd - no of subarrays with at most k-1 odd 
// this would give exactly k odds 

// a simple sliding window where we increase the window size add the window size on every iteration to count no of subarrays . 
// and maintain the size after reaching k 
// TC - O(n)  SC- O(1) 

class Solution {
public:
    int numberOfSubarraysAtMost(vector<int>& nums, int k){
        int i=0,j=0;
        int cnt = 0;
        int ans = 0;
        int n = nums.size();
        while(j<n){
            if(nums[j]&1)cnt++;
            while(cnt>k && i<=j){
                if(nums[i]&1)cnt--;
                i++;
            }
            ans+=(j-i+1);
            j++;
        }
        return ans;
    }
    int numberOfSubarrays(vector<int>& nums, int k) {
        return numberOfSubarraysAtMost(nums,k) - numberOfSubarraysAtMost(nums,k-1);
    }
};


//  We can also do this in a single sliding window. 
// we will keep track of no of continuous even no in a valid window to find no of subarrays
// i and j for window , cnt for current odd calculation , even for cont even count in a valid window 
// we will update when cnt==k 
class Solution {
public:
    int numberOfSubarrays(vector<int>& nums, int k) {
        int i=0,j=0;
        int cnt = 0;
        int even = 0;
        int ans = 0;
        int n = nums.size();
        while(j<n){
            if(nums[j]&1)cnt++;
            while(cnt>k && i<=j){
                if(nums[i]&1)cnt--;
                i++;
                even=0;
            }
            while(!(nums[i]&1) && i<j){
                even++;
                i++;
            }
            if(cnt==k) ans+=even+1;
            j++; 
        }
        return ans;
    }
};