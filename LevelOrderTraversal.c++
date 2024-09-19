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



int levelOrder(Node* root){
    vector<vector<int>> ans;
    if(root==NULL){
        queue<Node*> q; 
        q.push(root);
        while(!q.empty()){
            int size = q.size();
            vector<int> level;
            for(int i=0;i<size;i++){
                Node node* = q.front();
                q.pop();
                if(node->left!=NULL) q.push(node->left);
                if(node->right!=NULL) q.push(node->right);
                level.push_back(node->val);

            }
            ans.push_back(level);
        }
        for(int i=0;i<ans.size();i++){
            for(int j=0;j<ans[i].size();j++){
                cout<<ans[j]<<" "<<endl;
            }
        }
    }
}
int levelorder(node* node){
    queue<Node*> q;
    q.push(root);
    while(!q.empty()){
        
    }
}


int main(){
    struct Node* root  = new Node(1);
    root->left = new Node(2);
    root->right = new Node(3);
    root->left->left = new Node(4);
    root->left->right = new Node(5);
    root->right->left = new Node(6);
    root->right->right = new Node(7);
    levelOrder(root);

}