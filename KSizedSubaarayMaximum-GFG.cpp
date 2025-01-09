#include<bits/stdc++.h>
using namespace std;

// we can do this via brute force //O(n^3) (3 loop - 2 for subarray one for maximum)
// or we can use a normal sliding window and an inner loop to find max in window 
// O(n^2)

// or we can use a priority queue for optimal answer 
// TC : O(nlogn), SC : O(1) (not including ans vector)
class Solution {
  public:
    // Function to find maximum of each subarray of size k.
    vector<int> maxOfSubarrays(vector<int>& arr, int k) {
        int n=arr.size();
        vector<int>result;
        priority_queue<pair<int,int>>pq;
        
        for(int i=0;i<k;i++)pq.push({arr[i],i});
        result.push_back(pq.top().first);
        
        for(int i=k;i<n;i++){
            pq.push({arr[i],i});
            // removing elements out of window if they come on top
            // of pq to keep the answer correct 
            while(pq.top().second <=i-k)pq.pop();
            result.push_back(pq.top().first);
        }
        return result;
    }
};