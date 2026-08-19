#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
#define pb push_back
#define _ ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#define int ll
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
int tot_ops = 0;
#ifndef gato
void solve() {
#else
vector<int> solve(int q, vector<ii> calls) {
tot_ops = 0;
#endif
#ifndef gato
    int q; cin >> q;
#endif
    vector<deque<int>> qq(5);
    q *= 2;
    vector<ii> ops;
    auto go = [&] (int i, int j) {
        tot_ops++;
        ops.pb({i+1, j+1});
        int k = qq[i].front(); qq[i].pop_front();
        qq[j].pb(k);
    };
    auto merge = [&] (int i, int j) {
        // merge queue j into queue i, mantaining sortness
        if (qq[j].empty()) return;
        int t1 = sz(qq[i]);
        for (int k = 0; k < t1; ++k) {
            while (!qq[j].empty()) {
                int x = qq[j].front();
                if (x > qq[i].front()) break;
                go(j, i);
            }
            go(i, i);
        }
        while (!qq[j].empty()) go(j, i);
    };
    vector<int> onde(4, -1), reservado(5, -1);
    #ifdef gato
vector<int> pops;
#endif
    #ifndef gato
    while (q--) {
        int op; cin >> op;
    #else
        for (auto [op, x] : calls) {     
    #endif
        if (op == 2) {
            int choice = -1;
            for (int i = 0; i < 5; ++i) {
                if (qq[i].empty()) continue;
                if (choice == -1 or qq[choice].front() > qq[i].front()) choice = i;
            }
            #ifndef gato
            cout << choice+1 << endl;
        #else
            pops.pb(qq[choice].front());
        #endif
            qq[choice].pop_front();
        } else {
            #ifndef gato
            int x; cin >> x;
            #endif
            qq[0].pb(x);
            if (onde[0] == -1) {
                for (int i = 1; i < 5; ++i) {
                    if (reservado[i] == -1) { reservado[i] = 0, onde[0] = i; break; }
                }
            }
            merge(onde[0], 0);
            int lim = 9;
            for (int i = 0, lim = 9; i < 4; ++i, lim *= 9) {
                if (sz(qq[onde[i]]) >= lim) {
                    if (onde[i+1] == -1) {
                        onde[i+1] = onde[i], reservado[onde[i]] = i+1;
                        onde[i] = -1;
                        break;
                    }
                    merge(onde[i+1], onde[i]);
                    onde[i] = reservado[onde[i]] = -1;
                } else break; 
            }
            //cout << flush;
            #ifndef gato
            cout << sz(ops) << endl;
            for (auto [x, y] : ops) cout << x << " " << y << endl;
            ops.clear();
             #endif
        }
    }
#ifdef gato
    return pops;
#endif
}

int32_t main() {_
#ifndef gato
    int t = 1; //cin >> t;
    while(t--) solve();
#else
    int t = 1;
    while (true) {
        int q = rnd(5000, 5000);
        vector<int> vals(q);
        set<int> mark;
        for (auto& x : vals) {
            x = rnd(0, 1e18);
            while (mark.find(x) != end(mark)) x = rnd(0, 1e18);
            mark.insert(x);
        }
        set<int> alive;
        vector<ii> ops;
        vector<int> ans;
        for (int i = 0; i < q; ++i) {
            alive.insert(vals[i]);
            ops.pb({1, vals[i]});
            if (rnd(0, 250) == 250) {
                int t = rnd(1, sz(alive));
                for (int j = 0; j < t; ++j) {
                    int x = *begin(alive);
                    ans.pb(x);
                    ops.pb({2, -1});
                    alive.erase(x);
                }
            }
        }
        while (!alive.empty()) {
            int x = *begin(alive);
            ans.pb(x);
            ops.pb({2, -1});
            alive.erase(x);
        }
        auto my = solve(q, ops);
        if (my != ans) {
            cout << "Wrong answer on test " << t << endl;
            cout << "Solve: ";
            for (auto x : my) cout << x << " ";
            cout << endl;
            cout << "Brute: ";
            for (auto x : ans) cout << x << " ";
            cout << endl;
            cout << q << endl;
            exit(0);
        }
        cout << "Accepted on test " << t++ << ' ' << tot_ops << endl;
    }
#endif
}
