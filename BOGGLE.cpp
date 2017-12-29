#include <iostream>
#include <algorithm>
#include <string>

using namespace std;

char board[5][5] = { 'A', };
const int dx[8] = { -1, -1, -1, 1, 1, 1, 0, 0 };
const int dy[8] = { -1, 0, 1, -1, 0, 1, -1, 1 };

// Ruturn the existence of 'word' in BOGGLE board
bool hasWord(int y, int x, const string& word) {

	//base
	//Out of range
	if (y < 0 || x < 0 || y > 5 || x > 5) return false;
	//word not match
	if (board[y][x] != word[0]) return false;
	//if word length is 1 -> true
	if (word.length() == 1) return true;

	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			string remains = word.substr(1);
			if(hasWord(y + dy[j], x + dx[i], remains)) return true;
		}
	}
	
	return false;
}

int main() {

	int N, M;
	string word;
	bool res = false;

	//start point
	cin >> N >> M;
	//word match
	cin >> word;

	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			cin >> board[i][j];
		}
	}

	res = hasWord(N, M, word);

	if (res == true) cout << "TRUE" << endl;
	else cout << "FALSE" << endl;

	return 0;
}


// Critical Point
// --> Recursive of Loop?
// --> Dealing with string, double array
// --> To check some condition at the first of the function
// --> Time Complexity is 8 direction for N-1 word lenght, 8^(N-1). if word is long enough, this will be failed.