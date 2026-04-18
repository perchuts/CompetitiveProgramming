#include <bits/stdc++.h>
#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define int ll
#define pb push_back
#define endl '\n'

using namespace std;

using ll = long long;

int binexp(int a, int b, int mod){
	int res = 1;
	while (b){
		if (b&1) res = res * a % mod;
		a = a * a  % mod;
		b >>= 1;
	}
	return res;
}

int32_t main() {_
	int le, n, m; cin >> le >> n >> m;

	vector<vector<int>> nums;
	vector<int> last;
	for (int i = 0; i < n; ++i){
		int x; cin >> x;
		if (last.empty() or 2*last.back() > x) last.pb(x);
		else{
			nums.pb(last);
			last = {x};
		}
	}
	nums.pb(last);

	int ans = binexp(2,le-nums.back().back());

	int rest = le;
	for (int i = ((int)nums.size())-1; i >= 0; --i)
		int ma = vec.back();
		int per = ma;
		for (int i = 0; i+1 < nums.vec(); ++i) per = gcd(per, vec[i]);
	}


}
