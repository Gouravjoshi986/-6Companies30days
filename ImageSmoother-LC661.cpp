#include<bits/stdc++.h>
using namespace std; 
// A very Simple Simulation solution where we will iterate over the matrix and compute the average using sum and count variable ( this will be time as there can be at max 8 neighbours, we will also check if they are valid before including them ) 
// TC - O(m*n*(9)) = O(m*n)   // SC - O(n*m)  
class Solution {
public:
    vector<vector<int>> imageSmoother(vector<vector<int>>& img) {
        int m = img.size();
        int n = img[0].size();
        vector<vector<int>>smooth_img(m,vector<int>(n));
        for(int i=0;i<m;i++){
            for(int j=0;j<n;j++){
                int sum=0;
                int count=0;
                // iterating over neighbours and using them if they are valid 
                for(int x=i-1;x<=i+1;x++){
                    for(int y=j-1;y<=j+1;y++){
                        if(x>=0 && x<m && y>=0 && y<n){
                            sum+=img[x][y];
                            count++;
                        }
                    }
                }
                smooth_img[i][j] = sum/count;
            }
        }
        return smooth_img;
    }
};

// We can optimize the space by looking at the calculation of average . 
// BY observation we can tell that we need two rows which were modified and the curr grid for calculation . we can store these two rows and curr and prev row. 

class Solution {
public:
    vector<vector<int>> imageSmoother(vector<vector<int>>& img) {
        int m = img.size();
        int n = img[0].size();
        // curr is having first row elements now 
        vector<int>prev(n);
        for(int i=0;i<m;i++){
            vector<int>curr = img[i];
            // assigned curr row 
            for(int j=0;j<n;j++){
                int sum=0;
                int count=0;
                // iterating over neighbours and using them if they are valid 
                for(int x=i-1;x<=i+1;x++){
                    for(int y=j-1;y<=j+1;y++){
                        if(x>=0 && x<m && y>=0 && y<n){
                            if(x==i-1){
                                sum+=prev[y];
                                count++;
                                continue;
                            }
                            else if(x==i && y==j-1){
                                sum+=curr[y];
                                count++;
                                continue;
                            }
                            sum+=img[x][y];
                            count++;
                        }
                    }
                }
                img[i][j] = sum/count;

            }
            prev = curr;
        }
        return img;
    }
};


// we can try to use only one vector for this problem . lets say we use temp where temp stores the previous row value and we will fill it dynamically while iterating the coulmns 
//  temp[j-1] keeps track of img[i][j-1] and a variable preVal will track img[i-1][j-1]
class Solution {
public:
    vector<vector<int>> imageSmoother(vector<vector<int>>& img) {
        int m = img.size();
        int n = img[0].size();

        vector<int>temp(n);
        int preVal = 0;
        for(int i=0;i<m;i++){
            for(int j=0;j<n;j++){
                int sum = 0;
                int cnt = 0;

                if(i+1<m){    // bottom row neighbour 
                    if(j-1>=0){
                        sum+=img[i+1][j-1];
                        cnt++;
                    }
                    sum+=img[i+1][j];
                    cnt++;
                    if(j+1<n){
                        sum+=img[i+1][j+1];
                        cnt++;
                    }
                }

                // next neighbours 
                if(j+1<n){
                    sum+=img[i][j+1];
                    cnt++;
                }
                // curr cell 
                sum+=img[i][j];
                cnt++;

                // previous using temp 
                if(j-1>=0){
                    sum+=temp[j-1];    
                    cnt++;
                }
                // top neighbours 
                if(i-1>=0){
                    if(j-1>=0){
                        sum+=preVal;
                        cnt++;
                    }

                    sum+=temp[j];
                    cnt++;

                    if(j+1<n){
                        sum+=temp[j+1];
                        cnt++;
                    }
                }
                // now updating temp values 
                if(i-1>=0)preVal = temp[j];
                temp[j] = img[i][j];

                img[i][j] = sum/cnt;
            }
        }
        return img;
    }
};