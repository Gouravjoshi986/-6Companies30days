#include<bits/stdc++.h>
using namespace std;

// for lexiographically incresing order we can just sort the 
// contacts and then interate over it and insert in ans;
// we can use two pointers to iterate over contacts and contact[j] and query[j] to insert matching words 

// Tc - O(n*min(|contact[i]|,|query|))
// Sc - O(n*m)

class Solution{
public:
    vector<vector<string>> displayContacts(int n, string contact[], string query)
    {
        int m = query.size();
        sort(contact,contact+n);
        vector<vector<string>>ans(m,vector<string>()); // answer for each char
        
        for(int i=0;i<n;i++){
            string word = contact[i];
            // now we check if this word is similar or not to the word before
            if(i>0 && word==contact[i-1])continue;
            int j=0; // pointer to iterate over word and query 
            while(j<m && j<word.size() && query[j]==word[j]){
                ans[j].push_back(word);
                j++;
            }
        }
        for(int i=0;i<m;i++){
            if(ans[i].empty())ans[i].push_back("0");
        }
        return ans;
    }
};

// we can also do it with a trie 
// Time complexity : O(n*max(contact) + |query|*(max(contact + klogk))) k = matching contactsw
// SC - O(n*max(contact) + |query|*n)
class Solution{
private:
    struct TrieNode{
        unordered_map<char,TrieNode*>child;
        vector<string>list;
    };
    TrieNode* root;
    TrieNode* p;
    
    void insert(string s){
        TrieNode* p = root;
        for(char c:s){
            if(p->child[c]==NULL)p->child[c] = new TrieNode();
            p=p->child[c];
            p->list.push_back(s);
        }
    }
    
    vector<string>query(char c){
        if(p==NULL || p->child[c]==NULL){
            p=NULL;
            return {"0"};
        }
        p=p->child[c];
        return p->list;
    }
public:
    vector<vector<string>> displayContacts(int n, string contact[], string s)
    {
        root = new TrieNode();
        p = root;
        
        for(int i=0;i<n;i++)insert(contact[i]);
        
        vector<vector<string>>ans;
        for(int i=0;i<s.length();i++){
            vector<string> list = query(s[i]);
            sort(list.begin(),list.end());
            list.erase(unique(list.begin(),list.end()),list.end());
            ans.push_back(list);
        }
        return ans;
    }
};