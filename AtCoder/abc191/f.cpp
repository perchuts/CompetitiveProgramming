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
const int maxn = 1e6+100;

template<typename X, typename Y> bool ckmin(X& x, const Y& y) { return (y < x) ? (x=y,1):0; }
template<typename X, typename Y> bool ckmax(X& x, const Y& y) { return (x < y) ? (x=y,1):0; }

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int rnd(int l, int r) {
    uniform_int_distribution<int> uid(l, r);
    return uid(rng);
}

char meb[maxn];

void crivo(int lim) {
	for (int i = 2; i <= lim; i++) meb[i] = 2;
	meb[1] = 1;
	for (int i = 2; i <= lim; i++) if (meb[i] == 2)
		for (int j = i; j <= lim; j += i) if (meb[j]) {
			if (meb[j] == 2) meb[j] = 1;
			meb[j] *= j/i%i ? -1 : 0;
		}
}

void solve(){
    int n; cin >> n;
    map<int, vector<int>> sexo;
    vector<int> test;
    int mn = 1e18;
    vector<int> v(n);
    for (auto& x : v) cin >> x, ckmin(mn, x);
    for (int i = 0; i < n; ++i) {
        int x = v[i];
        for (int i = 1; i * i <= x; ++i) {
            if (x % i) continue;
            if (i <= mn) sexo[i].pb(x), test.pb(i);
            if (i * i != x and x/i <= mn) test.pb(x/i), sexo[x/i].pb(x);
        }
    }
    sort(all(test)); test.erase(unique(all(test)), end(test));
    int ans = 0;
    for (auto k : test) {
        int g = sexo[k][0];
        for (auto x : sexo[k]) g = gcd(g, x);
        if (g == k) ans++;
    }
    cout << ans << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
