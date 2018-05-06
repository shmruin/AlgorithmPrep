#include <iostream>
#include <algorithm>
#include <functional>
#include <string>
#include <vector>
#include <queue>

using namespace std;

struct RNG {
	int seed, a, b;
	RNG(int _a, int _b) : a(_a), b(_b), seed(1983) {}
	int next() {
		int ret = seed;
		seed = ((seed * (long long)a) + b) % 20090711;
		return ret;
	}
};

int runningMedian(int n, RNG rng) {
	priority_queue<int, vector<int>, less<int>> maxHeap;
	priority_queue<int, vector<int>, greater<int>> minHeap;
	int ret = 0;

	//1. maxHeap size is equal or greater than minHeap
	//2. maxHeap.top() <= minHeap.top()
	for (int cnt = 1; cnt <= n; ++cnt) {
		if (maxHeap.size() == minHeap.size())
			maxHeap.push(rng.next());
		else
			minHeap.push(rng.next());
		//if rule is broken
		if (!minHeap.empty() && !maxHeap.empty() && minHeap.top() < maxHeap.top()) {
			int a = maxHeap.top(), b = minHeap.top();
			maxHeap.pop(); minHeap.pop();
			maxHeap.push(b); minHeap.push(a);
		}

		ret = (ret + maxHeap.top()) % 20090711;
	}

	return ret;
}

int main() {
	ios_base::sync_with_stdio(false);

	int C;

	cin >> C; cin.ignore();

	for (int t = 0; t < C; ++t) {
		int n, a, b;

		cin >> n >> a >> b;

		RNG rng(a, b);

		int ret = runningMedian(n, rng);

		cout << ret << '\n';
	}

	return 0;
}
//Critical Points
//--> Use 'priority_queue' for Heap. How to set fomula of median.
//--> Random number generator