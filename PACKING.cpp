#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

using namespace std;

int C, N, W;
string name[100];
int cache[1001][100];
int volume[100], need[100];


int pack(int capacity, int item) {

	//base
	//no more carries
	if (item == N) return 0;

	int& ret = cache[capacity][item];
	if (ret != -1) return ret;

	//not taking this item
	ret = pack(capacity, item + 1);

	//take this item
	if (capacity >= volume[item])
		ret = max(ret, pack(capacity - volume[item], item + 1) + need[item]);

	return ret;
}

void reconstruct(int capacity, int item, vector<string>& picked) {
	//base
	//all items reconstructed
	if (item == N) return;

	if (pack(capacity, item) == pack(capacity, item + 1)) { //case that item is not taken
		reconstruct(capacity, item + 1, picked);
	}
	else { //case that item is taken
		picked.push_back(name[item]);
		reconstruct(capacity - volume[item], item + 1, picked);
	}
}

int main() {
	ios_base::sync_with_stdio(false);

	cin >> C;

	for (int t = 0; t < C; t++) {
		
		for (int i = 0; i < 100; i++) {
			name[i].clear();
		}
		memset(cache, -1, sizeof(cache));
		memset(volume, -1, sizeof(volume));
		memset(need, -1, sizeof(need));

		cin >> N >> W;

		for (int i = 0; i < N; i++) {
			cin >> name[i] >> volume[i] >> need[i];
		}

		vector<string> namelist;

		int res = pack(W, 0);
		reconstruct(W, 0, namelist);

		cout << res << " " << namelist.size() << '\n';

		for (const auto &ans : namelist) {
			cout << ans << '\n';
		}
	}

	return 0;
}
//Critical points
// --> How to make perfect A(n) for dynamic programming?
// --> Write down, think until all return val and parameters are good enought to solve the problem.
