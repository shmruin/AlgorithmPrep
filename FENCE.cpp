#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

vector<int> fences;

int areaFences(int left, int right) {

	if (left == right) return fences[left];

	int mid = (left + right) / 2;

	int ret = max(areaFences(left, mid), areaFences(mid + 1, right));

	int lo = mid; int hi = mid + 1;
	int height = min(fences[lo], fences[hi]);

	//This is middle base
	ret = max(ret, height * 2);

	//Until cover all left and right
	while (left < lo || hi < right) {
		//Expand to where height is higher
		if (hi < right && (lo == left || fences[lo - 1] < fences[hi + 1])) {
			++hi;
			height = min(height, fences[hi]);
		}
		else {
			--lo;
			height = min(height, fences[lo]);
		}

		//Get bigger square
		ret = max(ret, height * (hi - lo + 1));
	}

	return ret;
}

int main() {
	
	ios_base::sync_with_stdio(false);

	int C;
	vector<int> ans;

	cin >> C;

	for (int t = 0; t < C; t++) {

		int num;
		
		cin >> num;

		fences.clear();

		for (int i = 0; i < num; i++) {
			int temp;

			cin >> temp;

			fences.push_back(temp);
		}

		int res = areaFences(0, num-1);
		ans.push_back(res);
	}

	for (int i = 0; i < ans.size(); i++) {
		cout << ans[i] << '\n';
	}

	return 0;
}
//Critical Point
// --> Point is doing merging algorithm, and getting merged maximum area btw left and right
// --> Take the higher fence when comparing both side at that moment.
// --> Then also compare the area.
// --> This algorithm has a short mathmatical proof.