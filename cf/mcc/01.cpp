#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
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

struct Item {
    int w, v;
    Item(int ww, int vv) {
        w = ww, v = vv;
    }
};

int bestV = 0;
int cost = 0;
vector<bool> current, best;

void go(int W, const vector<Item>& items, int sw, int sv, int d, vector<bool>& taken) {
    cost++;
    int N = items.size();
    
    // optimistic upper bound: take all remaining values
    int remainingV = 0;
    for (int i = d; i < N; ++i) remainingV += items[i].v;

    if (sv + remainingV <= bestV) return;

    if (d == N) {
        if (sv > bestV) {
            bestV = sv;
            best = taken;
        }
    } else {
        if (sw + items[d].w <= W) {
            taken[d] = true;
            go(W, items, sw + items[d].w, sv + items[d].v, d + 1, taken);
            taken[d] = false;
        }
        go(W, items, sw, sv, d + 1, taken);
    }
}

int solve_basic(int W, const vector<Item>& items) {
    int N = items.size();
    bestV = 0;
    cost = 0;
    current.assign(N, false);
    best.assign(N, false);
    go(W, items, 0, 0, 0, current);
    return cost;
}

int size(int w, vector<pair<int, int>> a) {
    int n = a.size();
    int ret = to_string(n).size() + 1;
    for (int i = 0; i < n; i++) {
        ret += to_string(a[i].first).size() + to_string(a[i].second).size() + 2;
    }
    return ret;
}

int32_t main(){_
    vector<ii> caras;
    //int w = 1;
    //while (true) {
    //    caras.pb({1, 1});
    //    if (size(w, caras) > 100) {
    //        caras.pop_back();
    //        break;
    //    }
    //}
    int best_cost = 0;
    vector<ii> opt_c;
    int optw = 0, iter = 30;
    //vector<int> opcoes = {1, 2, 3, 5, 8};
    //for (int __ = 0; __ < iter; ++__) {
    //    int step = 0;
    //    while (true) {
    //        int x = rnd(0, sz(opcoes)-1);
    //        if (sz(caras) != 22) caras.pb({1, 1});
    //        else caras.pb({99, 99});
    //        if (size(30, caras) > 100) {
    //            caras.pop_back();
    //            break;
    //        }
    //    }
    //    int w = 50;
    //    sort(all(caras));
    //    cout << "test: " << __ << ' ';
    //    vector<Item> items;
    //    vector<bool> taken;
    //    for (auto [x, y] : caras) items.push_back(Item(x, y)), taken.pb(0); 
    //    int z = solve_basic(w, items);
    //    cout << w << ' ' << z << endl;
    //    if (ckmax(best_cost, z)) opt_c = caras, optw = w;
    //}
    //for (int __ = 0; __ < iter; ++__) {
    //    auto caras = opt_c;
    //    shuffle(all(caras), rng);
    //    vector<Item> items;
    //    for (auto [x, y] : caras) items.push_back(Item(x, y)); 
    //    int z = solve_basic(optw, items);
    //    cout << optw << ' ' << z << endl;
    //    if (ckmax(best_cost, z)) opt_c = caras, optw = optw;
    //}
    //vector<bool> taken;
    //int x1 = 1, x2 = 5;
    //for (int i = 0; i <= 24; ++i) {
    //    vector<ii> caras;
    //    for (int j = 0; j < i; ++j) caras.pb({x1, x1});
    //    for (int j = i; j < 24; ++j) caras.pb({x2, x2});
    //    vector<Item> bixo;
    //    // 24 - i
    //    for (auto [x, y] : caras) bixo.pb(Item(x, y));
    //    int w = min(99LL, i*x1 + (24-i)*x2 - x2 - 1);
    //    ckmax(w, 1);
    //    int ganho = solve_basic(w, bixo);
    //    cout << i << ": " << ganho << endl;
    //    if (ckmax(best_cost,ganho)) opt_c = caras, optw = w;
    //}
    //for (auto [x, y] : opt_c) items.push_back(Item(x, y)), taken.pb(0); 
    optw = 16;
    vector<Item> items;
    for (int i = 0; i < 23; ++i) items.pb(Item(1, 1));
    items.pb(Item(99, 9));
    best_cost = solve_basic(optw, items);
    cout << best_cost << endl;
    cout << optw << endl;
    for (auto [x, y] : items) cout << x << ' ' << y << endl;
}
