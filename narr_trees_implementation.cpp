#include<bits/stdc++.h>
using namespace std;


struct TreeNode{
    int data;
    vector<TreeNode*> children;
};

TreeNode* GetNewNode(int data){
    TreeNode* newNode = new TreeNode();
    newNode->data = data;

    return newNode;
}


void addChild(TreeNode* node, int data){
    TreeNode* newNode = GetNewNode(data);
    node->children.push_back(newNode);
}


void print(TreeNode* root){
    cout<< root->data;
    cout<< root->children[0]->data;

}

int main(){
    TreeNode* root;
    root = GetNewNode(3);
    addChild(root, 2);
    addChild(root, 3);
    addChild(root->children[0], 5);
    addChild(root->children[0],6);
    print(root);

}

