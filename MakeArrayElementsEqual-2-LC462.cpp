#include<bits/stdc++.h>
using namespace std;

//  1 2 9 10 median -  2 or 9  lets make them 2    1+1  2+0 9+(-7) 10+(-8) ->moves = 1+8+7 = 16
//   lets make 9  1+8 2+7 9+0 10-1 - so 8+7+1 - 16 
// very simple idea of converting each element into the median of array and counting the steps  

// Some mathematical observations : Mathematically, the median of a list L minimizes the sum of the absolute differences from each element of L. The mean minimizes the sum of the squared differences from each element of L.

// Average is the point it minimize the sum of distances where if we consider all integers between the min and max of the elements no matter if they are in the array or not.
// Median considers only those actually exist in the array.

class Solution {
public:
    int minMoves2(vector<int>& nums) {
        sort(nums.begin(),nums.end());
        int n = nums.size();    // 1 2 3 4 - m - 4+1/2 - 2 = index+1 
        int medianIdx = (n+1)/2 - 1;   // 1 2 3 - median - 3+1/2 - 2 
        int median = nums[medianIdx];
        int ans = 0;
        for(auto it:nums){
            ans += abs(it-median);
        }
        return ans;
    }
}; 
