#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <cmath>

using namespace std;

int C;
int n;
vector<string> words;
int adj[101][101] = { {0} };
vector<int> final_answer;

void makeAdj() {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (i != j) {
				if (words[i].back() == words[j].front()) adj[i][j]++;
			}
		}
	}
}

void eulerTrail(int here, int adjCpy[][101], vector<int>& answer) {
	for (int there = 0; there < words.size(); there++) {
		while (adjCpy[here][there] > 0) {
			adjCpy[here][there]--;
			adjCpy[there][here]--;
			eulerTrail(there, adjCpy, answer);
		}
	}
	answer.push_back(here);
}

bool checkAllZero(int a[][101], int nums)
{
	for (int i = 0; i < nums; i++) {
		for (int j = 0; j < nums; j++) {
			if (a[i][j] > 0) return false;
		}
	}

	return true;
}


int main() {

	ios_base::sync_with_stdio(false);

	cin >> C;

	for (int t = 0; t < C; t++) {
		cin >> n;
		words.clear();
		final_answer.clear();
		memset(adj, 0, sizeof(adj));

		for (int i = 0; i < n; i++) {
			string input;
			cin >> input;
			words.push_back(input);
		}

		makeAdj();

		//Find euler trail of words that stated from each word
		for (int i = 0; i < words.size(); i++) {

			int adjCpy[101][101];
			int trailLength = 0;
			vector<int> answer;

			memcpy(adjCpy, adj, sizeof(adj));

			eulerTrail(i, adjCpy, answer);

			if (!checkAllZero(adjCpy, n)) answer.clear();

			if (i == 0) {
				final_answer = answer;
			}
			else {
				if (final_answer.size() < answer.size()) final_answer = answer;
			}
		}

		//Reverse the trail
		reverse(final_answer.begin(), final_answer.end());

		//Erase the case that euler circuit is made
		if (final_answer.front() == final_answer.back()) final_answer.erase(final_answer.begin());

		for (int i = 0; i < final_answer.size(); i++) {
			cout << words[final_answer[i]] << ' ';
		}

		//Impossible case when size is zero
		if (final_answer.size() == 0) cout << "IMPOSSIBLE";

		cout << endl;
	}


	return 0;
}

// Critical Points
// --> Euler Trail is simlar to Euler Circuit except the stage of erasing the last line (start - end)
// --> Use adjacent matrix