#include<bits/stdc++.h>
using namespace std;
// just take remainder with 26 to get last character and add to string ans 
// reduce num by dividing with 26 . reverse the ans before returning as we are constructing string from right side 
// TC - O(logN base 26) = O(logN)
class Solution {
public:
    string convertToTitle(int columnNumber) {
        string ans; 
        while(columnNumber){
            columnNumber--;  // shifting index as we are adding A
            ans = ans + (char)((columnNumber)%26 + 'A');
            columnNumber = columnNumber/26;
        }
        reverse(ans.begin(),ans.end());
        return ans;
    }
};