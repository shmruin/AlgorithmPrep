#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <map>

using namespace std;

int C;

map<int, int> coords;

bool isDominated(int x, int y) {
	map<int, int>::iterator it = coords.lower_bound(x);

	if (it == coords.end()) return false;

	return y < it->second;
}

void removeDominated(int x, int y) {
	map<int, int>::iterator it = coords.lower_bound(x);

	if (it == coords.begin()) return;
	--it;

	while (true) {
		if (it->second > y) break;

		if (it == coords.begin()) {
			coords.erase(it);
			break;
		}
		else {
			map<int, int>::iterator jt = it;
			--jt;
			coords.erase(it);
			it = jt;
		}
	}
}

int registered(int x, int y) {
	if (isDominated(x, y)) return coords.size();
	removeDominated(x, y);
	coords[x] = y;
	return coords.size();
}

int main() {
	ios_base::sync_with_stdio(false);

	cin >> C;

	for (int t = 0; t < C; ++t) {

		int ans = 0;
		int N;

		coords.clear();
		
		cin >> N;

		for (int i = 0; i < N; ++i) {
			int x, y;
			cin >> x >> y;
			ans += registered(x, y);
		}

		cout << ans << '\n';
	}

	return 0;
}
//Critical Points
//--> Think about 2D coordinates.
//--> for coord a, if the right coord is higher then dominated. (binary tree)
//--> if not dominated, for all coords lower y then eliminate them.