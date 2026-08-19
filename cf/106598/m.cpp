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
    int p, q; string s, t; cin >> s >> t >> p >> q;
    int n = sz(s), m = sz(t);
    int T = p * n + q * m;
    int N = max(n, m);
    int l = 1, r = T, ans = 0;
    const int B = 10007;
    vector<int> h = {998244353, mod+2};
    vector<vector<int>> pot(sz(h));
    for (int i = 0; i < sz(h); ++i) {
        pot[i].resize(N+1);
        pot[i][0] = 1;
        for (int j = 1; j <= N; ++j) pot[i][j] = pot[i][j-1] * B % h[i];
    }
    // r copies of ith string
    vector<vector<vector<int>>> single(2);
    for (int z = 0; z < 2; ++z) {
        single[z] = vector<vector<int>>(sz(s)+1, vector<int>(sz(h)));
        for (int i = 1; i <= sz(s); ++i) {
            for (int j = 0; j < sz(h); ++j) {
                single[z][i][j] = (B * single[z][i-1][j] + s[i-1]) % h[j];
            }
        }
        swap(s, t);
    }
    auto fexp = [&] (int b, int e, int m) {
        int ans = 1;
        while (e) {
            if (e & 1) ans = ans * b % m;
            e /= 2, b = b * b % m;
        }
        return ans;
    };
    const int LG = 50;
    vector<vector<vector<int>>> pows(2, vector<vector<int>>(LG, vector<int>(sz(h))));
    auto wpp = pows;
    pows[0][0] = single[0].back();
    pows[1][0] = single[1].back();
    for (int j = 0; j < sz(h); ++j) {
        wpp[0][0][j] = fexp(B, sz(s), h[j]);
        wpp[1][0][j] = fexp(B, sz(t), h[j]);
    }
    for (int i = 1; i < LG; ++i) {
        for (int j = 0; j < sz(h); ++j) {
            for (int w = 0; w < 2; ++w) {
                wpp[w][i][j] = wpp[w][i-1][j] * wpp[w][i-1][j] % h[j];
                pows[w][i][j] = (pows[w][i-1][j] * wpp[w][i-1][j] + pows[w][i-1][j]) % h[j];
            }
        }
    }
    // get r copies of ith string
    auto get = [&] (int r, int i) {
        vector<int> res;
        for (int j = 0; j < sz(h); ++j) {
            int cur = 0;
            for (int pw = 0; pw < LG; ++pw) {
                if (r >> pw & 1) {
                    cur = (cur * wpp[i][pw][j] + pows[i][pw][j]) % h[j];
                }
            }
            res.pb(cur);
        }
        return res;
    };
    vector<string> bichos = {s, t};
    auto get2 = [&] (int k, int i) {
        int full_copies = k / sz(bichos[i]);
        auto ans = get(full_copies, i);
        for (int j = 0; j < sz(h); ++j) {
            ans[j] = (ans[j] * pot[j][k % sz(bichos[i])] + single[i][k % sz(bichos[i])][j]) % h[j];
        }
        return ans;
    };

    int ss = p * n, st = q * m;

    auto check = [&] (int md) {
        vector<int> h1, h2;
        if (md > ss) {
            h1 = get(p, 0);
            auto temp = get2(md - ss, 1);
            for (int j = 0; j < sz(h); ++j) h1[j] = (h1[j] * fexp(B, md-ss, h[j]) + temp[j]) % h[j];
        } else h1 = get2(md, 0);

        if (md > st) {
            h2 = get(q, 1);
            auto temp = get2(md - st, 0);
            for (int j = 0; j < sz(h); ++j) h2[j] = (h2[j] * fexp(B, md-st, h[j]) + temp[j]) % h[j];
        } else h2 = get2(md, 1);
        return (h1 == h2);
    };
    while (l <= r) {
        int md = l + (r-l+1)/2;
        if (check(md)) ans = md, l = md+1;
        else r = md-1;
    }

    if (ans == T) cout << "=" << endl;
    else {
        char c1, c2;

        if (ans < ss) c1 = s[ans%n];
        else c1 = t[(ans-ss)%m];
    
        if (ans < st) c2 = t[ans%m];
        else c2 = s[(ans-st)%n];
        
        assert(c1 != c2);

        cout << (c1 < c2 ? "<" : ">") << endl;
    }
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
            cout << "Solve: " << my << endl;
            cout << "Brute: " << ans << endl;
            exit(0);
        }
        cout << "Accepted on test " << t++ << endl;
    }
#endif
}
