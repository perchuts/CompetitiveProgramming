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

void solve(){
    int t, r; cin >> t >> r;
    enum SEXO {
        COMPUTE, LOCK, UNLOCK
    };
    struct task {
        int start, base, ptr, W;
        vector<pair<SEXO, int>> ins;
        task() {}
    };
    vector<task> v(t);
    vector<int> owner(r, -1), ans(t), priority(t), blocked(t), ceiling(r);
    for (int i = 0; i < t; ++i) {
        int m; cin >> v[i].start >> v[i].base >> m;
        v[i].ins.resize(m);
        for (int j = 0; j < m; ++j) {
            string s; cin >> s;
            int x = stoi(s.substr(1, sz(s)-1));
            if (s[0] == 'C') v[i].ins[j] = {COMPUTE, x};
            else if (s[0] == 'L') v[i].ins[j] = {LOCK, x-1}, ckmax(ceiling[x-1], v[i].base);
            else v[i].ins[j] = {UNLOCK, x-1};
        }
        reverse(all(v[i].ins));
    }
    int foi = 0, tempo = 1;
    vector<int> ord(t); iota(all(ord), 0); 
    sort(all(ord), [&] (int x, int y) { return v[x].base > v[y].base; });
    while (foi != t) {
        for (int i = 0; i < t; ++i) priority[i] = v[i].base;
        int mx = -1;
        for (int i = 0; i < r; ++i) if (owner[i] != -1) ckmax(mx, ceiling[i]);
        ii best = {-1, -1};
        for (auto i : ord) {
            blocked[i] = 0;
            if (v[i].ins.empty() or v[i].start > tempo) continue;
            auto [type, id] = v[i].ins.back();
            if (type == LOCK and owner[id] != -1) ckmax(priority[owner[id]], priority[i]), blocked[i] = 1;
            if (type == LOCK) {
                for (int j = 0; j < r; ++j) {
                    if (owner[j] != -1 and owner[j] != i and ceiling[j] >= priority[i]) blocked[i] = 1, ckmax(priority[owner[j]], priority[i]);
                }
            }
            if (!blocked[i]) ckmax(best, pair(priority[i], i));
        }
        int i = best.second;
        if (i == -1) {
            tempo++;
            continue;
        }
        auto& [type, x] = v[i].ins.back();
        if (type == LOCK) {
            assert(owner[x] == -1);
            owner[x] = i;
            v[i].ins.pop_back();
            assert(!v[i].ins.empty());
        } else if (type == UNLOCK) {
            assert(owner[x] == i);
            owner[x] = -1;
            v[i].ins.pop_back();
            if (v[i].ins.empty()) {
                ans[i] = tempo;
                foi++;
            }
        } else {
            x--, tempo++;  
            if (x == 0) v[i].ins.pop_back();
            if (v[i].ins.empty()) {
                ans[i] = tempo;
                foi++;
            }
        }
    }
    for (auto x : ans) cout << x << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
