#include<bits/stdc++.h>
using namespace std;

struct Node{
    int data;
    struct Node* left;
    struct Node* right;

    Node(int val){
        data = val;
        left = NULL;
        right = NULL;
    }
};


int maxDepth(Node* root){
    if(root==NULL) return 0;

    int ln = maxDepth(root->left);
    int rh = maxDepth(root->right);
    return 1+max(ln,rh);
}




// creating a basic binary tree 
int main(){
    struct Node* root  = new Node(1);
    root->left = new Node(2);
    root->right = new Node(3);

    root->left->left = new Node(4);
    root->left->right = new Node(5);
    root->right->right = new Node(6);
    root->right->left = new Node(7);
    root->right->right->right = new Node(8);

    int Depth = maxDepth(root);
    cout<<Depth<<endl;
    
}                   



