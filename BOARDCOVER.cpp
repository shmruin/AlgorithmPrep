#include <iostream>
#include <algorithm>
#include <string>

using namespace std;

int C, H, W;
int ans = 0;
char board[22][22] = { '#', };
const int coverType[4][3][2] = {
	{ { 0,0 },{ 1, 0 },{ 0, 1 } },
	{ { 0,0 },{ 0, 1 },{ 1, 1 } },
	{ { 0,0 },{ 1, 0 },{ 1, 1 } },
	{ { 0,0 },{ 1, 0 },{ 1, -1 } },
};

int coveringBoard(int pieces) {

	//x, y coordinate of starting point on board
	int dx = 0;
	int dy = 0;

	//base
	for (int i = 0; i < H; i++) {
		for (int j = 0; j < W; j++) {
			if (board[i][j] == '.') {
				if (pieces == 0) return 0;
				else {
					dy = i;
					dx = j;
					goto exit;
				}
			}
		}
	}
	exit:
	if (pieces == 0) return 1;

	int ret = 0;

	//put on the space
	for (int t = 0; t < 4; t++) {
		if (board[dy + coverType[t][0][0]][dx + coverType[t][0][1]] == '.' &&
			board[dy + coverType[t][1][0]][dx + coverType[t][1][1]] == '.' &&
			board[dy + coverType[t][2][0]][dx + coverType[t][2][1]] == '.') {

			board[dy + coverType[t][0][0]][dx + coverType[t][0][1]] = '#';
			board[dy + coverType[t][1][0]][dx + coverType[t][1][1]] = '#';
			board[dy + coverType[t][2][0]][dx + coverType[t][2][1]] = '#';

			ret += coveringBoard(pieces - 1);

			board[dy + coverType[t][0][0]][dx + coverType[t][0][1]] = '.';
			board[dy + coverType[t][1][0]][dx + coverType[t][1][1]] = '.';
			board[dy + coverType[t][2][0]][dx + coverType[t][2][1]] = '.';
		}
	}

	return ret;
}

int main() {

	ios_base::sync_with_stdio(false);

	cin >> C >> H >> W;

	int spaces = 0;

	for (int i = 0; i < H; i++) {
		for (int j = 0; j < W; j++) {
			char z;
			cin >> z;
			board[i][j] = z;
			if (z == '.') spaces++;
		}
	}

	if (spaces % 3 != 0) {
		cout << "0!!!" << '\n';
	}
	else {
		ans = coveringBoard(spaces / 3);
		cout << ans << '\n';
	}

	return 0;
}

//Critical Points
// --> This problem can impel the order by putting block left to right, up to down.
// --> The pre-made block structure for ease
// --> Mistake!!! Using '=' to '=='