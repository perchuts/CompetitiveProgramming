#include <bits/stdc++.h>
#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define int ll
#define pb push_back
#define PI pair<int,int>

using namespace std;

using ll = long long;

map<PI,int> memo;
map<PI,int> qid;
int que;
int ask(int p, int e){
	PI cur = {p,e};
	if (memo.count(cur)) return memo[cur];
	qid[cur] = ++que;
	cout << "? " << p << " " << e << endl;
	int ret; cin >> ret;
	return memo[cur] = ret;
}

void solve(){
	memo.clear();
	qid.clear();
	que = 0;
	int m; cin >> m;
	vector<int> rep(15);
	vector<int> pos(m+1);
	vector<int> ans(m+1);
	vector<int> grandes;
	
	for (int i = 1; i <= m; ++i){
		int lo = -1, hi = 15;
		while (lo+1 < hi){
			int mid = (lo+hi)/2;
			if (ask(rep[mid], i)) hi = mid;
			else lo = mid;
		}

		if (hi == 15) ans[i] = -1;
		else if (hi == 14) grandes.pb(i), ans[i] = 15;
		else{
			pos[i] = hi;
			PI cur = {rep[hi],i};
			assert(qid.count(cur));
			rep[hi] = qid[cur];
		}
	}

	rep[14] = 0;
	for (auto v : grandes){
		cout << "? " << rep[14] << " " << v << endl;
		++que;
		rep[14] = que;	
	}

	for (int i = 1; i <= m; ++i) if (ans[i] == 0){
		int lo = pos[i], hi = 15;	
		while (lo+1 < hi){
			int mid = (lo+hi)/2;
			if (!ask(rep[mid], i)) lo = mid;
			else hi = mid;
		}
		ans[i] = lo+1;
	}

	cout << "! ";
	for (int i = 1; i <= m; ++i){
		if (ans[i] == 15) cout << 0 << " ";
		else cout << ans[i] << " ";
	}
	cout << endl;
    int x; cin >> x;
    assert(x != -1);
}

int32_t main() {_
	int t; cin >> t;
	while (t--){
		solve();
	}
}
