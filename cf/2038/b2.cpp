#include <bits/stdc++.h>
#define _ ios_base::sync_with_stdio(0); cin.tie(0);
#define int long long
#define endl '\n'
using namespace std;

typedef long long ll;

bool good(ll x, vector<ll> v, int ops){
	int n = v.size(), cost = 1, mod = 2;
	while (cost <= ops) {
		for (int i = 0; i < n; ++i) {
			if (x % mod != v[i] % mod) {
				v[i] += mod/2;
				v[(i-1+n)%n] -= mod;
				ops -= cost;
			}
		}
		mod *= 2, cost *= 2;
	}
	for (int i = 0; i < n; ++i) if (v[i] != x) return false;
	return true;
}
map<vector<int>, bool> foi;
int best;
void go(vector<int> v, int ops) {
	if (foi[v] == true) return;
	bool ok = 1;
	int n = v.size();
	int s = 0;
	for (int i = 0; i < n; ++i) ok &= (v[i] == v[0]), s += v[i]; 
	if (s < 0) return;
	if (ok){
		best = min(best, ops);
		return;
	}
	foi[v] = 1;
	for (int i = 0; i < n; ++i) {
		v[i] -= 2, v[(i+1)%n]++;
		go(v, ops+1);
		v[i] += 2, v[(i+1)%n]--;
	}
}

int32_t main(){ _
	int tc =0 ;
	while(true){
		mt19937 rng(time(0));
		int n = rng() % 10 + 1, tot = 0;
		vector<int> v(n);
		for (auto& x : v) x = rng() % 5, tot += x; 
		foi.clear();
		best = 1e18;
		go(v, 0);
		ll l = 0, r = 1e9, ans = -1;
		while(l <= r){
			ll m = (l+r)/2;
			if(good(m, v, tot)) ans = m, l = m+1;
			else r = m-1;
		}
		if (best == 1e18) best = -1;
		if ((ans == -1 and best != -1) or (ans != -1 and tot-n*ans != best)) {
			cout << 1 << endl;
			cout << n << endl;	

			for (auto x : v) cout << x << ' ';
			cout << endl;
			cout << "Your output: " << tot-n*ans << endl;
			cout << "Answer: " << best << endl;
			exit(0);
		}
		cout << "OK" << ' ' << tc++ << endl;
	}
}

