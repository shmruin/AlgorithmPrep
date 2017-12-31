#include <iostream>
#include <algorithm>
#include <string>

using namespace std;

int friends[10][10] = { 0, };
int ans = 0;
int C, n, m;

int matchFriends(bool matchFriendsArr[10]) {
	
	//base
	int firstFree = -1;
	int pass = false;
	for (int t = 0; t < n; t++) {
		if (matchFriendsArr[t] == false) {
			firstFree = t;
			pass = true;
			break;
		}
	}
	if (!pass) return 1;

	int ret = 0;

	//Fix one of the element to the smaller one. fristFree < i , no case that fristFree > i
	for (int i = firstFree+1; i < n; i++) {
		if (friends[firstFree][i] == 1 && friends[i][firstFree] == 1 && matchFriendsArr[i] == false && matchFriendsArr[firstFree] == false) {
			matchFriendsArr[i] = true;
			matchFriendsArr[firstFree] = true;
			ret += matchFriends(matchFriendsArr);
			matchFriendsArr[i] = false;
			matchFriendsArr[firstFree] = false;
		}
	}

	return ret;
}

int main() {

	std::ios_base::sync_with_stdio(false);

	bool taken[10] = { false, };

	cin >> C;
	cin >> n >> m;

	for (int t = 0; t < m; t++) {
		int x, y;
		cin >> x >> y;
		friends[x][y] = 1;
		friends[y][x] = 1;
	}

	ans = matchFriends(taken);

	cout << ans << '\n';

	return 0;
}

//Critical Points
// --> How to avoid from making duplicated set when all process is complete? ans : SHOULD compel some order on the set. like a dictionary order.
// --> Toggling state my 'taken' array, true or false.
// --> Brute force n by n iterator.