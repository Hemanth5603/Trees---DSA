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

void preorder(struct Node* x){
    if(x==NULL) return;

    cout<<x->data<<" ";
    preorder(x->left);
    preorder(x->right);
}

void inorder(struct Node* node){
    if(node==NULL) return;

    inorder(node->left);
    cout<<node->data<<" ";
    inorder(node->right);
}   



void postorder(struct Node* node){
    if(node==NULL) return;

    postorder(node->left);
    postorder(node->right);
    cout<<node->data<<" ";
}


// creating a basic binary tree 
int main(){
    struct Node* root  = new Node(1);
    root->left = new Node(2);
    root->right = new Node(3);

    root->left->left = new Node(4);
    root->left->right = new Node(5);
    preorder(root);
    cout<<endl;
    inorder(root);
    cout<<endl;
    postorder(root);
}                   



