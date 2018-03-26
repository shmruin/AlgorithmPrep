#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <queue>
#include <math.h>

using namespace std;

int C, K, N;

//long long makeAi(int nth) {
//
//	long long prev = 1983;
//
//	for (int i = 0; i < nth; ++i) {
//		prev = (prev * 214013 + 2531011) % (long long)pow(2.0, 32.0);
//	}
//	
//	return prev;
//}
//
//int main() {
//	ios_base::sync_with_stdio(false);
//
//	cin >> C; cin.ignore();
//
//	for (int t = 0; t < C; ++t) {
//		
//		cin >> K >> N; cin.ignore();
//
//		queue<long> numQ;
//		long long sum = 1983;
//		int count = 0;
//		int i = 1;
//
//		numQ.push(1983);
//
//		while(i < N) {
//
//			if (numQ.empty() || sum < K) {
//				long long next = makeAi(i) % 10000 + 1;
//				numQ.push(next);
//				sum += next;
//				i++;
//			}
//			else if (sum == K) {
//				count++;
//
//				long long fronter = numQ.front();
//				numQ.pop();
//				sum -= fronter;
//			}
//			else if (sum > K) {
//				long long fronter = numQ.front();
//				numQ.pop();
//				sum -= fronter;
//			}
//		}
//
//		cout << count << '\n';
//	}
//
//
//	return 0;
//}

struct RNG {
	unsigned seed;
	RNG() : seed(1983) {}
	unsigned next() {
		unsigned ret = seed;
		seed = ((seed * 214013u) + 2531011u);
		return ret % 10000 + 1;
	}
};

int main() {
	ios_base::sync_with_stdio(false);

	cin >> C; cin.ignore();

	for (int t = 0; t < C; ++t) {
		
		cin >> K >> N; cin.ignore();

		queue<long long> range;
		long long rangeSum = 0;
		int ret = 0;

		RNG rng;

		for (int i = 0; i < N; ++i) {
			long long newSignal = rng.next();
			rangeSum += newSignal;
			range.push(newSignal);

			while (rangeSum > K) {
				rangeSum -= range.front();
				range.pop();
			}

			if (rangeSum == K) ret++;
		}

		cout << ret << '\n';
	}


	return 0;
}
//Critical Points
//--> The way to producing by head, tail itself is almost right. tail never decreased, only increase the ranges.
//--> The mistake was in producing RNG. loop makes it O(N), which makes total process O(N^2).
//--> simple RNG structure using structure works. This is the ONLINE ALGORITHM that makes every input on demand.
