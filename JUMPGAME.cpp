#include <iostream>
#include <algorithm>
#include <string>
#include <vector>

using namespace std;

int N, M;
int arr[10][10] = {};
int memo[10][10] = {};

int jumps(int n, int m) {

	//base
	if (n > N - 1 || m > M - 1 || n < 0 || m < 0) return 0;
	if ((n == N - 1) && (m == M - 1)) return 1;

	if (memo[n][m] != -1) return memo[n][m];
	//four case for evert tile n, e, w, s

	int offset = arr[n][m];

	memo[n][m] = jumps(n + offset, m) || jumps(n, m + offset);

	return memo[n][m];
}

int main() {
	ios_base::sync_with_stdio(false);

	memset(memo, -1, sizeof(memo));

	cin >> N >> M;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> arr[i][j];
		}
	}

	int ans = jumps(0, 0);

	cout << ans << '\n';

	return 0;
}
// Critical Points
// --> Easy Quiz !!!!!
// --> I'd better read the rubric more carefully...