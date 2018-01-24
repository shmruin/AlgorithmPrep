#include <iostream>
#include <algorithm>
#include <string>
#include <vector>

using namespace std;

int C;
vector<string> ans;
string pat;
string testee;
int cache[101][101];

bool patternMatching(int idxPat, int idxTest) {

	//base
	if (idxPat == pat.length() && idxTest == testee.length()) {
		cache[idxPat][idxTest] = 1;
		return true;
	}
	if (idxPat == pat.length() && idxTest != testee.length()) {
		cache[idxPat][idxTest] = 0;
		return false;
	}

	if (cache[idxPat][idxTest] != -1) return cache[idxPat][idxTest] == 1 ? true : false;

	//process by '?' and '*' pattern
	if ((pat[idxPat] == testee[idxTest]) || (pat[idxPat] == '?')) {
		bool res = patternMatching(idxPat + 1, idxTest + 1);
		cache[idxPat][idxTest] = (res == true ? 1 : 0);
		return res;
	}
	else if (pat[idxPat] == '*') {

		bool wildMatching = false;

		for (int i = 0; i <= testee.length() - idxTest; i++) {
			wildMatching = (wildMatching || patternMatching(idxPat + 1, idxTest + i));
		}

		cout << idxPat << " , " << testee << '\n';

		cache[idxPat][idxTest] = (wildMatching == true ? 1 : 0);
		return wildMatching;
	}
	else {
		cout << "char not matching!!!" << '\n';
		cout << idxPat << " , " << testee << '\n';
		cache[idxPat][idxTest] = 0;
		return false;
	}
}


int main() {
	ios_base::sync_with_stdio(false);

	cin >> C >> pat;

	for (int t = 0; t < C; t++) {
		int l;

		cin >> l;

		for (int u = 0; u < l; u++) {
			memset(cache, -1, sizeof(cache));

			testee = "";
			cin >> testee;

			//Do test for 'tests' if matching pattern 'pat'
			if (patternMatching(0, 0) == true) ans.push_back(testee);
		}
	}

	for (int i = 0; i < ans.size(); i++) cout << ans[i] << '\n';

	cout << "end!!" << '\n';

	return 0;
}
//Critical Points
// --> Correct Answer.
// --> Check the fact that if wildcard is too long, and lots of matching exists (ex. ******a, aaaaaaaaaab) then execution time will be failed.
// --> Use cache, as what dynamic programming says.
// --> Always do step by step. Slowly & Logically...