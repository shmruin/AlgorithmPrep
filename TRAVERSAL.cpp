#include <iostream>
#include <algorithm>
#include <string>
#include <vector>

using namespace std;

int C, N;
vector<int> VLR;
vector<int> LVR;

void LRV(vector<int>& roots, vector<int> lists) {
	if (lists.empty()) return;

	//find v
	int root = roots[0];
	roots.erase(roots.begin());

	vector<int>::iterator idx = find(lists.begin(), lists.end(), root);

	//left
	vector<int> leftLists;
	leftLists.assign(lists.begin(), idx);
	LRV(roots, leftLists);

	//right
	vector<int> rightLists;
	rightLists.assign(idx + 1, lists.end());
	LRV(roots, rightLists);

	//root
	cout << root << " ";

	return;
}

int main() {
	ios_base::sync_with_stdio(false);

	cin >> C; cin.ignore();

	for (int t = 0; t < C; ++t) {

		VLR.clear();
		LVR.clear();

		cin >> N; cin.ignore();

		for (int i = 0; i < N; ++i) {
			int temp;
			cin >> temp;
			VLR.push_back(temp);
		}

		for (int i = 0; i < N; ++i) {
			int temp;
			cin >> temp;
			LVR.push_back(temp);
		}

		cin >> '\n';

		LRV(VLR, LVR);
	}

	return 0;
}
//Critical Points
//--> Basic problem to solve traveling tree
//--> Get root from VLR's first, then split LVR by the root and take the left side first to make LRV. Recursive.