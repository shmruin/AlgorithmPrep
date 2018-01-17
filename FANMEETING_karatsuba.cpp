#include <iostream>
#include <algorithm>
#include <string>
#include <vector>

using namespace std;

//a += b*(10^k);
void addTo(vector<int>& a, vector<int>& b, int k);

//a -= b; (a >= b)
void subFrom(vector<int>& a, vector<int>& b);

//Return the result of multiplying two integers -> O(n^lg3)
vector<int> karatsuba(const vector<int>& a, const vector<int>& b) {
	int an = a.size(), bn = b.size();

	if (an < bn) return karatsuba(b, a);

	if (an == 0 || bn == 0) return vector<int>();

	//if size is small enough, O(n^2) normal multiply is faster than karatsuba
	//if (an <= 50) return multiply(a, b);
	int half = an / 2;

	vector<int> a0(a.begin(), a.begin() + half);
	vector<int> a1(a.begin() + half, a.end());
	vector<int> b0(b.begin(), b.begin() + min<int>(b.size(), half)); //for cases when b is size of 1
	vector<int> b1(b.begin() + min<int>(b.size(), half), b.end());

	//(a0 + a1) * (b0 + b1) = a0*b0 + (a1*b0 + a0*b1) + (a1*b1)
	vector<int> z2 = karatsuba(a1, b1);
	vector<int> z0 = karatsuba(a0, b0);

	addTo(a0, a1, 0); addTo(b0, b1, 0);

	vector<int> z1 = karatsuba(a0, b0);
	subFrom(z1, z0);
	subFrom(z1, z2);

	vector<int> ret;
	addTo(ret, z0, 0);
	addTo(ret, z1, half);
	addTo(ret, z2, half + half);
	return ret;
}

int hugs(const string& members, const string& fans) {
	int N = members.size(), M = fans.size();
	vector<int> A(N), B(N);

	for (int i = 0; i < N; i++) A[i] = (members[i] == 'M');
	for (int i = 0; i < M; i++) B[M-i-1] = (fans[i] == 'M');

	//Do karatsuba without raise each digit
	vector<int> C = karatsuba(A, B);
	int allHugs = 0;
	for (int i = N - 1; i < M; i++) {
		if (C[i] == 0) ++allHugs;
	}
	return allHugs;
}

int main() {
	ios_base::sync_with_stdio(false);

	int C;
	vector<int> ans;

	cin >> C;

	for (int t = 0; t < C; t++) {
		string members;
		string fans;

		cin >> members >> fans;

		int res = hugs(members, fans);
		ans.push_back(res);
	}

	for (int i = 0; i < ans.size(); i++) cout << ans[i] << '\n';

	return 0;
}