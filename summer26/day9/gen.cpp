#include <bits/stdc++.h>
#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
#define pb push_back
#define int ll
using namespace std;

using ll = long long;

mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());

int rnd(int a, int b){
	return uniform_int_distribution<int>(a,b)(rng);
}

int32_t main() {_ 
	int n = rnd(10, 30);
	vector<string> ss;
	int left = n;
	string s;
	while (left) {
		s += char('a' + rnd(0, 3));
		if (rnd(0, 2) == 2) left--, ss.pb(s);
	}
	cout << 0 << endl;
	exit(0);
	cout << n << endl;
	shuffle(begin(ss), end(ss), rng);
	for (auto x : ss) cout << x << endl;
	cout << 0 << endl;
}
