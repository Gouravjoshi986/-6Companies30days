#include<bits/stdc++.h>
using namespace std;

// Serialization Time Complexity: O(V)   // v - no of nodes  // H - height of tree/stack
// Serialization Space Complexity: O(V+H)
// Deserialization Time Complexity: O(V)
// Deserialization Space Complexity: O(V+H)

class Codec {
private: 
    struct TreeNode {
        int val;
        TreeNode *left;
        TreeNode *right;
        TreeNode(int x) : val(x), left(NULL), right(NULL) {}
    };
    void helperSerialize(TreeNode* root,string &ans){
        if(root==NULL){
            ans+="#,";
            return;
        }
        ans += (to_string(root->val)+",");
        helperSerialize(root->left,ans);
        helperSerialize(root->right,ans);
    }

    TreeNode* helperDeserialize(stringstream &s){
        string val;
        getline(s,val,',');
        if(val=="#"){
            return NULL;      
        }
        int a = stoi(val);
        TreeNode* root = new TreeNode(a);
        root->left = helperDeserialize(s);
        root->right = helperDeserialize(s);

        return root;
    }
public:

    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        string ans="";
        helperSerialize(root,ans);
        return ans;
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        stringstream s(data);
        return helperDeserialize(s);   
    }
};

// Your Codec object will be instantiated and called as such:
// Codec ser, deser;
// TreeNode* ans = deser.deserialize(ser.serialize(root));