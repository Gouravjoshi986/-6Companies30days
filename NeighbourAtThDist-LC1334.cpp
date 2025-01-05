#include<bits/stdc++.h>
using namespace std;
//  This question can be easily tackled by building a distance vector for cities using floyd warshal algorithm. This will give us distance of each city to every other city. 
// We can then count the distances which are <= threshold. and find the minimum count and its city. 

// TC - O(n^3) SC- O(n^2) 
class Solution {
public:
    int findTheCity(int n, vector<vector<int>>& edges, int distanceThreshold) {
        vector<vector<int>>dist(n,vector<int>(n,1e9));
        // marking self distances as 0 
        for(int i=0;i<n;i++)dist[i][i]=0;

        for(auto edge:edges){
            dist[edge[0]][edge[1]]=edge[2];
            dist[edge[1]][edge[0]]=edge[2];
        }
        for(int via=0;via<n;via++){
            for(int i=0;i<n;i++){
                for(int j=0;j<n;j++){
                    if(dist[i][via]<1e9 && dist[via][i]<1e9){
                          // nodes are connected directly or indirectly 
                          dist[i][j]=min(dist[i][j],dist[i][via]+dist[via][j]);
                    }
                }
            }
        }
        int cityMax=n;
        int cityNo=-1;
        for(int i=0;i<n;i++){
            int count=0;
            for(int j=0;j<n;j++){
                if(dist[i][j]<=distanceThreshold)count++;
            }
            if(count<=cityMax){
                cityMax=count;
                cityNo=i;
            }
        }
        return cityNo;
    }
};

// We can reduce the time complexity using n Dijkstra approach when E << n^2. 
// TC - O(n*(E+nlogn)) = O(n^2 + Elogn) or O(nElogn)  
// SC - O(n^2)

class Solution{
public: 
    int findTheCity(int n, vector<vector<int>>& edges, int distanceThreshold){
        vector<vector<pair<int,int>>>adjList(n);
        for(auto &edge:edges){
            adjList[edge[0]].emplace_back(edge[1],edge[2]);
            adjList[edge[1]].emplace_back(edge[0],edge[2]);
        }

        auto dijkstra = [&](int start)-> vector<int> { // lambda function 
            vector<int>dist(1e9);
            priority_queue<pair<int,int>,vector<pair<int,int>>,greater<>>pq; // min heap
            dist[start]=0;
            pq.emplace(0,start);
            while(!pq.empty()){
                int currentDist = pq.top().first;
                int node = pq.top().second;
                pq.pop();

                if(currentDist>dist[node])continue;

                for(auto& it:adjList[node]){
                    int neighbour = it.first;
                    int weight = it.second;
                    if(dist[node]+weight<dist[neighbour]){
                        dist[neighbour]=dist[node]+weight;
                        pq.emplace(dist[neighbour],neighbour);
                    }
                }
            }
            return dist;
        };
        int cityMax = n;
        int cityNo = -1; 
        for(int i=0;i<n;i++){
            vector<int>distances = dijkstra(i);
            int cnt = 0;
            for(int j=0;j<n;j++){
                if(distances[j]<=distanceThreshold)cnt++;
            }
            if(cnt<=cityMax){
                cityMax=cnt;
                cityNo=i;
            }
        }
        return cityNo;
    }
};