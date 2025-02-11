#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
#define endl '\n'
#define pb push_back
#define _ ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#define int ll

using namespace std;

using ll = long long;
using ull = unsigned long long;
using ii = pair<int,int>;
using iii = tuple<int,int,int>;

const int inf = 2e9+1;
const int mod = 1e9+7;
const int maxn = 3e5+100;

template<typename X, typename Y> bool ckmin(X& x, const Y& y) { return (y < x) ? (x=y,1):0; }
template<typename X, typename Y> bool ckmax(X& x, const Y& y) { return (x < y) ? (x=y,1):0; }

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int rnd(int l, int r) {
    uniform_int_distribution<int> uid(l, r);
    return uid(rng);
}
//2 3
//0 1 2 0 3 2 1 3 
//2 2
//0 1 2 1 0 3 2 3 
//2 1
//0 1 0 2 3 1 3 2 
//3 1
//0 1 0 2 3 1 3 2 4 6 7 4 5 7 6 5 
//RESTO TUDO rev(RESTO) 0 TUDO 0 


void solve(){
    int m, k; cin >> m >> k;
	if (k >= (1 << m) or (m == 1 and k == 1)) {
		cout << -1 << endl;
		exit(0);
	}
	vector<int> ans;
	if (k == 0) {
		for (int i = 0; i < (1 << m); ++i) cout << i << ' ' << i << ' ';
		cout << endl;
		exit(0);
	}
	for (int i = 1; i < (1 << m); ++i) if (i != k) cout << i << ' ';
	cout << k << ' ';
	for (int i = (1<<m)-1; i; --i) if (i != k) cout << i << ' ';
	cout << 0 << ' ' << k << ' ' << 0 << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
