#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
#define pb push_back
#define _ ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#define int long long
//#define gato

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
int meb[maxn];
vector<int> divs[maxn];
void crivo(int lim) {
	for (int i = 2; i <= lim; i++) meb[i] = 2;
	meb[1] = 1;
    divs[1].pb(1);
    for (int i = 2; i <= lim; ++i) { 
        for (int j = 1; j * j <= i; ++j) {
            if (i % j) continue;
            divs[i].pb(j);
            if (j * j != i) divs[i].pb(i/j);
        }
    }
	for (int i = 2; i <= lim; i++) if (meb[i] == 2)
		for (int j = i; j <= lim; j += i) if (meb[j]) {
			if (meb[j] == 2) meb[j] = 1;
			meb[j] *= j/i%i ? -1 : 0;
		}
}
int brute(int n, vector<int> p) {
    int ans = 0;
    for (int i = 0; i < n; ++i) for (int j = i; j < n; ++j) {
        if (gcd(i+1, j+1) != 1 and gcd(p[i], p[j]) != 1) ans++;
    }
    return ans;
}
int solve(int n, vector<int> p){
    vector<int> f(n+1), freq(n+1);
    for (int i = 2; i <= n; ++i) {
        vector<int> go;
        for (int j = i; j <= n; j += i) {
            int tot = 0;
            for (auto k : divs[p[j-1]]) {
                if (k == 1) continue;
                freq[k]++;
                tot -= meb[k] * freq[k];
            }
            f[i] += tot;
        }
        for (int j = i; j <= n; j += i) {
            for (auto k : divs[p[j-1]]) freq[k]--; 
        }

    }
    int ans = 0;
    for (int i = 2; i <= n; ++i) {
        for (int j = i; j <= n; j += i) {
            ans += f[j] * meb[j/i];
        }
    }
    return ans;
}

int32_t main(){_
    crivo(200500);
#ifndef gato
    int n; cin >> n;
    vector<int> p(n);
    for (auto& x : p) cin >> x;
    cout << solve(n, p) << endl;
#else
    int t = 1;
    while (true) {
        int n = rnd(10, 100);
        vector<int> p(n); iota(all(p), 1);
        shuffle(all(p), rng);
        cout << p[5] << endl;
        int my = solve(n, p), ans = brute(n, p);
        if (my != ans) {
            cout << "Wrong answer on test " << t << endl;
            cout << n << endl;
            for (auto x : p) cout << x << ' ';
            cout << endl;
            cout << "Your output: " << my << endl;
            cout << "Answer: " << ans << endl;
            exit(0);
        }
        cout << "Accepted on test " << t++ << endl;
    }
#endif
}
