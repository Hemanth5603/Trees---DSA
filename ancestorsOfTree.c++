#include<iostream>
using namespace std;

struct Node{
    int data;
    Node* left;
    Node* right;
    Node(val){
        data = val;
        left = NULL;
        right = NULL;
    }
};

    vector<int> v;
    bool helper(struct Node *root,int target){
        if(root == NULL) return false;
         
         if(root->data == target) return true;
         
         if(helper(root->left,target) || helper(root->right,target)){
            v.push_back(root->data);
            return true;
         }
         return false;
    }
    
    vector<int> Ancestors(struct Node *root, int target)
    {
        helper(root,target);
        return v;
         
    }


int main(){
    struct Node* root  = new Node(1);
    root->left = new Node(2);
    root->right = new Node(3);
    root->left->left = new Node(4);
    root->left->right = new Node(5);
    root->right->left = new Node(6);
    root->right->right = new Node(7);
    Ancestors(root,5);
    for(auto x: v){
        cout<<x<<" ";
    }

}