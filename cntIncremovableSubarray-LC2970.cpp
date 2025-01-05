#include<bits/stdc++.h>
using namespace std;
// we will use three loops to check all the subarrays and if we found one where it is strictly increasing we increase the counter by one. 
// for i and j to simulate a subarray .  for k to check if num k > num k-1 .
// note - make sure to check the boundary point num i-1 < num j+1 
// TC - O(n^3)  SC - O(1)
class Solution {
public:
    int incremovableSubarrayCount(vector<int>& nums) {
        int n = nums.size();
        int cnt = 0;

        for(int i=0;i<n;i++){
            for(int j=i;j<n;j++){
                bool isValid = true;   // flag 
                int prev = 0; // to keep track of last valid element

                for(int k=0; k<i;k++){
                    if(k>0 && nums[k]<=nums[k-1]){
                        isValid=false;
                        break;
                    }
                    prev = nums[k];
                }
                // checking nums[i-1] and nums[j+1] (boundary points)
                if(isValid && i>0 && j<n-1 && nums[j+1]<=prev){
                    isValid = false; 
                } 
                if(isValid){
                    for(int k=j+1;k<n;k++){
                        if(k>j+1 && nums[k]<=nums[k-1]){
                            isValid=false;
                            break;
                        }
                    }
                }

                if(isValid)cnt++;
            }
        }
        return cnt;
    }
};

// we can optimize this using an observation // instead of thinking about deleting an subarray we can think about making an incremovable array. 
// we have to delete a subarray so we will divide the nums in left and right sorted parts. 
// we take prefix from left   and suffix from right .  // this will be equal to deleting elements from middle and rest becomes incremovable 
// TC - O(N) , SC-O(N)
class Solution{
public:
    int incremovableSubarrayCount(vector<int>& nums){
        int n = nums.size();
        if(n==1)return 1;
        vector<int>left,right;

        for(int i=0;i<n;i++){
            if(left.empty() || left.back()<nums[i])left.push_back(nums[i]);
            else break;
        }

        for(int i=n-1;i>=0;i--){
            if(right.empty() || right.back()>nums[i])right.push_back(nums[i]);
            else break;
        }

        if(left.size()+right.size()>n)return 1LL*n*(n+1)/2; // already sorted array 
        reverse(right.begin(),right.end());
        int ans = left.size()+right.size(); // you can always take seperate elements from left and right only.  // for eg 1 2 5 .. we can take prefix as 1, 1 2, 1 2 5 = 3(equal to size of array)
        int i=0,j=0;
        // taking prefix and suffix to make combination arrays 
        while(i<left.size() && j<right.size()){
            if(left[i]<right[j]){
                ans+=right.size()-j;
                i++;
            }else j++;
        }
        return ans+1;  // this +1 is for empty array  
    }
};