#include <iostream>
#include <algorithm>
#include <string>
#include <vector>

using namespace std;

int cache[101];
int MOD = 1000000007;

int tiling(int n) {
	if (n <= 1) return 1;

	int& ret = cache[n];
	if (ret != -1) return cache[n];

	return ret = (tiling(n - 1) + tiling(n - 2)) % MOD;
}

//asyncTiling = tiling - syncTiling of n/2
int asycTiling(int n) {
	if (n % 2 == 1) {
		return (tiling(n) - tiling(n/2) + MOD) % MOD;
	}
	else {
		return (tiling(n) - tiling(n / 2) - tiling(n / 2 - 1) + 2 * MOD) % MOD;
	}
}

int main() {
	ios_base::sync_with_stdio(false);

	int C;

	cin >> C;

	for (int t = 0; t < C; t++) {
		memset(cache, -1, sizeof(cache));

		int n;

		cin >> n;

		int ans = asycTiling(n);

		cout << ans << '\n';
	}

	return 0;
}

//Critical Points
// --> Dealing with MOD when it comes to a big number
// --> Using pre-solved algorithm