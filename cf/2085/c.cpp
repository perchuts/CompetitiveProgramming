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

void solve(int x, int y){
    //int x, y; cin >> x >> y;
    if (x == y) {
        cout << -1 << endl;
        return;
    }
    if (x < y) swap(x, y);
    int k = 0;
	for (int j = 0; (1 << j) < x; ++j) {
		if (x >> j & 1) {}
		else x += (1 << j), y += (1 << j), k += (1 << j);
	}
	x++, y++, k++;
	assert(!(x&y));
    cout << k << endl;
}

int32_t main(){_
	int t; cin >> t;
	while (t--) {
		int x, y; cin >> x >> y;
		solve(x, y);
	}
}
