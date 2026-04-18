#include <bits/stdc++.h>
#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
#define int ll
#define pb push_back

using ll = long long;
using namespace std;

const int maxn = 2e6+10;
int lp[maxn];
vector<int> pr;

ll mul(ll a, ll b, ll m) {
	ll ret = a*b - ll((long double)1/m*a*b+0.5)*m;
	return ret < 0 ? ret+m : ret;
}

int pow(int x, int y, int m){
	if (!y) return 1ll;
	int ans = pow(mul(x,x,m), y/2, m);
	return (y&1) ? mul(x,ans,m) : ans;
}

bool prime(int n){
	if (n < 2) return 0;
	if (n <= 3) return 1;
	if ((n&1) == 0) return 0;
	int r = __builtin_ctzll(n-1), d = n >> r;

	for (int a : {2, 325, 9375, 28178, 450775, 9780504, 1795265022}){
		int x = pow(a,d,n);
		if (x == 1 or x == n-1 or a%n == 0) continue;
		for (int j = 0; j < r-1; ++j){
			x = mul(x,x,n);
			if (x == n-1) break;
		}	
		if (x != n-1) return 0;
	}
	return 1;

}

int32_t main() {_
	for (int i = 2; i < maxn; ++i) if (!lp[i]){
		pr.pb(i);
		for (int j = 2*i; j < maxn; j += i) lp[j] = i;
	}

	auto isp = [&](int x){
		for (int i = 2; i*i <= x; ++i){
			while (x%i == 0){
			x /= i;
			}
		}
		return (x > 1);
	};

	vector<int> vec;
	for (auto v : pr){
		int test = v*v + 4;
		if (prime(test)) {
				vec.pb(test);
			}
	}	


	int q; cin >> q;
	while (q--){
		int l, r; cin >> l >> r;
		int vr = upper_bound(vec.begin(), vec.end(), r) - vec.begin();
		int vl = upper_bound(vec.begin(), vec.end(), l-1) - vec.begin();
		cout << vr-vl << endl;
	}
	
}
