#include <iostream>
#include <algorithm>
#include <string>
#include <vector>

using namespace std;

int cache[101][101];
int n;
int MOD = 10000000;

int poly(int n, int first) {

	if (n == 1 || n == first) return 1;
	
	int& ret = cache[n][first];
	if (ret != -1) return cache[n][first];

	int result = 0;

	int sub = n - first;

	for (int i = 1; i <= sub; i++, first++) {
		int add = poly(sub, i) % MOD;
		result += (first * add);
		result %= MOD;
	}

	return ret = result % MOD;
}

int main() {
	ios_base::sync_with_stdio(false);

	int C;

	cin >> C;

	for (int t = 0; t < C; t++) {
		memset(cache, -1, sizeof(cache));

		cin >> n;

		int ans = 0;

		for (int i = 1; i <= n; i++) {
			int temp = poly(n, i);

			//cout << temp << '\n';


			ans += temp;
			ans %= MOD;
		}

		cout << ans << '\n';
	}

	return 0;
}
//Critical Points
//--> More be careful on MOD operation.
//--> Think dynamic!!!