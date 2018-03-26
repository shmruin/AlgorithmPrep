#include <iostream>
#include <algorithm>
#include <vector>
#include <algorithm>
#include <list>

using namespace std;

int C, N, K;

struct Applicant {
	int idx;
	bool alive;
};

int main() {
	ios_base::sync_with_stdio(false);

	cin >> C;

	for (int t = 0; t < C; ++t) {
		
		cin >> N >> K;

		list<int> lists;

		for (int i = 1; i <= N; i++) {
			lists.push_back(i);
		}

		while (lists.size() > 2) {
			lists.pop_front();

			for (int i = 0; i < K - 1; i++) {
				int temp = lists.front();
				lists.pop_front();
				lists.push_back(temp);
			}
		}

		lists.sort();

		while (!lists.empty()) {
			cout << lists.front() << " ";
			lists.pop_front();
		}

		cout << '\n';
	}

	return 0;
}
//Critical Points
//--> Practice how to use 'list' in c++