#include <iostream>
#include <cstdlib>
#include <cassert>
#include <string>
#include <vector>
using namespace std;

int main() {
	cin.sync_with_stdio(false);
	int N, K, D;
	cin >> N >> K >> D;
	vector<vector<bool> > strings(N, vector<bool>(K));
	vector<bool> iscandidate(N, true);
	int ncand = N;
	string str;
	for (int i = 0; i < N; ++i) {
		cin >> str;
		for (int j = 0; j < K; ++j)
			strings[i][j] = (str[j] == '1');
	}
	while (ncand > 1) {
cerr << ncand << endl;
		vector<bool> included(N);
		unsigned int nincluded = 0;
		for (int i = 0; i < N; ++i) {
			included[i] = (rand() >> 14) & 1;
			nincluded += included[i] ? 1 : 0;
		}
		vector<int> count(K, 0);
		for (int i = 0; i < N; ++i) {
			if (!included[i]) continue;
			for (int j = 0; j < K; ++j) {
				count[j] += strings[i][j];
			}
		}
		for (int i = 0; i < N; ++i) {
			if (!iscandidate[i]) continue;
			unsigned int sumdif = 0;
			for (int j = 0; j < K; ++j)
				sumdif += (strings[i][j] ? nincluded - count[j] : count[j]);
			unsigned int expectedsumdif = nincluded * D - (included[i] ? D : 0);
			if (sumdif != expectedsumdif) {
				iscandidate[i] = false;
				--ncand;
			}
		}
	}
	int ans = -1;
	for (int i = 0; i < N; ++i) {
		if (iscandidate[i]) {
			ans = i;
		}
	}
	assert(ans != -1);
	for (int i = 0; i < N; ++i) if (i != ans) {
		int dif = 0;
		for (int j = 0; j < K; ++j)
			dif += (strings[i][j] != strings[ans][j]);
		assert(dif == D);
	}
	cout << ans + 1 << endl;
	return 0;
}
