#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define int ll
#define fast_io cin.tie(0)->sync_with_stdio(0);
#define endl '\n'

const int INF = 0x3f3f3f3f;
const ll LINF = 0x3f3f3f3f3f3f3f3f;

int32_t main() {
	fast_io;
	string s; cin >> s;
	sort(begin(s), end(s));
	int n = s.size();
	if (s[0] != s.back()) cout << 0 << endl;
	else {
		cout << n-1 << endl;
	} 
	return 0;
}

