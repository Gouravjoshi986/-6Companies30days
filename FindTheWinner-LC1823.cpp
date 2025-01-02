#include<bits/stdc++.h>
using namespace std; 

class Solution {
public:
    int findTheWinner(int n, int k) {
        vector<int>lis;
        for(int i=1;i<=n;i++){
            lis.push_back(i);
        }
        int st = 0;
        while(lis.size()>1){
            int remove = (st+k-1)%lis.size();
            lis.erase(lis.begin()+remove);
            st = remove; // as index will shift forward after deleting 
        }
        return lis.front();
    }
};

//this is just a simple brute force approach which simulates the conditions 
// TC - O(n^2)   SC - O(n)

// using a queue for optimization TC - O(n*k)  SC - O(n)
// taking a queue and removing first k-1 players and adding back to list 
class Solution {
public:
    int findTheWinner(int n, int k) {
        queue<int>lis;
        for(int i=1;i<=n;i++)lis.push(i);

        while(lis.size()>1){
            for(int i=0;i<k-1;i++){
                lis.push(lis.front());
                lis.pop();
            }
            lis.pop();
        }
        return lis.front();
    }
};

// Using recursive approach to reduce time complexity 
// f(args) - gives the index of the last remaning player  
// base case - when only one player remains - return 0 as index 
// we also need to change the index to simulate changing starting points 
// TC and SC - O(n)
class Solution {
private:
    int helper(int n,int k){
        if(n==1)return 0; 
        // after looping we add k to change the index of every person
        return (helper(n-1,k)+k)%n;
    }
public:
    int findTheWinner(int n, int k) {
        return helper(n,k)+1;
    }
};

// Iterative approach to reduce the function stack required 
// TC - O(n) 
// SC - O(1)

class Solution {
public:
    int findTheWinner(int n, int k) {
        // using iterative approach for recursive solution 
        // initially for n=1 ans = 0;
        int ans = 0;
        for(int i=2;i<=n;i++){
            ans = (ans+k)%i;
        }
        return ans+1;
    }
};


