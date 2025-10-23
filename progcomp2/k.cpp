#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
#define endl '\n'
#define pb push_back
#define _ ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);

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
    int n, m, q; cin >> n >> m >> q;
    int o; cin >> o;
    vector<int> on(n);
    for (int i = 0; i < o; ++i) {
        int x; cin >> x; 
        on[x-1] = 1;
    }
    vector<int> ans(n), cnt(n), imp(n);
    vector<ii> ini(m);
    for (auto& [u, v] : ini) cin >> u >> v, --u, --v, cnt[u]++, cnt[v]++;
    vector<tuple<char, int, int>> qu(q);
    map<ii, int> sexoo;
    for (auto& [a, b, c] : qu) {
        cin >> a >> b; --b;
        if (a == 'A' or a == 'D') {
            cin >> c, --c;
            if (a == 'A' and sexoo[{min(c, b), max(c, b)}] == false) cnt[c]++, cnt[b]++, sexoo[{min(c, b), max(c, b)}] = true;
        }
    }
    vector<unordered_set<int>> sexo(n), sexo2(n);
    for (int i = 0; i < n; ++i) {
        imp[i] = (cnt[i] > 350);
    }
    for (auto [u, v] : ini) {
        sexo[u].insert(v), sexo[v].insert(u);
        if (!imp[v]) ans[u] += on[v];
        else sexo2[u].insert(v); 
        if (!imp[u]) ans[v] += on[u];
        else sexo2[v].insert(u);
    }
    for (int i = 0; i < q; ++i) {
        auto [a, b, c] = qu[i];
        if (a == 'O') {
            on[b] = 1;
            if (!imp[b]) for (auto u : sexo[b]) ans[u]++;
        } else if (a == 'F') {
            on[b] = 0;
            if (!imp[b]) for (auto u : sexo[b]) ans[u]--;
        } else if (a == 'A') {
            if (!imp[b]) sexo[b].insert(c);
            if (!imp[c]) sexo[c].insert(b);
            if (!imp[c]) ans[b] += on[c];
            else sexo2[b].insert(c);
            if (!imp[b]) ans[c] += on[b];
            else sexo2[c].insert(b);
        } else if (a == 'D') {
            if (!imp[b]) sexo[b].erase(c);
            if (!imp[c]) sexo[c].erase(b);
            if (!imp[c]) ans[b] -= on[c];
            else sexo2[b].erase(c);
            if (!imp[b]) ans[c] -= on[b];
            else sexo2[c].erase(b);
        } else {
            int tot = 0;
            for (auto c : sexo2[b]) tot += on[c];
            cout << ans[b]+tot << endl;
        }
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
            cout << "Your output: " << my << endl;
            cout << "Answer: " << ans << endl;
            exit(0);
        }
        cout << "Accepted on test " << t++ << endl;
    }
#endif
}
