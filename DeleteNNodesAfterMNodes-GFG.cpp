#include<bits/stdc++.h>
using namespace std;
// Just Do what is told.

struct Node {
    int data;
    Node *next;

    Node(int x) {
        data = x;
        next = NULL;
    }
};

class Solution {
  public:
    Node* linkdelete(Node* head, int n, int m) {
        Node* temp = head; 
        int a=0;
        while(temp){
            Node* prev = NULL;
            for(size_t i=0;i<m && temp!=NULL;i++){
                prev = temp;
                temp = temp->next;
            }
            // now prev is on one side of connection 
            for(size_t i=0;i<n && temp!=NULL;i++){
                Node* del = temp;
                temp=temp->next;
                delete del;
            }
            prev->next = temp;
        }
        return head;
    }
};