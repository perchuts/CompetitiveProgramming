#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

const int MAX = 2e5 + 10;
vector<int> g[MAX];
int n;

void readAndCheckAnswer(InStream& in) {
	string s = in.readLine();
	stringstream ss(s);

	vector<int> order;
	int nxt;
	while (ss >> nxt) {
		order.push_back(nxt);
	}

	vector<int> degree(n + 1);
	for (int i = 1; i <= n; i++) {
		for (int j : g[i])
			degree[j]++;
	}

	for (int i : order) {
		if (1 <= i && i <= n) {
			if (degree[i] != 0) quitf(_wa, "not valid");
			for (int j : g[i]) --degree[j];
		} else {
			quitf(_wa, "v_i not in [1, n]");
		}
	}

	if (degree[1] != 0)
		quitf(_wa, "did not padjo");
}

int main(int argc, char** argv) {
	registerTestlibCmd(argc, argv);

	n = inf.readInt();
	for (int i = 1; i <= n; i++) {
		int k = inf.readInt();
		for (int j = 0; j < k; j++) {
			int pre = inf.readInt();
			g[pre].push_back(i);
		}
	}

	readAndCheckAnswer(ouf);
	readAndCheckAnswer(ans);

	quitf(_ok, "xD");
}
