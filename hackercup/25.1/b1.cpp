#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
#define endl '\n'
#define pb push_back
#define _ ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#define ll __int128
#define int long long

using namespace std;

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


ll mul(ll a, ll b, ll m) {
	ll ret = a*b - ll((long double)1/m*a*b+0.5)*m;
	return ret < 0 ? ret+m : ret;
}

ll pow(ll x, ll y, ll m) {
	if (!y) return 1;
	ll ans = pow(mul(x, x, m), y/2, m);
	return y%2 ? mul(x, ans, m) : ans;
}

ll gcd(ll a, ll b) {
    if (a == 0) return b;
    return gcd(b%a, a);
}

bool prime(ll n) {
	if (n < 2) return 0;
	if (n <= 3) return 1;
	if (n % 2 == 0) return 0;

	ll r = __builtin_ctzll(n - 1), d = n >> r;
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

ll rho(ll n) {
	if (n == 1 or prime(n)) return n;
	auto f = [n](ll x) {return mul(x, x, n) + 1;};

	ll x = 0, y = 0, t = 30, prd = 2, x0 = 1, q;
	while (t % 40 != 0 or gcd(prd, n) == 1) {
		if (x==y) x = ++x0, y = f(x);
		q = mul(prd, max(x, y) - min(x, y), n);
		if (q != 0) prd = q;
		x = f(x), y = f(f(y)), t++;
	}
	return gcd(prd, n);
}

vector<long long> fact(long long n) {
	if (n == 1) return {};
	if (prime(n)) return {n};
	ll d = rho(n);
	vector<long long> l = fact(d), r = fact(n / d);
	l.insert(l.end(), r.begin(), r.end());
	return l;
}

void solve() {
    int n, a, b; cin >> n >> a >> b;
    auto ff = fact(b);
    map<int, int> mp;
    for (auto x : ff) mp[x]++;
    vector<ii> bichos;
    for (pair<int, int> z : mp) {
        bichos.pb(z);
    }
    int tp = sz(bichos);
    vector<int> vp(tp);
    auto fexp = [&] (int B, int e) {
        int ans = 1;
        while (e) {
            if (e&1) ans = ans * B % mod;
            e /= 2, B = B * B % mod;
        }
        return ans;
    };
    vector<int> inv(100, 1);
    for (int i = 1; i < 100; ++i) inv[i] = fexp(i, mod-2) * inv[i-1] % mod;
    auto ncr = [&] (int A, int B) {
        ll ans = inv[B];
        for (int i = A; i > A-B; --i) ans = ans * (i%mod) % mod;
        return ans;
    };
    map<int, int> ways;
    auto rec = [&] (auto&& self, int pos, ll val) -> void {
        if (pos == tp) {
            ll tot = 1;
            for (auto x : vp) tot = tot * ncr(n+x-1, x) % mod;
            ways[val] = tot;
            return;
        }
        ll tot = 1;
        for (int i = 0; i <= bichos[pos].second; ++i) {
            vp[pos] = i;
            self(self, pos+1, val*tot);
            tot *= bichos[pos].first;
        }
    };
    rec(rec, 0, 1);
    int ans = 0; 
    for (auto [x, y] : ways) {
        if (x <= a) ans = (ans + ways[x] * ways[b/x]) % mod;
    }
    cout << ans << endl;
}

int32_t main() {_
#ifndef gato
    int t = 1; cin >> t;
    for (int i = 1; i <= t; ++i) {
        cout << "Case #" << i << ": ";
        solve();
    }
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
