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

void solve(int n, int p){
    auto fexp = [&] (int b, int e) {
        int ans = 1;
        while (e) {
            if (e&1) ans = ans * b % p;
            e /= 2, b = b * b % p;
        }
        return ans;
    };
    while (true) {
        //auto get = [&] (int a, int b, int c) {
        //    int s1 = (a + b + c) % p;
        //    int A = fexp(a, n), B = fexp(b, n), C = fexp(c, n);
        //    int s2 = (A + B + C) % p;
        //    int s3 = (A * A + B * B + C * C) % p;
        //    int s4 = ((A * A % p * A) + (B * B % p * B) + (C * C % p * C)) % p;
        //    cout << (s1*s2%p*s3)%p << ' ' << s4 << endl;
        //};
        int a = rnd(1, p-3), b = rnd(a+1, p-2), c = rnd(b+1, p-1);
        int s1 = (a + b + c) % p;
        int A = fexp(a, n), B = fexp(b, n), C = fexp(c, n);
        int s2 = (A + B + C) % p;
        int s3 = (A * A + B * B + C * C) % p;
        int s4 = ((A * A % p * A) + (B * B % p * B) + (C * C % p * C)) % p;
        if (s1 != 0 and s2 != 0 and s3 != 0 and s4 != 0) {
            int f = s1 * s2 % p * s3 % p, g = s4;
            int t = g * fexp(f, p-2) % p;
            a = a * t % p;
            b = b * t % p;
            c = c * t % p;
            vector<int> v = {a, b, c}; sort(all(v));
            for (auto x : v) cout << x << ' ';
            cout << endl;
            return;
        }
    }
}

int32_t main(){_
    int t; cin >> t;
    while (t--) {
        int n, p; cin >> n >> p;
        solve(n, p);
    }
}
