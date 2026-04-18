#include <bits/stdc++.h>
#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define int ll
#define endl '\n'
#define pb push_back

using namespace std;

using ll = long long;
const int maxn = 1e6+10;
int fact[maxn];
const int mod = 998244353;
int32_t main() {_
	fact[0] = 1;
	for (int i = 1; i < maxn; ++i) fact[i] = fact[i-1] *i % mod;
		
	int n, m; cin >> n >> m;
	int da = 0, ta = 0, ca = 0;
	int db = 0, tb = 0, cb = 0;

	vector<int> va, vb;
	for (int i = 0; i < n; ++i){
		int x; cin >> x;
		char ch; cin >> ch;
		if (ch == 'D') da += x, ca++;
		else ta += x, va.pb(x);
	}

	for (int i = 0; i < m; ++i){
		int x; cin >> x;
		char ch; cin >> ch;
		if (ch == 'D') db += x, cb++;
		else tb += x, vb.pb(x);
	}

	if (da < db){
		swap(n,m);
		swap(da,db);
		swap(ta,tb);
		swap(ca,cb);
		swap(va,vb);
	}

	int ans = fact[ca] * fact[cb] % mod;

	int st = 0;
	for (auto b : vb){
		if (db+b > da) st++;
	}

	ans = ans * fact[n-ca] % mod;
	if (cb < m){
		ans = ans * st % mod;
		ans = ans * fact[m-cb-1] % mod;
	}

	cout << ans << endl;
}
