#include <iostream>
#include <algorithm>
#include <iterator>
#include <vector>
#include <string>

using namespace std;

int C, N, D, P;
int ways[51][51]; //way map
double pos[51]; //possibility of ways to go to other town
double cache[101][51]; //cache of day n, town m

//Possiblity of existance in town on day.
double isTown(int day, int town) {

	//cout << day << " " << town << '\n';

	if (day == 0) {
		return town == P ? 1.0 : 0.0;
	}

	double& res = cache[day][town];
	if (res != -1.0) return cache[day][town];

	res = 0.0;

	for (int k = 0; k < N; k++) {
		if (ways[town][k] == 1) {
			res += (isTown(day - 1, k) * pos[k]);
		}
	}

	return res;
}

void calcPos() {
	for (int i = 0; i < N; i++) {
		
		int townPos = 0;

		for (int j = 0; j < N; j++) {
			if (ways[i][j] == 1) townPos++;
		}

		pos[i] = (double)(1.0 / townPos);
	}
}

int main() {
	ios_base::sync_with_stdio(false);

	cin >> C;

	for (int t = 0; t < C; t++) {
		fill(&cache[0][0], &cache[0][0] + 101*51, -1.0);
		fill(&pos[0], &pos[0] + 51, 0.0);
		memset(ways, 0, sizeof(ways));

		cin >> N >> D >> P;

		for (int k = 0; k < N; k++) {
			for (int l = 0; l < N; l++) {
				cin >> ways[k][l];
			}
		}

		//initial location of prisoner
		cache[0][P] = 1.0;

		//calculate fixed possability to other town from each one
		calcPos();

		int T;
		vector<double> ans;

		cin >> T;
		
		for (int k = 0; k < T; k++) {
			int Q;
			cin >> Q;

			//Do it
			isTown(D, Q);

			cout << cache[D][Q] << " ";
		}

		cout << '\n';
	}


	return 0;
}
//Critical Points
//--> Nice try to make a paper work first. This is good.
//--> Some cpp syntaxs - like no memset to double - will be important. study.
//--> Have relationship with Makrov chaining