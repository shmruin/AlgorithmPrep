#include <iostream>
#include <algorithm>
#include <string>
#include <vector>

using namespace std;

//Total sequence
vector<int> arr;
//min difficulty at that start point
int cache[10001];


//Return the min difficulty btw two separated sequence
int testifier(int start, int len) {

	int diff = 1;

	//init condition
	bool flag = true;
	int i = 0;

	//case 1 : 333, 5555
	for (i = 0; i < len - 1; ++i) {
		if (arr[start + i] != arr[start + i + 1]) {
			diff = 2;
			flag = false;
		}
	}

	if (flag == true) return diff;

	//init condition
	i = 0;
	flag = true;

	//case 2: 23456, 3210
	int k = arr[start + 1] - arr[start];

	if (k == 1 || k == -1) {
		for (i = 0; i < len - 1; ++i) {
			if (arr[start + i + 1] - arr[start + i] != k) {
				diff = 4;
				flag = false;
			}
		}
	}
	else {
		diff = 4;
		flag = false;
	}

	if (flag == true) return diff;

	//init condition
	i = 0;
	flag = true;

	//case 3: 323, 54545
	int m = arr[start];
	int n = arr[start + 1];

	for (i = 0; i < len - 1; ++i) {
		if ((start % 2 == (start + i) % 2) && (arr[start + i] != m)) {
			diff = 5;
			flag = false;
		}
		if ((start % 2 != (start + i) % 2) && (arr[start + i] != n)) {
			diff = 5;
			flag = false;
		}
	}

	if (flag == true) return diff;

	//init condition
	i = 0;
	flag = true;

	//case 4: 147, 8642
	k = arr[start + 1] - arr[start];

	for (i = 0; i < len - 1; ++i) {
		if (arr[start + i + 1] != arr[start + i] + k) diff = 10; //all other cases are 10
	}

	return diff;
}

//Calculate min difficulty of the current sequence
int diffPi(int start) {

	//Base
	if (start == arr.size()) return 0;

	if (cache[start] != -1) return cache[start];

	int diff = 98;

	//from start point, test 3, 4, 5 digits.
	if (start <= arr.size() - 3) {
		diff = min(diff, testifier(start, 3) + diffPi(start + 3));
		cout << start << " ";
		cout << diff << endl;
	}
	else { //fail
		return cache[start] = 99;
	}
	if (start <= arr.size() - 4) {
		diff = min(diff, testifier(start, 4) + diffPi(start + 4));
		cout << start << " ";
		cout << diff << endl;
	}
	if (start <= arr.size() - 5) {
		diff = min(diff, testifier(start, 5) + diffPi(start + 5));
		cout << start << " ";
		cout << diff << endl;
	}

	return cache[start] = diff;
}


int main() {

	ios_base::sync_with_stdio(false);

	int C;
	vector<int> ans;

	cin >> C;

	cin.ignore(1);

	for (int t = 0; t < C; t++) {

		arr.clear();
		memset(cache, -1, sizeof(cache));

		char a;
		while (cin.get(a) && a != '\n') {
			arr.push_back(a - '0');
		}

		int diff = diffPi(0);
		ans.push_back(diff);
	}

	for (int i = 0; i < ans.size(); i++) cout << ans[i] << '\n';


	return 0;
}
//Critical Points
// --> Idea about dynamic programming is correct.
// --> But should have thought about boundary test and initializing
// --> Is there any way that I can easily deal with C++ I/O? Pretty starnge. Need some googling on competitive programming.
// --> Nice Job :)