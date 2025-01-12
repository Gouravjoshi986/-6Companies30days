#include<bits/stdc++.h>
using namespace std;
// This Problem is same as minimum time to burn the binary tree 
// we will use a bfs traversal and increase time with every move. 
// we cant directly use a bfs on a tree as it doesnt have undirected edges. 
// so we will create it into a graph then do a bfs 

struct TreeNode {
      int val;
      TreeNode *left;
      TreeNode *right;
      TreeNode() : val(0), left(nullptr), right(nullptr) {}
      TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
      TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};
class Solution {
public:
    void convert(TreeNode* curr,int parent,unordered_map<int,unordered_set<int>>&mpp){
        if(curr==NULL)return; 

        if(mpp.find(curr->val)==mpp.end()){
            mpp[curr->val]= unordered_set<int>();
        }
        unordered_set<int>&adjList = mpp[curr->val];
        if(parent!=0)adjList.insert(parent);
        if(curr->left!=NULL)adjList.insert(curr->left->val);
        if(curr->right!=NULL)adjList.insert(curr->right->val);

        convert(curr->left,curr->val,mpp);
        convert(curr->right,curr->val,mpp);
    }
    int amountOfTime(TreeNode* root, int start) {
        unordered_map<int,unordered_set<int>>mpp;
        convert(root,0,mpp);
        queue<int>q;
        q.push(start);
        int minTime=0;
        unordered_set<int>vis;
        vis.insert(start);
        
        while(!q.empty()){
            int sz = q.size();
            while(sz){
                int curr = q.front();
                q.pop();

                for(int num:mpp[curr]){
                    if(vis.find(num)==vis.end()){
                        vis.insert(num);
                        q.push(num);
                    }
                }
                sz--;
            }
            minTime++;
        }
        return minTime-1;
    }
};

// We can also do this in a one pass DFS solution as minimum time taken would be the same as maximum distance of start to any node. 
// https://imgur.com/x5LHXQL  (Very good explanation) 
// GREEN CASE: if root.val == start:
// RED CASE: elif left_depth >= 0 and right_depth >= 0: 
// BLUE CASE else: 

class Solution {
public:
    int maxDist = 0;
    int amountOfTime(TreeNode* root, int start) {
        traverse(root,start);
        return maxDist;
    }
    int traverse(TreeNode* root,int start){
        int depth = 0;
        if(root==NULL)return depth;

        int left = traverse(root->left,start);
        int right = traverse(root->right,start);

        if(root->val==start){
            maxDist = max(left,right);
            depth=-1;
        }
        else if(left>=0 && right>=0){
            depth = max(left,right) + 1;
        }
        else{
            int dist = abs(left)+abs(right);
            maxDist = max(maxDist,dist);
            depth = min(left,right)-1;
        }
        return depth;
    }
};