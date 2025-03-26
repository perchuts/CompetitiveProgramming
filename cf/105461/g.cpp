#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
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
	vector<int> a(n+1);
	a[1] = 1;
	for (int i = 2; i <= n; ++i) {
		bool ok = 0;
		for (int j = 2; j * j <= i; ++j) {
			if (i % j) continue;
			ok = 1;
			int cur = i;
			while (cur % j == 0) cur /= j;
			a[i] = a[cur] * a[i/cur];
		}
		if (!ok) {
			cout << "? " << i << endl;
			cin >> a[i];
		}
	}
	crivo(n);
	vector<int> ans(n+1);
	cout << "! ";
    // kp + x, x \in [0, p), k \in [0, q)
    // kp + x === y mod q
    // kp === y-x mod q -> soh tem solucao pra tudo em [0, q) se gcd(p, q) = 1!
    // logo eh por isso que a funcao eh multiplicativa (e nao da pra fazer A(pq) = A(p)A(q) se gcd(p, q) != 1
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j * j <= i; ++j) {
			if (i % j) continue;
			ans[i] += a[j] * meb[j] * i / j;
			if (j * j != i) ans[i] += a[i/j] * meb[i/j] * j;
		}
		cout << ans[i] << ' ';
	}
	cout << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
