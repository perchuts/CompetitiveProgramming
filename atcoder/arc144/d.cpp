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
const int maxn = 3e5+100;

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
int fat[maxn], ifat[maxn];

int C2(int a_, int b) {
	return fat[a_] * ifat[b] % mod * ifat[a_-b] % mod;
}

void solve() {
    int n, k; cin >> n >> k;
   	int pot = 1, ans = 0, meusaco1 = 1, meusaco2 = (k+1)%mod;
	for (int j = 0; j <= min(n, k); ++j) {
		int fora = pot * C2(n, j) % mod % mod;
		int dentro = ((1 + k) % mod * meusaco1 % mod * ifat[j] % mod - (j * meusaco2 % mod * ifat[j+1] % mod)%mod + mod) % mod;
		meusaco1 = meusaco1 * ((k - j)%mod) % mod, meusaco2 = meusaco2 * ((k-j)%mod) % mod;
		ans = (ans + fora * dentro) % mod, pot = 2 * pot % mod;
	}
	cout << ans << endl;
}

int32_t main(){
	fat[0] = 1;
	for (int i = 1; i < maxn; ++i) fat[i] = i * fat[i-1] % mod;
	ifat[maxn-1] = fexp(fat[maxn-1], mod - 2);
	for (int i = maxn-2; i >= 0; --i) ifat[i] = (i+1) * ifat[i+1] % mod;
    solve();
}
