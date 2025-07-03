#include <bits/stdc++.h>
#define ONLINE_JUDGE
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

int solve(int n, vector<int> a, vector<int> b) {
    int sa = 0, sb = 0;
    for (int i = 0; i < n; i++) {
        sa += a[i], sb += b[i];
    }

	int na = 0, nb = 0;

    for (int i = 0; i < n; i++) {
        sa -= a[i], sb -= b[i];
		na += max(0LL, a[i] - sb);
		nb += max(0LL, b[i] - sa);
        sa += a[i], sb += b[i];
    }
	//cout << na << " " << nb << " " << na + nb + abs((sa - na) - (sb - nb)) << endl;

	return na + nb + abs((sa - na) - (sb - nb));
}

int32_t main(){_
#ifdef ONLINE_JUDGE
    int t = 1; //cin >> t;
    while(t--) {
		int n; cin >> n;
		vector<int> a(n), b(n);
		for (int i = 0; i < n; i++) {
			cin >> a[i] >> b[i];
		}
		int ans = solve(n, a, b);
		cout << ans << endl;
	}
#else
	for (int seed = 0; seed < 10; seed++) {
		int n = rand() % 3 + 1; n = 3;
		vector<int> a(n), b(n);
		cout << endl;
		cout << n << endl;
		for (int i = 0; i < n; i++) {
			a[i] = rand() % 5;
			b[i] = rand() % 5;
			cout << a[i] << " " << b[i] << endl;
		}
		cout.flush();
		solve(n, a, b);
	}
#endif
}
