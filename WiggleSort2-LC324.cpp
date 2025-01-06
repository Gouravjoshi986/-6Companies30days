#include<bits/stdc++.h>
using namespace std;
// We can observe that smaller elements are in even indices and larger elements are in odd indices  
// we can sort and divide into two partitions small and large 
// To deal with overlapping elements we will iterate in reverse  or we can revrese the array 
// By reversing smaller and larger, we ensure the following:
// 1.  Larger values in each group (especially overlapping ones) are placed in positions where they satisfy the wiggle-sort condition.
// 2.  This avoids the scenario where overlapping elements (e.g., 5 from both groups in the 4 5 5 6) end up as neighbors. 
class Solution {
public:
    void wiggleSort(vector<int>& nums) {
        sort(nums.begin(),nums.end());
        int n=nums.size();
        vector<int> smaller(nums.begin(),nums.begin()+(n+1)/2);
        vector<int> larger(nums.begin()+(n+1)/2,nums.end());
        int i=smaller.size()-1;
        int j=larger.size()-1;
        for(int k=0;k<n;k++){
            if(k%2==0){
                nums[k]=smaller[i--];
            }
            else{
                nums[k]=larger[j--];
            }
        }
    }
};

// we can do count sort and reduce the time complexity // using frequency count and iterating in reverse 
// TC & SC - O(N)
class Solution {
public:
    void wiggleSort(vector<int>& nums) {
        vector<int>count(5001,0);
        for (int n : nums) {
            count[n]++;
        }
        int odd = 1;
        int even = 0;
        int n = nums.size();

        for(int num = 5000;num>=0;num--){
            while(count[num]>0 && (odd<n || even<n)){
                count[num]--;
                if(odd<n){
                    nums[odd]=num;
                    odd+=2;
                }else{
                    nums[even]=num;
                    even+=2;
                }
            }
        }
    }
};

  
//  We can reduce the time complexity three way partitioning. --> dutch national flag algo . 
//  ie.  sort 0 1 2

// space complexity can be reduced using virtual indexing  --to store it without need of temp 
//  A(i) = nums[(1+2*i)%(n|1)]  .. 1+2*1 generates odd indices . %(n|1) wraps it in index 
// n|1 - remains odd when n is odd . becomes next odd if n is even 

// The function nth_element(nums.begin(), nums.begin() + n / 2, nums.end()) in C++ is part of the Standard Template Library (STL) and is used to partially sort an array or vector so that the element at the specified position is placed where it would be if the array were fully sorted.  
// it rearranges array such that all elements before nth element are smaller or equal to it and all elements after nth are greater or equal to it  

class Solution {
public:
    void wiggleSort(vector<int>& nums) {
        int n = nums.size();
        nth_element(nums.begin() , nums.begin()+n/2 , nums.end());
        int mid = *(nums.begin() + n/2);
        
        #define arr(i) nums[(1+2*(i)) % (n|1)]
        
        int i=0; 
        int j=0;
        int k=n-1;
        
        while( j <= k){
            
            if(arr(j) > mid){
                swap(arr(i++),arr(j++));
            }
            else if(arr(j) < mid){
                swap(arr(j) , arr(k--));
            }
            else{
                j++;
            }
        }
    }
};