#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
#define endl '\n'
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

vector<int> solve(int n, int q, vector<iii> ops){
    vector<int> pos_nest(n), pos_pigeon(n), inverse(n);
    iota(all(pos_nest), 0);
    pos_pigeon = inverse = pos_nest;
    vector<int> ans;
    for (auto [op, a, b] : ops) {
        --a, --b;
        if (op == 1) {
            pos_pigeon[a] = inverse[b];
        } else if (op == 2) {
            int x = inverse[a], y = inverse[b];
            int z1 = pos_nest[x], z2 = pos_nest[y];
            swap(inverse[z1], inverse[z2]);
            swap(pos_nest[x], pos_nest[y]);
        } else {
            int x = a;
            ans.pb(pos_nest[pos_pigeon[x]]+1);
        }
    }
    return ans;
}

int32_t main(){_
#ifndef gato
    int n, q; cin >> n >> q;
    vector<iii> ops(q);
    for (int i = 0; i < q; ++i) {
        int op; cin >> op;
        if (op == 1) {
            int a, b; cin >> a >> b;
            ops[i] = {op, a, b};
        } else if (op == 2) {
            int a, b; cin >> a >> b;
            ops[i] = {op, a, b};
        } else {
            int x; cin >> x;
            ops[i] = {op, x, 0};
        }
    }
    auto ans = solve(n, q, ops);
    for (auto x : ans) cout << x << endl;
#else
    int t = 1;
    while (true) {
        int n = rnd(2, 50), q = rnd(1, 200);
        vector<vector<int>> caras(n+1);
        for (int i = 1; i <= n; ++i) caras[i].pb(i);
        vector<iii> ops;
        vector<int> resp;
        for (int i = 0; i < q; ++i) {
            int op = rnd(1, 3);
            if (op == 3) {
                int x = rnd(1, n);
                int onde = -1;
                for (int j = 1; j <= n; ++j) {
                    for (auto y : caras[j]) {
                        if (y == x) onde = j;
                    }
                }
                assert(onde != -1);
                resp.pb(onde);
                ops.pb({op, x, -1});
            } else if (op == 1) {
                int a = rnd(1, n), b = rnd(1, n);
                bool ok = 0;
                for (int j = 1; j <= n; ++j) {
                    int pos = -1;
                    for (int k = 0; k < sz(caras[j]); ++k) {
                        if (caras[j][k] == a) pos = k; 
                    }
                    if (pos != -1) {
                        ok = 1;
                        caras[j].erase(begin(caras[j])+pos);
                        break;
                    }
                }
                assert(ok);
                caras[b].pb(a);
                ops.pb({op, a, b});
            } else {
                int a = rnd(1, n-1), b = rnd(a+1, n);
                ops.pb({op, a, b});
                vector<int> na = caras[b], nb = caras[a];
                caras[a] = na, caras[b] = nb;
            }
        }
        auto my = solve(n, q, ops);
        if (my != resp) {
            cout << "Wrong answer on test " << t << endl;
            cout << n << ' ' << q << endl;
            for (auto [x, y, z] : ops) {
                if (x == 3) cout << x << ' ' << y << endl;
                else cout << x << ' ' << y << ' ' << z << endl;
            }
            cout << "Your output: ";
            for (auto x : my) cout << x << ' ';
            cout << endl;
            cout << "Correct answer: ";
            for (auto x : resp) cout << x << ' ';
            cout << endl;
            exit(0);
        }
        cout << "Accepted on test " << t++ << endl;
    }
#endif
}
