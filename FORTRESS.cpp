#include <iostream>
#include <algorithm>
#include <string>
#include <vector>

using namespace std;

int C, N;
int y[100], x[100], radius[100];

int longest;

struct TreeNode {
	vector<TreeNode*> children;
};

int sqr(int x) {
	return x * x;
}

int sqrdist(int a, int b) {
	return sqr(y[a] - y[b]) + sqr(x[a] - x[b]);
}

bool encloses(int a, int b) {
	return radius[a] > radius[b] && sqrdist(a, b) < sqr(radius[a] - radius[b]);
}

bool isChild(int parent, int child) {
	if (!encloses(parent, child)) return false;
	for (int i = 0; i < N; ++i) {
		if (i != parent && i != child && encloses(parent, i) && encloses(i, child))
			return false;
	}
	return true;
}

TreeNode* getTree(int root) {
	TreeNode* ret = new TreeNode();

	for (int ch = 0; ch < N; ++ch) {
		if (isChild(root, ch))
			ret->children.push_back(getTree(ch));
	}

	return ret;
}

int height(TreeNode* root) {

	vector<int> heights;

	for (int i = 0; i < root->children.size(); ++i) {
		heights.push_back(height(root->children[i]));
	}

	if (heights.empty()) return 0;
	sort(heights.begin(), heights.end());

	//if has child nodes
	if (heights.size() >= 2)
		longest = max(longest, 2 + heights[heights.size() - 2] + heights[heights.size() - 1]);

	return heights.back() + 1;
}

int solve(TreeNode* root) {
	longest = 0;

	int h = height(root);
	return max(longest, h);
}


int main() {
	ios_base::sync_with_stdio(false);

	cin >> C; cin.ignore();

	for (int t = 0; t < C; ++t) {

		cin >> N; cin.ignore();

		memset(y, -1, sizeof(y));
		memset(x, -1, sizeof(x));
		memset(radius, -1, sizeof(radius));

		for (int i = 0; i < N; ++i) {
			cin >> x[i] >> y[i] >> radius[i]; cin.ignore();
		}

		int ans = solve(getTree(0));

		cout << ans << '\n';
	}


	return 0;
}
//Critical Points
//--> Quite difficult to make and travel the Tree...
//--> Think about making tree, get the longest path among the nodes.