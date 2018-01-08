#include <iostream>
#include <algorithm>
#include <string>
#include <vector>

using namespace std;

string parts = "";

string reverseQuad(int& pos) {

	char head = parts[pos];
	++pos;
	if (head == 'b' || head == 'w')
		return string(1, head);
	string upperLeft = reverseQuad(pos);
	string upperRight = reverseQuad(pos);
	string lowerLeft = reverseQuad(pos);
	string lowerRight = reverseQuad(pos);
	return string("x") + lowerLeft + lowerRight + upperLeft + upperRight;
}

int main() {
	ios_base::sync_with_stdio(false);

	int C;
	vector<string> ans;

	cin >> C;

	for (int i = 0; i < C; i++) {
		parts = "";

		cin >> parts;

		int start = 0;

		string res = reverseQuad(start);

		ans.push_back(res);
	}

	for (int i = 0; i < C; i++) {
		cout << ans[i] << '\n';
	}

	return 0;
}
//Critical Points
// --> Using 'pos' reference to get the tile iterator
// --> Think-as-a-picture.
// --> Fuck this problem.