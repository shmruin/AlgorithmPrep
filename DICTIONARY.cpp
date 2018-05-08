#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <cmath>

using namespace std;

vector<string> words;

//adjacency metrix
vector< vector<int> > adj;

void makeGraph() {

	adj = vector< vector<int> >(26, vector<int>(26, 0));

	for (int i = 1; i < words.size(); ++i) {

		int j = i - 1;
		int len = min(words[i].size(), words[j].size());

		for (int k = 0; k < len; ++k) {
			if (words[i][k] != words[j][k]) {
				int a = words[j][k] - 'a';
				int b = words[i][k] - 'a';
				adj[a][b] = 1;
				break;
			}
		}
	}
}

vector<int> seen, order;

void dfs(int here) {

	seen[here] = 1;

	for (int there = 0; there < adj.size(); ++there) {
		if (adj[here][there] && !seen[there])
			dfs(there);
	}
	order.push_back(here);
}

vector<int> topologicalSort() {
	int n = adj.size();
	seen = vector<int>(n, 0);
	order.clear();

	for (int i = 0; i < n; ++i) 
		if (!seen[i]) dfs(i);

	reverse(order.begin(), order.end());

	//If cycle exist, return empty vector
	for (int i = 0; i < n; ++i) {
		for (int j = i + 1; j < n; ++j) {
			if (adj[order[j]][order[i]])
				return vector<int>();
		}
	}
	return order;
}

int main() {
	ios_base::sync_with_stdio(false);

	int C;

	cin >> C; cin.ignore();

	for (int t = 0; t < C; ++t) {
		
		adj.clear();
		words.clear();
		int n = 0;

		cin >> n; cin.ignore();

		for (int i = 0; i < n; i++) {
			string temp;
			cin >> temp; cin.ignore();
			words.push_back(temp);
		}
		
		vector<int> ans;

		makeGraph();
		ans = topologicalSort();

		if (ans.empty()) {
			cout << "INVALID HYPOTHESIS" << '\n';
		}
		else {
			for each(int w in ans) {
				char k = w + 'a';
				cout << k << " ";
			}
			cout << '\n';
		}
	}

	return 0;
}
//Critical Points
//--> Use topological sort by dfsAll & reverse