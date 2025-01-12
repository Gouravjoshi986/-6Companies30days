#include<bits/stdc++.h>
using namespace std;

// we can easily do this using a bfs traversal (multi source) as bfs will take the shortest path/minimum time. 
// we keep a counter of fresh oranges and we also keep track of how many oranges we converted. if it is equal to fresh oranges at start then we return min time. else we return -1 as it is impossible. 

class Solution {
public:
    int orangesRotting(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        vector<vector<int>>vis(m,vector<int>(n,0));
        queue<pair<pair<int,int>,int>>q;  // x,y,t
        int freshCnt = 0;
        // we will insert all the rotten oranges into the queue to start a multi source bfs and we will count the fresh oranges to check at last step 
        for(int i=0;i<m;i++){
            for(int j=0;j<n;j++){
                if(grid[i][j]==2){ // rotten
                    q.push({{i,j},0});
                    vis[i][j]=2;
                }
                else if(grid[i][j]==1)freshCnt++;
            }
        }
        // now for four direction iteration 
        int delrow[] = {0,-1,0,1};
        int delcol[] = {1,0,-1,0};
        int timeCnt = 0,cnt=0;
        while(!q.empty()){
            int x = q.front().first.first;
            int y = q.front().first.second;
            int t = q.front().second;
            timeCnt = max(timeCnt,t);
            q.pop();

            for(int i=0;i<4;i++){
                int xx = x+delrow[i];
                int yy = y+delcol[i];

                if(xx>=0 && xx<m && yy>=0 && yy<n && grid[xx][yy]==1
                && !vis[xx][yy]){
                    q.push({{xx,yy},t+1});
                    vis[xx][yy]=1;
                    cnt++;  // one fresh converted to rotten
                }
            }
        }
        if(cnt==freshCnt)return timeCnt;
        return -1;
    }
}; 

// TC  - bfs traverses all nodes once so  - O(mn) 
// SC - O(mn)  
