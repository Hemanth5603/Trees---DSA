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

int dfsheight(Node* root){
    if(root==NULL) return 0;

    int lh = dfsheight(root->left);
    if(lh==-1) return -1;
    int rh = dfsheight(root->right);
    if(rh==-1) return -1;

    if(abs(lh-rh)>1) return -1;
    return max(lh,rh)+1;

}


bool isbalanced(Node* root){
    return dfsheight(root) != -1;
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
    root->right->right->left = new Node(8);

    cout<<isbalanced(root);
    
}                   



