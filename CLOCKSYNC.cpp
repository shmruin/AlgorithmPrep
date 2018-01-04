#include <iostream>
#include <algorithm>
#include <string>
#include <vector>

using namespace std;

const int INF = 9999;

vector<int> switchWorks[10] = {
	{0, 1, 2},
	{3,7,9,11},
	{4,10,14,15},
	{0,4,5,6,7},
	{6,7,8,10,12},
	{0,2,14,15},
	{3,14,15},
	{4,5,7,14,15},
	{1,2,3,4,5},
	{3,4,5,9,13}
};

void push(vector<int>& clocks, int swit) {
	for (int i = 0; i < switchWorks[swit].size(); i++) {
		clocks[switchWorks[swit][i]] = (clocks[switchWorks[swit][i]] + 3) % 12;
		if (clocks[switchWorks[swit][i]] == 0) clocks[switchWorks[swit][i]] = 12;
	}
}

int solve(vector<int>& clocks, int swit) {

	//base
	if (swit == 10) {
		bool finish = true;

		for (int i = 0; i < clocks.size(); i++) {
			if (clocks[i] % 12 != 0) finish = false;
		}

		if (finish) return 0;
		else return INF;
	}
	
	int ret = INF;

	for (int nums = 0; nums < 4; nums++) {
		ret = min(ret, nums + solve(clocks, swit + 1));
		push(clocks, swit);
	}

	return ret;
}

int main() {

	ios_base::sync_with_stdio(false);

	int C;
	vector<int> ans;

	

	cin >> C;

	for (int t = 0; t < C; t++) {
		
		vector<int> clocks;
		
		for (int z = 0; z < 16; z++) {
			int k;

			cin >> k;
			clocks.push_back(k);
		}

		int temp = solve(clocks, 0);

		ans.push_back(temp);
	}

	for (int t = 0; t < C; t++) {
		cout << ans[t] << '\n';
	}

	return 0;
}

//Critical Points
// --> The order of pushing switch is not important : only the number of each switch pushed matter
// --> The switch works same every 4times pushed (3, 6, 9, 12'0 clock)
// --> Recursive problem : What should be recursive and what to be increase normally?