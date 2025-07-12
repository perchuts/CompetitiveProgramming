#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
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
const int maxn = 1e7+100;

template<typename X, typename Y> bool ckmin(X& x, const Y& y) { return (y < x) ? (x=y,1):0; }
template<typename X, typename Y> bool ckmax(X& x, const Y& y) { return (x < y) ? (x=y,1):0; }

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int rnd(int l, int r) {
    uniform_int_distribution<int> uid(l, r);
    return uid(rng);
}
// Miller-Rabin
//
// Testa se n eh primo, n <= 3 * 10^18
//
// O(log(n)), considerando multiplicacao
// e exponenciacao constantes

ll mul(ll a, ll b, ll m) {
	ll ret = a*b - ll((long double)1/m*a*b+0.5)*m;
	return ret < 0 ? ret+m : ret;
}

ll pow(ll x, ll y, ll m) {
	if (!y) return 1;
	ll ans = pow(mul(x, x, m), y/2, m);
	return y%2 ? mul(x, ans, m) : ans;
}

bool prime(ll n) {
	if (n < 2) return 0;
	if (n <= 3) return 1;
    if (n == 2 or n == 3 or n == 5 or n == 7) return true;
	if (n % 2 == 0) return 0;
    if (n % 3 == 0) return 0;
    if (n % 5 == 0) return 0;
    if (n % 7 == 0) return 0;
	ll r = __builtin_ctzll(n - 1), d = n >> r;

 	// com esses primos, o teste funciona garantido para n <= 2^64
	// funciona para n <= 3*10^24 com os primos ate 41
	for (int a : {2, 325, 9375, 28178, 450775, 9780504, 1795265022}) {
		ll x = pow(a, d, n);
		if (x == 1 or x == n - 1 or a % n == 0) continue;
		
		for (int j = 0; j < r - 1; j++) {
			x = mul(x, x, n);
			if (x == n - 1) break;
		}
		if (x != n - 1) return 0;
	}
	return 1;
}
bool foi[maxn], foi2[maxn], ok[maxn];
void solve() {
    int l, r; cin >> l >> r;
    for (int i = 2; i < min(r+1, maxn); ++i) {
        if (foi[i]) continue;
        for (int j = i * i; j < min(r+1, maxn); j += i) foi[j] = true;
        int lst = 0;
        int pot = 1;
        while (pot <= r / i and pot * i <= l) pot *= i, lst++;
        if (pot <= r / i) {
            pot *= i;
            vector<int> list;
            while (true) { 
                int cara = (l + pot - 1) / pot * pot;
                while (!list.empty() and list.back() >= cara) list.pop_back();
                if (cara <= r) list.pb(cara);
                if (pot > r / i) break;
                pot *= i;
            }
            for (auto x : list) foi2[x-l] = 1;
        }
    }
    int ans = 0;
    for (int i = 1; i <= r-l; ++i) ans += (prime(i+l) or foi2[i]);
    cout << ans+1 << endl;
}

int32_t main() {_
#ifndef gato
    int t = 1; //cin >> t;
    while(t--) solve();
#else
    int t = 1;
    while (true) {
        int my = solve(), ans = brute();
        if (my != ans) {
            cout << "Wrong answer on test " << t << endl;
            cout << "Your output: " << my << endl;
            cout << "Answer: " << ans << endl;
            exit(0);
        }
        cout << "Accepted on test " << t++ << endl;
    }
#endif
}
