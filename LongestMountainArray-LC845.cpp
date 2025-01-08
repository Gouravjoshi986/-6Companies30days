#include<bits/stdc++.h>
using namespace std;

// On observing we can think of it as a combination of finding LI subarray and LD subarray . 
// the length of mountain array at any point would be LI[i]+LD[i]-1 . 
// TC - O(n) & SC - O(n) 
class Solution {
public:
    int longestMountain(vector<int>& arr) {
        int n = arr.size();
        vector<int>inc(n,1); // default length 
        vector<int>dec(n,1); 
        int ans = 0; 

        for(int i=1;i<n;i++){
            if(arr[i]>arr[i-1]){
                inc[i] = 1+inc[i-1];
            }
        }

        for(int i=n-2;i>=0;i--){
            if(arr[i]>arr[i+1]){
                dec[i] = 1+dec[i+1];
            }
        }

        for(int i=0;i<n;i++){
            if(inc[i]>1 && dec[i]>1){
                ans = max(ans,inc[i]+dec[i]-1);
            }
        }
        return ans;
    }
};

// We can do this in two pass also 
class Solution {
public:
    int longestMountain(vector<int>& arr) {
        int n = arr.size();
        vector<int>inc(n,1); // default length 
        vector<int>dec(n,1); 
        int ans = 0; 

        for(int i=n-2;i>=0;i--){
            if(arr[i]>arr[i+1]){
                dec[i] = 1+dec[i+1];
            }
        }

        for(int i=1;i<n;i++){
            if(arr[i]>arr[i-1]){
                inc[i] = 1+inc[i-1];
            }
            if(inc[i]>1 && dec[i]>1){
                ans = max(ans,inc[i]+dec[i]-1);
            }
        }

        return ans;
    }
};

// we can do this in one pass 
// we calculate the increase if elements are increasing and calculate the decrease if they are decreasing . the increase + decrease + 1(peak element) will be length of mountain 
// TC - O(n)  & SC - O(1) 
class Solution {
public:
    int longestMountain(vector<int>& arr) {
        int ans = 0; 
        int i=1;
        while(i<arr.size()){
            while(i<arr.size() && arr[i-1]==arr[i])i++; // if similar move forward 
            int inc = 0;
            while(i<arr.size() && arr[i-1]<arr[i]){
                inc++;
                i++;
            }
            int dec = 0;
            while(i<arr.size() && arr[i-1]>arr[i]){
                dec++;
                i++;
            }
            if(inc>0 && dec>0)ans = max(ans,inc+dec+1);
            // uphill + downhill + 1(peak)
        }
        return ans;
    }
};

// We can also write this in a kadanes algo manner (increase or decrease followed by a reset)
// Tc-O(n)  & Sc-O(1)
class Solution {
public:
    int longestMountain(vector<int>& arr) {
        int ans = 0,inc = 0,dec = 0;
        for(int i=1;i<arr.size();i++){
            if(dec>0 && arr[i]>arr[i-1] || arr[i]==arr[i-1]){
                inc=0;    // condition of valley or flat surface
                dec=0;  
            }

            if(arr[i]>arr[i-1])inc++;
            if(arr[i]<arr[i-1])dec++;
            if(inc>0 && dec>0){
                ans = max(ans,inc+dec+1);
            }
        }
        return ans;
    }
};