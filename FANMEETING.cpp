#include <iostream>
#include <algorithm>
#include <string>
#include <vector>

using namespace std;

int hugs(string M, string N) {

	vector<int> A;
	vector<int> B;
	int hugNum = 0;

	for (int i = 0; i < M.length(); i++) {
		if (M[i] == 'M') A.push_back(1);
		else A.push_back(0);
	}
	for (int i = 0; i < N.length(); i++) {
		if (N[i] == 'M') B.push_back(1);
		else B.push_back(0);
	}

	for (int i = 0; i < M.length() + N.length() - 1; i++) {
		int C = 0;
		int l = A.size();
		for (int j = l - 1; j >= 0; j--) {
			if (j > i) {
				C = 1;
				break;
			}
			if (i - j >= B.size()) {
				C = 1;
				break;
			}
			else {
				C += (A[j] * B[i - j]);
			}
		}
		cout << C << '\n';
		if (C == 0) hugNum++;
	}

	return hugNum;
}

int main() {

	ios_base::sync_with_stdio(false);

	int C;
	vector<int> ans;

	cin >> C;

	for (int t = 0; t < C; t++) {

		//len(M) < len(N)
		string M;
		string N;
		
		cin >> M >> N;

		int res = hugs(M, N);
		ans.push_back(res);
	}

	for (int i = 0; i < ans.size(); i++) cout << ans[i] << '\n';

	return 0;
}
//Critical Point
// --> Failed Solution
// --> Understande M == 1, F == 0 ... Find M * M == 0. But How?
// --> Fast & Simple(in this case) multiple method - Karatsuba