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

void solve() {
    int n; cin >> n;
    vector<int> primes, crivo(maxn), a(n);
    for (auto& x : a) cin >> x;
    for (int i = 2; i < maxn and sz(primes) < 1000; ++i) {
        if (crivo[i]) continue;
        primes.pb(i);
        for (int j = i * i; j < maxn; j += i) crivo[j] = 1;
    }
    map<int, int> freq, cmpl;
    int lim = 1e10 + 10;
    for (int i = 0; i < n; ++i) {
        int eu = 1, outro = 1, cur = a[i];
        auto mul = [&] (int& a, int b) {
            if (a == -1) return;
            if (b == -1) a = -1;
            else if (b > lim / a) a = -1;
            else a *= b;
        };
        for (auto p : primes) {
            int cnt = 0;
            while (cur % p == 0) cnt++, cur /= p;
            if (cnt) {
                cnt %= 3;
                if (cnt == 1) eu *= p, mul(outro, p*p);
                else if (cnt == 2) eu *= p * p, mul(outro, p);
            }
        }
        if (cur != 1) {
            // 2 casos: cur tem 1 primo ou 2 primos.
            // definitivamente vai ser necessario adicionar essa info na classe de equivalencia dele.
            int sqr = sqrt(cur), root = -1;
            for (int j = max(2LL, sqr-10); j <= sqr+10; ++j) {
                int k = j; mul(k, k);
                if (k == cur) {
                    root = j; break;
                }
            }
            eu *= cur;
            if (root == -1) {
                int z = cur; mul(z, z); mul(outro, z);
            } else {
                mul(outro, root);
            }
        }
        freq[eu]++;
        cmpl[eu] = outro;
    }
    int ans = 0;
    for (auto [x, y] : freq) {
        // nao posso pegar mais q um bicho
        if (x == 1) {
            ans++;
            continue;
        }
        int z = cmpl[x];
        if (z == -1 or freq.count(z) == false) ans += y;
        else if (x < z) ans += max(freq[x], freq[z]);
    }
    cout << ans << endl;
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
