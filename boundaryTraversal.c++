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


void addLeftBoundary(Node* root, vector<int> &res) // adding all the left nodes
    {
        Node* curr = root->left;
        
        while(curr)
        {
            if(!isLeaf(curr)) res.push_back(curr->data);
            if(curr->left) curr=curr->left;
            else curr=curr->right;
        }
    }
    
    void addRightBoundary(Node* root, vector<int> &res) // adding all the right nodes
    {
        Node* curr = root->right; 
        //stack needed -> LIFO -> 1,3 goes in -> needed 3,1
        stack<int> st;
        while(curr)
        {
            if(!isLeaf(curr)) st.push(curr->data);
            if(curr->right) curr=curr->right;
            else curr=curr->left;
        }
        
        while(!st.empty())
        {
            res.push_back(st.top());
            st.pop();
        }
    }
    
    void addLeaf(Node* root, vector<int> &res) // function to add leaf nodes
    {
        if(isLeaf(root))
        {   res.push_back(root->data);
            return;
        }
        
        if(root->left) addLeaf(root->left,res);
        if(root->right) addLeaf(root->right,res);
    }
    
    bool isLeaf(Node *root) // function to check of the current node is leaf node or not
    {
        return (root->left == NULL and root->right==NULL);
    }
    

    
    
    
public:
    vector <int> boundary(Node *root)
    {
        vector<int> v;
        if(!root) return v;
        if(!isLeaf(root)) v.push_back(root->data);
        addLeftBoundary(root,v);
        addLeaf(root,v);
        addRightBoundary(root,v);
        return v;
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



