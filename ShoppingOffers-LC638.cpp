#include<bits/stdc++.h>
using namespace std;
// here price is constant , special is constant , the needs array will be updated on every purchase so we can pass it in recursion 
// with this we will find all path and choose the min cost out of all of them with a backtracking solution
// TC - n = needs array size  ,m = special array size - -O(m*max(needs)^n * n)
// max(needs)^n calls for every offer and res calculation for every call
// SC - O(max(needs)^n * n) recursion stack and clone 
class Solution {
public:
    int rec(vector<int>& price, vector<vector<int>>& special, vector<int>& needs){
        int res = 0; // to find the original cost 
        for(int i=0;i<needs.size();i++){
            res+=needs[i]*price[i];
        }
        // for every new offer we have a new path 
        for(auto &s:special){
            vector<int> temp = needs; // a copy of needs to iterate again
            int j=0;
            for(;j<needs.size();j++){
                int left = temp[j]-s[j];
                if(left<0)break; //cant take this offer 
                temp[j] = left;
            }
            if(j==needs.size()){
                res = min(res,s[j]+rec(price,special,temp));
            }
        }
        return res;
    }
    int shoppingOffers(vector<int>& price, vector<vector<int>>& special, vector<int>& needs) {
        return rec(price,special,needs);
    }
};

// we can memoize this to move towards a dp solution 
// we use an unordered map to store the needs vector and its value for answer. 
// to store a vector we can either use a custom hash to store it or encode it into a string

class Solution {
public:
    int shoppingOffers(vector<int>& price, vector<vector<int>>& special, vector<int>& needs) {
        unordered_map<vector<int>, int, VectorHash> memo;
        return shopping(price, special, needs, memo);
    }

private:
    struct VectorHash {
        size_t operator()(const vector<int>& v) const {
            size_t hash = 0;
            for (int num : v) {
                hash = hash * 31 + num;
            }
            return hash;
        }
    };

    int shopping(vector<int>& price, vector<vector<int>>& special, vector<int>& needs, unordered_map<vector<int>, int, VectorHash>& memo) {
        if (memo.find(needs) != memo.end()) {
            return memo[needs];
        }

        int res = dot(needs, price); // Calculate the cost without any special offers

        for (auto& s : special) {
            vector<int> clone = needs;
            int j = 0;
            for (; j < needs.size(); ++j) {
                int diff = clone[j] - s[j];
                if (diff < 0) break; // Cannot use this offer if it exceeds the needs
                clone[j] = diff;
            }
            if (j == needs.size()) {
                res = min(res, s[j] + shopping(price, special, clone, memo));
            }
        }

        memo[needs] = res; // Store the result in memoization map
        return res;
    }

    int dot(vector<int>& a, vector<int>& b) {
        int sum = 0;
        for (int i = 0; i < a.size(); ++i) {
            sum += a[i] * b[i];
        }
        return sum;
    }
};

// we can optimize it further - using bitmask to store 
class Solution {
private:
    int n;
    unordered_map<int, unordered_map<int, int>> dp;
public:
    int solve(int i, int mask, vector<int> &price, vector<vector<int>>& special){
        if(mask == 0) return 0; //nothing to purchase 
        if(dp.find(mask) != dp.end() && dp[mask].find(i) != dp[mask].end()) 
            return dp[mask][i];

        int ans = 1e9;
        // all offers used so find price directly 
        if(i >= special.size()){
            ans = 0;
            for(int j = 0; j < n; j++){
                int curr = (mask >> (4 * j)) & ((1 << 4) - 1);
                ans += curr * price[j];
            }
        }
        else{
            int temp = mask;                                 
            //covering special array            
            int cost = special[i].back();     
            bool flag = true;       
            //taking ith offer
            for(int j = 0; j < n; j++){   
                int curr = (mask >> (4 * j)) & ((1 << 4) - 1);
                if(special[i][j] > curr) {
                    flag = false;
                    break;
                }               
                else{              
                    mask = mask ^ (curr << (4 * j));
                    curr -= special[i][j];                  
                    mask = mask | (curr << (4 * j));
                }
            }
            if(flag) ans = cost + solve(i, mask, price, special);
            mask = temp;
            ans = min(ans, solve(i + 1, mask, price, special));
        }
        return dp[mask][i] = ans;
    }

    int shoppingOffers(vector<int>& price, vector<vector<int>>& special, vector<int>& needs) {
        //4 bits per item so total 4 * n bits required
        n = price.size();
        int mask{};
        // dp = vector<int> (1 << (4*n), -1);
        // eg 3,2,1 needs  = 0001 0010 0011
        for(int i = 0; i < n; i++){
            int a = needs[i] << (4*i);
            mask = mask | a;
        }
        // solving for each mask and each offer 
        // dp[mask][i] - cost for mask(needs) using ith offer 
        return solve(0, mask, price, special);
    }
};