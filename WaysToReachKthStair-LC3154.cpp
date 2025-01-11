#include<bits/stdc++.h>
using namespace std;

// we can go for a recursive appraoch to calculate total no of ways 
// states - back jump / jump /  back step available  : index cant be used as infinite stairs 
// transition - if stair>0 and back step is allowed
//              else forward 
// answer = OR of both transition 
// we know k max = 10^9  . we can jump by 2^jump < 10^9    so jump , back jump = 32 max


#define ll long long

ll dp[50][50][2];

ll find(int pos, int stat, int jump, int back, vector<ll> &exp, int k)
{
    if(pos > k+1) // no possible way to attain k once step number exceeds k + 1
        return 0;
    
    if(dp[jump][back][stat] != -1)
        return dp[jump][back][stat]; 
    
    ll ans = 0;
    
    if(pos == k) // dont end the recursion here as we may still reach k even after this
        ++ans; 

    if(stat == 1)
    {
        ans += find(pos-1, 0, jump, back+1, exp, k); // backstep
        ans += find(pos+exp[jump], 1, jump+1, back, exp, k); // forward jump
    }

    if(stat == 0)
        ans += find(pos+exp[jump], 1, jump+1, back, exp, k); // forward jump
    
    return dp[jump][back][stat] = ans;
}


class Solution {
public:
    int waysToReachStair(int k) {
            
        memset(dp, -1, sizeof(dp));
        vector<ll> exp(33,0);
        
        for(int i=0; i<33; ++i) // creating a pre-computed array containing powers of 2 to speed up the calculation.
            exp[i] = pow(2,i);

        ll ans = find(1, 1, 0, 0, exp, k);   
        return ans;
    }
};

// we can use mathematics to find out the no of ways: 
// if k is a power of 2 . then we need 2^n = k   and 1 back step to reach k. so ans = n+1
// generally if we reach u = 2^n and take backSteps r = u-k, then total ways = (n+1)C(r)
// Time complexity - O(n)  SC - O(1)
class Solution {
public:
    int findN(long long k){
        int cnt = 0;
        while(k){
            cnt++;
            k=k>>1;
        }
        return cnt;
    }

    unsigned long long binomialCoefficient(int n,int r){
        if(r>n)return 0;

        if(r==0 || r==n)return 1;
        r = min(r,n-r);
        unsigned long long result = 1;
        for(int i=1;i<=r;i++){
            result = result * (n-r+i)/i;
        }

        return result;
    }
    int waysToReachStair(int k) {
        if(k==0)return 2;
        if(k==1)return 4;
        if(k==2)return 4;

        int bit = __builtin_popcount(k);
        int n = findN(k); // 2^n >= k  

        int u = 1LL<<n;  // 2^n - k = r (after n forward jumps)
        n = n + 1;
        int r = u-k;

        int ans = binomialCoefficient(n,r);
        return ans + (bit==1?1:0);  // if k is a power of 2 ways = n+1 
    }
};

