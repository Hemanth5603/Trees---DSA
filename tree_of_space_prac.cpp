#include<bits/stdc++.h>
#include<queue>
using namespace std;


struct Node{
    string name;
    vector<Node*> links;
    Node* parent;
    int dec_locked_count, anc_locked_count;
    int uid;
    bool isLocked = false;

    Node(string str, Node* par){
        name = str;
        parent = par;
        anc_locked_count = 0;
        dec_locked_count = 0;
        uid = 0;
        isLocked = false;
    }
    void addLinks(vector<string> nodes, Node* parent){
        for(auto &it : nodes){
            links.push_back(new Node(it, parent));
        }
    }
     
};



struct Node* buildTree(Node *root, int &m, vector<string> &s){
	queue<Node*> q;
	q.push(root);

	int st = 1;
	while(!q.empty()){
		Node *r = q.front();
		q.pop();

		if(st >= s.size()) continue;

		vector<string> temp;
		for(int i = st; i < st + m; i++)
			temp.push_back(s[i]);
		r->addLinks(temp,r);
		st += m;

		for(auto k: r->links)
			q.push(k);
	}

	return root;
}


class Tree{
    private:
    Node *root;
    unordered_map<string, Node*> map;
    public:
    Tree(Node* r){
        root = r;
    }
    Node* getRoot(){
        return root;
    }

    void populateNodeMap(Node *root){
        if(!root) return;
        map[root->name] = root;
        for(auto it: root->links){
            populateNodeMap(it);
        }
    }


    bool lock(string s, int uid){
        Node *node = map[s];
        if(node->isLocked) return false;

        if(node->anc_locked_count != 0) return false;
        if(node->dec_locked_count != 0) return false;

        Node* currParent = node->parent;
        while(currParent){
            currParent->dec_locked_count++;
            currParent = currParent->parent;
        }
        modifyDecendants(node, 1);
        node->isLocked = true;
        node->uid = uid;
        return true;

    }

    bool unlock(string s, int uid){
        Node* node = map[s];

        if(!node->isLocked) return false;

        if(node->isLocked && node->uid != uid) return false;

        Node* currParent = node->parent;
        while(currParent){
            currParent->dec_locked_count--;
            currParent = currParent->parent;
        }
        modifyDecendants(node, -1);
        node->isLocked = false;
        return true;
    }

    bool upgrade(string s, int uid){
        Node *node = map[s];

        if(node->isLocked) return false;

        if(node->anc_locked_count != 0) return false;
        if(node->dec_locked_count == 0) return false;

        vector<Node*> v;
        if(verifyDecendants(node, uid, v)){
            for(auto it: v){
                unlock(it->name, uid);
            }
        }else return false;
        lock(s, uid);
        return true;
    }

    bool verifyDecendants(Node* root,int uid,vector<Node*> &v){
        if(root->isLocked){
            if(root->uid != uid) return false;
            v.push_back(root);
        }
        if(root->dec_locked_count == 0) return true;

        bool ans = true;
        for(auto it: root->links){
            ans &= verifyDecendants(it, uid, v);
            if(ans == false) return false;
        }
        return ans;

    }




    void modifyDecendants(Node* root, int val){
        for(auto it: root->links){
            it->anc_locked_count += val;
            modifyDecendants(it, val);
        }
    }

    
};




int main(){
    int n, m, queries;
    cin>>n;
    cin>>m;
    cin>>queries;

    vector<string> nodes(n);
    for(int i=0;i<n;i++){
        cin>>nodes[i];
    }

    Node* root = new Node(nodes[0], nullptr);
    root = buildTree(root, m , nodes);
    
    Tree tree(root);
    tree.populateNodeMap(tree.getRoot());

    int op, uid;
    string name;

    for(int i=0;i<queries;i++){
        cin>>op>>name>>uid;
        switch(op){
            case 1: if(tree.lock(name, uid)){
                        cout<<"true"<<endl;
                    }else cout<<"false"<<endl;
                    break;
            case 2: if(tree.unlock(name, uid)){
                        cout<<"true"<<endl;
                    }else cout<<"false"<<endl;
                    break;
            case 3: if(tree.upgrade(name, uid)){
                        cout<<"true"<<endl;
                    }else cout<<"false"<<endl;
                    break;

        }
    }
    return 0;

}