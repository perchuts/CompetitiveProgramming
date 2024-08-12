#include <bits/stdc++.h>
#define int long long
#define endl '\n'
#define sz(x) (int) x.size()
#define pb push_back
#define _ ios_base::sync_with_stdio(0); cin.tie(0);
using namespace std;

using ll = long long;

const int mod = 998244353;
const int inf = 2e9 + 100;

int32_t main() {_
	int c, d; cin >> c >> d;

	vector<int> fizz, buzz;
	vector<string> A(d - c + 1);
	for (int i = c; i <= d; i++) {
		cin >> A[i - c];
		if (count(A[i - c].begin(), A[i - c].end(), 'F'))
			fizz.push_back(i);
		if (count(A[i - c].begin(), A[i - c].end(), 'B'))
			buzz.push_back(i);
	}

	int f = 1e6, b = 1e6;
	if (fizz.size() >= 2)
		f = fizz[1] - fizz[0];
	else if (fizz.size() == 1)
		f = fizz[0];

	if (buzz.size() >= 2)
		b = buzz[1] - buzz[0];
	else if (buzz.size() == 1)
		b = buzz[0];

	vector<string> gen;
	for (int i = c; i <= d; i++) {
		string s;
		if (i % f == 0) s += "Fizz";
		if (i % b == 0) s += "Buzz";
		if (s == "") s += to_string(i);
		gen.push_back(s);
	}

	assert(gen == A);
	cout << f << " " << b << endl;
}
