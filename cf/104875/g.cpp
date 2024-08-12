#include <bits/stdc++.h>
#define int long long
#define sz(x) (int) x.size()
#define pb push_back
using namespace std;

using ll = long long;

const int mod = 998244353;
const int inf = 2e9 + 100;
const int magic = 40;
//const int magic = 5;

void flip() {
	cout << "? flip" << endl;
	int x; cin >> x;
}

int right() {
	cout << "? right" << endl;
	int x; cin >> x;
	return x;
}

void answer(int n) {
	cout << "! " << n << endl;
	exit(0);
}

int32_t main() {
	srand(6942069);
	deque<int> str(magic);
	for (int i = 0; i < magic; i++) {
		str[i] = rand() % 2;
	}

	deque<int> window;
	int s; cin >> s;
	for (int i = 0, v = s; ; i++, v = right()) {
		window.push_back(v);
		if (window.size() > magic) window.pop_front();
		
		if (window == str) {
			answer(i + 1 - magic);
		}

		if (i < magic) {
			if (v != str[i]) flip();
		}
	}
	assert(false);	
}
