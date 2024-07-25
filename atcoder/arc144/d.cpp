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
const int mod = 998244353;
const int maxn = 1e6+100;

template<typename X, typename Y> bool ckmin(X& x, const Y& y) { return (y < x) ? (x=y,1):0; }
template<typename X, typename Y> bool ckmax(X& x, const Y& y) { return (x < y) ? (x=y,1):0; }

int fexp(int b, int e) {
    int ans = 1, p = b;
    while (e) {
        if (e&1) ans = ans * p % mod;
        p = p * p % mod, e /= 2;
    }
    return ans;
}

int C(int a, int b) {
    int ans = 1;
    ckmin(b, a-b);
    a %= mod;
    for (int i = 1; i <= b; ++i) {
        ans = ans * (a-i+1+mod) % mod * fexp(i, mod-2) % mod;
    }
    return ans;
}
int a[10], tot = 0;
void brute(int i, int n, int k) {
	if (i == (1<<n)) {
		for (int j = 0; j < (1<<n); ++j) {
			for (int w = j; w < (1<<n); ++w) {
				if (a[j]+a[w] != a[(j|w)] + a[(j&w)]) return;
			}
		}
		for (int j = 0; j < (1 << n); ++j) cout << a[j] << ' ';
		cout << endl;
		tot++;
		return;
	}
	for (int j = 0; j <= k; ++j) {
		a[i] = j;
		brute(i+1, n, k);
	}
}
void solve() {
    int n, k; cin >> n >> k;
    // if we dont mark anyone (f(0) = 0)
    // C(N+K, N)
    cout << C(n+k, k) << ' ' << (n*C(n+k,k-1))%mod << " " << C(n+k, k-1) << endl;
    int ans = (C(n+k, k) + n*C(n+k,k-1)+C(n+k,k-1))%mod;
	brute(0, n, k);
	cout << tot << ' ';
    cout << ans << endl;
    
}

mt19937 rng(time(0));

int rnd(int l, int r) {
    uniform_int_distribution<int> uid(l, r);
    return uid(rng);
}
int32_t main(){
    solve();
}
