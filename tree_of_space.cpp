// You are given a complete, balanced N-Ary Tree and must support Q queries. There are 3 kinds of queries. Return true or false depending on whether the query was successful.


// Lock(v, id) - Lock vertex v for user - id
// Unlock(v, id) - If vertex v is locked by the same id, unlock it.
// Upgrade(v, id) - If v is unlocked and has at least one locked vertex in it's subtree and every locked vertex in the subtree of v is locked by id, unlock them and lock v instead.
// Further, here are some additional constraints


// A vertex cannot be locked if it has any locked ancestors or descendants, by any ID.
// When a vertex is upgraded, it's locked descendants are automatically unlocked.
// An upgrade operation is not possible if the vertex is already locked or has any locked ancestors
// An unlock operation is only possible if the vertex is already locked and locked by the same id








#include <bits/stdc++.h>
using namespace std;

struct Node{
	string v;
	vector<Node*> links;
	Node* parent;
	int anc_locked, dec_locked, uid;
	bool isLocked;
	
	Node(string x, Node *p){
		v = x;
		parent = p;
		anc_locked = 0;
		dec_locked = 0;
		uid = 0;
		isLocked = false;
	}

	void addLinks(vector<string> l, Node *p){
		for(auto &i : l)
			links.push_back(new Node(i,p));
	}
};

void printTree(Node *r){
	cout << "Parent: " << r->v << "\n";
	cout << "Child: \n";
	for(auto k : r->links){
		cout << k->v << " anc_locked: " << k->anc_locked 
			<< " dec_locked:" << k->dec_locked << " isLocked:" 
			<< k->isLocked << " uid:" << k->uid << "\n";
	}
	cout << "\n";
	for(auto k : r->links){
		printTree(k);
	}
}

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
		unordered_map<string, Node*> vton;
	public:

		Tree(Node *r){ root = r;}

		Node* getRoot() { return root; }

		void fillVtoN(Node *r){
			if(!r) return;
			vton[r->v] = r;
			for(auto k : r->links)
				fillVtoN(k);
		}

		void informDecendants(Node *r, int val){
			for(auto k: r->links){
				k->anc_locked += val;
				informDecendants(k,val);
			}
			
		}

		

		bool lock(string v, int id){
			Node *t = vton[v];
			if(t->isLocked) return false;

			if(t->anc_locked != 0) return false;
			if(t->dec_locked != 0) return false;

			Node *cur = t->parent;
			while(cur){
				cur->dec_locked++;
				cur = cur->parent;
			}
			informDecendants(t,1);
			t->isLocked = true;
			t->uid = id;
			return true;
		}

		bool unlock(string v, int id){
			Node *t = vton[v];
			if(!t->isLocked) return false;
			if(t->isLocked && t->uid != id) return false;

			Node *cur = t->parent;
			while(cur){
				cur->dec_locked--;
				cur = cur->parent;
			}
			informDecendants(t,-1);
			t->isLocked = false;
			return true;
		}

		bool upgrade(string v, int id){
			Node *t = vton[v];
			if(t->isLocked) return false;

			if(t->anc_locked != 0) return false;
			if(t->dec_locked == 0) return false;

			vector<Node*> vec;
			if(verifyDecendants(t,id,vec)){
				for(auto k : vec){
					unlock(k->v,id);
				}
			}else return false;
			lock(v,id);
			return true;
		}

        // the root will obviously not be locked go along with the recursion 
        bool verifyDecendants(Node *r, int &id, vector<Node*> &v){
			if(r->isLocked){
				if(r->uid != id) return false;
				v.push_back(r);
			}

            // if there are no further locked decendants we return true for that node and need not check for the decendants
			if(r->dec_locked == 0) return true;

			bool ans = true;
			for(auto k: r->links){
				ans &= verifyDecendants(k,id,v);
				if(ans == false) return false;
			}
			return ans;
		}
};

/*
Example Input:
7
2
4
World
Asia
Africa
India
China
SouthAfrica
Egypt
1 China 9
1 India 9
3 Asia 9
2 India 9
*/

int main() {

	/*
	 * INPUT
	 * n = total number of nodes
	 * m = number of child per node
	 * q = number of queries    
	 *
	 * next 'n' lines = node name in string
	 * next 'q' lines = queries with (opcode, string, uid)
	 *
	 * opcode => 1 = Lock, 2 = Unlock, 3 = Upgrade
	*/


	int n,m,q;
	cin >> n;
	cin >> m;
	cin >> q;

	vector<string> s(n);
	for(int i = 0; i < n; i++)
		cin >> s[i];
	
	Node *r = new Node(s[0],nullptr);
	r = buildTree(r,m,s);
	printTree(r);
	
	Tree t(r);
	t.fillVtoN(t.getRoot());

	int op,uid;
	string sq;
	for(int i = 0; i < q; i++){
		cin >> op >> sq >> uid;
		switch(op){
			case 1:	if(t.lock(sq,uid)){
						cout << "true\n";
						//printTree(r);
					}else
						cout << "false\n";
					break;
			case 2:	if(t.unlock(sq,uid))
						cout << "true\n";
					else
						cout << "false\n";
					break;
			case 3:	if(t.upgrade(sq,uid)){
						cout << "true\n";
						//printTree(r);
					}else
						cout << "false\n";
					break;
		}
	}
	return 0;
}