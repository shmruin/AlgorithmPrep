#include <iostream>
#include <algorithm>
#include <string>
#include <vector>

using namespace std;

const int INF = 987654321;

int n, s;
int A[101], pSum[101], pSqSum[101];
int cache[101][11];

void precalc() {
	sort(A, A + n);
	pSum[0] = A[0];
	pSqSum[0] = A[0] * A[0];
	
	for (int i = 1; i < n; i++) {
		pSum[i] = pSum[i - 1] + A[i];
		pSqSum[i] = pSqSum[i - 1] + A[i] * A[i];
	}
}

int minError(int lo, int hi) {
	int sum = pSum[hi] - (lo == 0 ? 0 : pSum[lo - 1]);
	int sqSum = pSqSum[hi] - (lo == 0 ? 0 : pSqSum[lo - 1]);

	int m = int(0.5 + (double)sum / (hi - lo + 1));

	int ret = sqSum - 2 * m * sum + m * m * (hi - lo + 1);

	return ret;
}

int quantize(int from, int parts) {

	//base - all quantize
	if (from == n) return 0;
	//base - Cannot set rest numbers
	if (parts == 0) return INF;

	int& ret = cache[from][parts];
	if (ret != -1) return ret;

	ret = INF;

	for (int partSize = 1; from + partSize <= n; ++partSize) {
		ret = min(ret, minError(from, from + partSize - 1) + quantize(from + partSize, parts - 1));
	}

	return ret;
}

int main() {
	ios_base::sync_with_stdio(false);

	int C;
	vector<int> ans;

	cin >> C;

	for (int t = 0; t < C; t++) {

		memset(A, 0, sizeof(A));
		memset(pSum, 0, sizeof(pSum));
		memset(pSqSum, 0, sizeof(pSqSum));
		memset(cache, -1, sizeof(cache));

		cin >> n >> s;

		for (int i = 0; i < n; i++) {
			cin >> A[i];
		}

		precalc();

		int res = quantize(0, s);
		ans.push_back(res);
	}

	for (int i = 0; i < ans.size(); i++) cout << ans[i] << '\n';

	return 0;
}
//Critical Points!
// --> Still difficult.
// --> Should use 'limited answer' form. "If we sort the original sequence, the quantized sequence numbers are always close each other."
// --> Some mathmatics. simple differential, part sum technique.
// --> Need to sutdy on this chapter further.