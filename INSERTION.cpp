#include <iostream>
#include <algorithm>
#include <string>
#include <Vector>
#include <cmath>

using namespace std;

int C, N;
int A[50001];
int shifted[50001];


//Use treap to solve this problem with balanced binary tree
typedef int KeyType;

struct Node {
	KeyType key;

	int priority, size;

	Node* left;
	Node* right;

	Node(const KeyType& _key) : key(_key), priority(rand()), size(1), left(NULL), right(NULL) { }

	void setLeft(Node* newLeft) {
		left = newLeft;
		calcSize();
	}

	void setRight(Node* newRight) {
		right = newRight;
		calcSize();
	}

	void calcSize() {
		size = 1;
		if (left) size += left->size;
		if (right) size += right->size;
	}
};

typedef pair<Node*, Node*> NodePair;

NodePair split(Node* root, KeyType key) {
	if (root == NULL) return NodePair(NULL, NULL);

	if (root->key < key) {
		NodePair rs = split(root->right, key);
		root->setRight(rs.first);
		return NodePair(root, rs.second);
	}

	NodePair ls = split(root->left, key);
	root->setLeft(ls.second);
	return NodePair(ls.first, root);
}

Node* insert(Node* root, Node* node) {
	if (root == NULL) return node;

	if (root->priority < node->priority) {
		NodePair splitted = split(root, node->key);
		node->setLeft(splitted.first);
		node->setRight(splitted.second);
		return node;
	}
	else if (node->key < root->key) {
		root->setLeft(insert(root->left, node));
	}
	else {
		root->setRight(insert(root->right, node));
	}

	return root;
}

//a and b are treap, when max(a) < min(b)
Node* merge(Node* a, Node* b) {
	if (a == NULL) return b;
	if (b == NULL) return a;

	if (a->priority < b->priority) {
		b->setLeft(merge(a, b->left));
		return b;
	}

	a->setRight(merge(a->right, b));
	return a;
}

Node* erase(Node* root, KeyType key) {
	if (root == NULL) return root;

	if (root->key == key) {
		Node* ret = merge(root->left, root->right);
		delete root;
		return ret;
	}

	if (key < root->key)
		root->setLeft(erase(root->left, key));
	else
		root->setRight(erase(root->right, key));

	return root;
}

/* No need treap to calculate kth, countLessThan */

//find kth element with treap
Node* kth(Node* root, int k) {
	int leftSize = 0;
	if (root->left != NULL) leftSize = root->left->size;
	if (k <= leftSize) return kth(root->left, k);
	if (k == leftSize + 1) return root;
	return kth(root->right, k - leftSize - 1);
}

int countLessThan(Node* root, KeyType key) {
	if (root == NULL) return 0;
	if (root->key >= key)
		return countLessThan(root->left, key);
	int ls = (root->left ? root->left->size : 0);
	return ls + 1 + countLessThan(root->right, key);
}

void solve() {
	Node* candidates = NULL;

	for (int i = 0; i < N; ++i) {
		candidates = insert(candidates, new Node(i + 1));
	}

	for (int i = N - 1; i >= 0; --i) {
		int larger = shifted[i];
		Node* k = kth(candidates, i + 1 - larger);
		A[i] = k->key;
		candidates = erase(candidates, k->key);
	}
}

int main() {
	ios_base::sync_with_stdio(false);

	cin >> C; cin.ignore();

	for (int t = 0; t < C; ++t) {

		memset(A, -1, sizeof(A));
		memset(shifted, -1, sizeof(shifted));

		cin >> N;

		for (int i = 0; i < N; ++i) {
			cin >> shifted[i];
		}

		solve();

		for (int i = 0; i < N; ++i) {
			cout << A[i] << " ";
		}

		cout << '\n';
	}

	return 0;
}
//Critical Points
//--> Difficult example of using binary tree to find kth small element reverse.
//--> Practice to use treap; seems good to solve kind of 'balanced binary tree' (with priority)
//--> Too far from here to there... :(