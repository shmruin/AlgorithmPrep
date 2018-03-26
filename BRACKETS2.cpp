#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <stack>

using namespace std;

int C;

int main() {
	ios_base::sync_with_stdio(false);

	cin >> C;

	for (int t = 0; t < C; ++t) {
		
		string sentence;
		bool flag = true;

		cin >> sentence; cin.ignore();

		stack<char> bucket;

		for (int i = 0; i < sentence.size(); ++i) {
			if (sentence[i] == ')') {
				if (bucket.top() != '(') {
					flag = false;
					break;
				}
				else {
					bucket.pop();
				}
			}
			else if (sentence[i] == '}') {
				if (bucket.top() != '{') {
					flag = false;
					break;
				}
				else {
					bucket.pop();
				}
			}
			else if (sentence[i] == ']') {
				if (bucket.top() != '[') {
					flag = false;
					break;
				}
				else {
					bucket.pop();
				}
			}
			else {
				bucket.push(sentence[i]);
			}
		}

		if(flag == true)
			cout << "YES" << '\n';
		else
			cout << "NO" << '\n';
	}


	return 0;
}
//Critical Points
//--> An easy stack problem!!! :)