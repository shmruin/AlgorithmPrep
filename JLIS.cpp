#include <iostream>
#include <algorithm>
#include <string>
#include <vector>

using namespace std;

int n, m;
int cache[101], S[202];

//Return maximum length of subsequence starting from S[start] (normal lis)
int lis(int start) {
	int& ret = cache[start + 1];
	if (ret != -1) return ret;

	//At lesat S[start]'s length is 1
	ret = 1;
	for (int next = start + 1; next < (n + m - 1); ++next) {
		if (start == -1 || S[start] < S[next]) {
			ret = max(ret, lis(next) + 1);
		}
	}
	
	return ret;
}

void resetSubsequence(vector<int> k) {
	memset(cache, -1, sizeof(cache));
	memset(S, -1, sizeof(S));

	for (int i = 0; i < k.size(); i++) {
		S[i] = k[i];
	}
}

int main() {

	ios_base::sync_with_stdio(false);

	int C;
	vector<int> ans;
	
	cin >> C;

	for (int t = 0; t < C; t++) {
		vector<int> a;
		vector<int> b;

		cin >> n >> m;

		for (int i = 0; i < n; i++) {
			int z;
			cin >> z;

			a.push_back(z);
		}

		for (int j = 0; j < m; j++) {
			int z;
			cin >> z;

			b.push_back(z);
		}

		//the answer of joined longest increasing subsequence is in either res1 or res2
		vector<int> ab = a;
		ab.insert(ab.end(), b.begin(), b.end());
		resetSubsequence(ab);

		int res1 = lis(-1);

		
		ab = b;
		ab.insert(ab.end(), a.begin(), a.end());
		resetSubsequence(ab);

		int res2 = lis(-1);

		ans.push_back(max(res1, res2));
	}

	for (int t = 0; t < ans.size(); t++) cout << ans[t] << '\n';


	return 0;
}
//Critical Points
// --> From lis, do lis on joined two lists.
// --> No greedy soliutions work.
// --> Two possiblities, answer is lis of A + B or B + A (because of pure increasement)
// --> SHOULD REMEMBER NORMAL LIS ALGORITHM.