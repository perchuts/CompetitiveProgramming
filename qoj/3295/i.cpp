#include <bits/stdc++.h>
#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define int ll
#define pb push_back
#define endl '\n'

using namespace std;

using ll = long long;

void solve(){
	int n, kk; cin >> n >> kk;
	vector<int> as(n);
	for (int i = 0; i < n; ++i) cin >> as[i];

	vector<int> f(kk+1,n), l(kk+1,-1);
	int ma = 0;
	for (int i = 0; i < n; ++i){
		int x = as[i];
		if (!x) continue;
		f[x] = min(f[x], i);
		l[x] = i;
		ma = max(ma, l[x]-f[x]);
	}
	
	vector<vector<int>> st(n);
	vector<vector<int>> ed(n);
	for (int i = 1; i <= kk; ++i) if (l[i] != -1){
		st[f[i]].pb(i);
		ed[l[i]].pb(i);
	}

	set<int> act;
	for (int i = 0; i < n; ++i){
		for (auto v : st[i]) act.insert(v);
		if (!as[i] and !act.empty()){
			as[i] = *act.begin();
		}
		for (auto v : ed[i]) act.erase(v);
	}

	vector<int> unused;
	for (int i = 1; i <= kk; ++i) if (l[i] == -1) unused.pb(i);

	auto check = [&](int x){
		vector<int> resp(n);
		vector<int> lib;
		vector<int> un = unused;
		vector<int> nf = f;

		for (int i = 0; i < n; ++i){
			if (as[i]){
				resp[i] = as[i];
				lib.pb(as[i]);
				continue;
			}

			while (!lib.empty()){
				int k = lib.back();
				if (i-nf[k] <= x){
					resp[i] = k;
					break;
				}
				lib.pop_back();
			}

			if (resp[i]) continue;

			for (int j = i; j < n and j-i <= x; ++j){
				if (!as[j]) continue;
				int k = as[j];
				if (l[k]-i <= x){
					resp[i] = k;
					nf[k] = i;
					lib.pb(k);
					break;
				}	
			}

			if (resp[i]) continue;
			if (un.empty()) return make_pair(false, resp);
			int k = un.back();
			un.pop_back();
			nf[k] = i;
			lib.pb(k);
			resp[i] = k;
		}
		
		return make_pair(true,resp);
	};

	int lo = ma-1, hi = n-1;
	while (lo+1 < hi){
		int mid = (lo+hi)/2;
		if (check(mid).first) hi = mid;
		else lo = mid;
	}

	vector<int> resp = check(hi).second;
	for (auto v : resp) cout << v << " ";
	cout << endl;
}

int32_t main() {_
	int t; cin >> t;
	while (t--){
		solve();
	}
}
