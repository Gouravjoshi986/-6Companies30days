#include<bits/stdc++.h>
using namespace std;

// we can try to use a backtrack solution to explore all paths and choose the minimum cost one
// changing variable -> string source is changing so we will use index as a state 
// BUT THIS WILL NOT GIVE CORRECT ANSWER because there may be intermediate transformations required in this question. exammple a->c->e  if a->e is not possible. 
// So we need the real cost of transformation when we are going via another trans. 

// For this We can use Floyd Warshal Algorithm to find the actual cost (because of via)
// OR we can also try dijkstra algo for shortest path 

// we create 26 nodes for letters and mark directed edges to paths with weights for cost. 
// then we calculate shortest paths from one node to another. (source to target)
// addition of these costs will give us the answer 

class Solution {
private:
    vector<long long> dijkstra(int start,const vector<vector<pair<int,int>>>&adjList){
        priority_queue<pair<long long,int>,vector<pair<long long,int>>,greater<pair<long long,int>>>pq;

        pq.push({0,start});
        vector<long long>dist(26,-1);
        while(!pq.empty()){
            auto top = pq.top();
            long long currCost = top.first;
            int currNode = top.second;
            pq.pop();

            if(dist[currNode]!=-1 && dist[currNode]<currCost)continue;
            
            for(auto& it:adjList[currNode]){
                int adjNode = it.first;
                int convCost = it.second;
                long long newCost = currCost + convCost;

                if(dist[adjNode]==-1 || newCost < dist[adjNode]){
                    dist[adjNode] = newCost;
                    pq.push({newCost,adjNode});
                }
            }
        }
        return dist;
    }
public:
    long long minimumCost(string source, string target, vector<char>& original, vector<char>& changed, vector<int>& cost) {
        vector<vector<pair<int,int>>>adjList(26);
        int n = original.size();
        for(int i=0;i<n;i++){
            adjList[original[i]-'a'].push_back({changed[i]-'a',cost[i]});
        }
        // graph is formed now calc paths 

        vector<vector<long long>>dist(26,vector<long long>(26));
        // from one node to every other node
        for(int i=0;i<26;i++){
            dist[i] = dijkstra(i,adjList);
        } 

        // now all costs are precomputed
        long long ans = 0;
        int len = source.length();
        for(int i=0;i<len;i++){
            if(source[i]!=target[i]){
                long long cost = dist[source[i]-'a'][target[i]-'a'];
                if(cost==-1)return -1;
                ans += cost;
            }
        }
        return ans;
    }
};

// Time complexity: O(m+n)  (adjList-O(m), Dijkstra-O((26+m)log26 * 26),convert-O(n))
// Space complexity: O(m)  // adjList - O(m) , dist - O(26^2) pq-O(m) 


// we can also use floyd warshal algo 
class Solution {
public:
    long long minimumCost(string source, string target, vector<char>& original, vector<char>& changed, vector<int>& cost) {
        int n = original.size();
        vector<vector<long long>>dist(26,vector<long long>(26,INT_MAX));
        
        // initial filling using original and change , cost array
        for(int i=0;i<n;i++){
            int start = original[i]-'a';
            int end = changed[i]-'a';
            dist[start][end] = min(dist[start][end],(long long)cost[i]);
        } 
        // from one node to every other node - FW algo

        for(int via = 0;via<26;via++){
            for(int i=0;i<26;i++){
                for(int j=0;j<26;j++){
                    if(dist[i][via]!=INT_MAX && dist[via][j]!=INT_MAX)
                    dist[i][j] = min(dist[i][j],dist[i][via]+dist[via][j]);
                }
            }
        }
        // now all costs are precomputed
        long long ans = 0;
        int len = source.length();
        for(int i=0;i<len;i++){
            if(source[i]!=target[i]){
                int start = source[i]-'a';
                int end = target[i]-'a';
                
                if(dist[start][end]>=INT_MAX)return -1;
                
                ans += dist[start][end];
            }
        }
        return ans;
    }
};
