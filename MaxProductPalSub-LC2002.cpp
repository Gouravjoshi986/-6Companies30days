// THIS IS HARDDD

#include<bits/stdc++.h>
using namespace std;
// Basic Solution is to implement a recursion (dfs like) and explore all paths
// cases - 1. include in s1 and not s2    2. include in s2 and not s1    3.dont include 
// we will take the maximum as answer 
// TC - O(3^N * N)   SC-O(N)
class Solution {
public:
    int result = 0;

    bool isPalindrome(string &s){         // O(n) for palindromic checking 
        int i=0,j=s.length()-1;
        while(i<j){
            if(s[i]!=s[j])return false;
            i++;
            j--;
        }
        return true;
    }

    void dfs(string &s,int i,string &s1,string &s2){    // O(3^N) for all transitions
        if(i>=s.length()){
            if(isPalindrome(s1)&& isPalindrome(s2)){
                result = max(result,(int)s1.length()*(int)s2.length());
            }
            return;
        }
        // include in s1
        s1.push_back(s[i]);
        dfs(s,i+1,s1,s2);
        s1.pop_back();

        // include in s2
        s2.push_back(s[i]);
        dfs(s,i+1,s1,s2);
        s2.pop_back();

        // dont include 
        dfs(s,i+1,s1,s2);
    }
    
    int maxProduct(string s) {
        string s1="",s2="";
        dfs(s,0,s1,s2);
        return result;
    }
};

// For Optimization we can use a dp approach with bitmask to track all the indexes which are used in a subsequence . 
// possible palindromes - 2^n  (n=12 max. so 1...4096)-mask
// we check if a mask represent palindrome and store length in dp
// length - no of set bits 
// disjoint subsequence - mask of both do not intersect 
// ie m1 & m2 = 0 --> check and find largest 
// we can use more efficient enumeration for m2 to only go through "available" bits (mask ^ m1) . this will be done using m2 = mask^m1 (complement of m1 - disjoint part)
// and we can iterate over all possible m2 using   (m2-1)&(mask^m1) . here m2-1 will give the next smaller binary number and &(mask^m1) will keep the operation only on bits not in m1

// Palindrome size function :
//If mask & (1 << i) is 1, the character at index i is part of the subsequence.
// If it’s 0, the character is skipped.

class Solution {
public:
    int palSize(string s,int mask){
        int i=0,j=s.size(),res=0;
        while(i<=j){
            if((mask&(1<<i))==0)i++; // if bit at i is not set
            else if((mask&(1<<j))==0)j--; 
            else if(s[i]!=s[j])return 0; // not palindrome
            else{
                res+= 1+(i!=j); // if indices are not same,res+2
                i++;            
                j--;
            }
        }
        return res;
    }
    int maxProduct(string s) {
        int dp[4096]={};
        int res=0,mask=(1<<s.size())-1; //all bits set
        for(int m=1;m<=mask;m++){
            dp[m]=palSize(s,m);  // finding pal size for this mask
        } 
        for(int m1=mask;m1;m1--){ // till m1 is not zero 
            if(dp[m1]*(s.size()-dp[m1]) > res){
                // if its possible to generate bigger answer
                for(int m2 = mask^m1;m2;m2 = (m2-1)&(mask^m1)){
                    res = max(res,dp[m1]*dp[m2]);
                }
            }
        }
        return res;
    }
};

// if for generating m2 we use :
// for (int m2 = 1; m2 < (1 << s.size()); ++m2) if ((m1 & m2) == 0)  --O(4^n)
// for(int m2 = mask^m1;m2;m2 = (m2-1)&(mask^m1))  -- O(3^n)  
// TC - O(2^n * n for precomp.  + 3^n for mask) ==> O(3^n) 
// SC - O(2^n) for dp 

// we can reduce the time complexity even more 
// when we are finding m2 for a certain m1. we can use the longest palindromic substring on inverted m1 to find the maximum possible value of m2 . 
// TC - O(2^n * n^2)   SC - O(2^n (dp mask) + n^2 (dp  lps))
class Solution {
public:
    int palSize(string s,int mask){
        int i=0,j=s.size(),res=0;
        while(i<=j){
            if((mask&(1<<i))==0)i++; // if bit at i is not set
            else if((mask&(1<<j))==0)j--; 
            else if(s[i]!=s[j])return 0; // not palindrome
            else{
                res+= 1+(i!=j); // if indices are not same,res+2
                i++;            
                j--;
            }
        }
        return res;
    }

    int maxPalindrome(string &s,int mask){
        string ss; // creating subsequence where bits are set in mask
        for(int i=s.size();i>=0;i--){
            if(mask&(1<<i))ss.push_back(s[i]); // ss contains the subset represented by the mask 
        }

        int n = ss.length(),dp[12][12]={0}; // max length is 12 
        // single elements are palindrome 
        for(int i=0;i<n;i++)dp[i][i]=1;

        for(int len = 2;len<=n;len++){
            for(int i=0;i<=n-len;i++){
                int j = i+len-1;
                if(ss[i]==ss[j])dp[i][j] = dp[i+1][j-1]+2;
                else dp[i][j] = max(dp[i][j-1],dp[i+1][j]);
            }
        }
        return dp[0][n-1];
    }
    int maxProduct(string s) {
        int dp[4096]={};
        int res=0,mask=(1<<s.size())-1; //all bits set
        for(int m=1;m<=mask;m++){
            dp[m]=palSize(s,m);  // finding pal size for this mask
        } 
        
        // finding largest subsequence in dp
        int maxDp = *max_element(begin(dp),end(dp));
        for(int m1=mask-1;m1;m1--){ // till m1 is not zero 
            if(dp[m1]*min((int)s.size()-dp[m1],maxDp) > res){
                // if its possible to generate bigger answer
                res = max(res,dp[m1]*maxPalindrome(s,mask^m1));
            }
        }
        return res;
    }
};