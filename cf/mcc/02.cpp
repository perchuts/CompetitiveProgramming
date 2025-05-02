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
	Item(int ww, int xx) {
		w = ww;
		v = xx;
	}
};

int W, N, bestV, cost;
std::vector<Item> items;

bool betterDensity(const Item& a, const Item& b) {
    // a.v / a.w > b.v / b.w ⇔ a.v * b.w > b.v * a.w
    long long lhs = 1LL * a.v * b.w;
    long long rhs = 1LL * b.v * a.w;
    if (lhs != rhs) return lhs > rhs;
    return a.w > b.w;
}

bool heuristic(int sw, int sv, int d) {
    // Compute rw = remaining weight we can use
    int rw = W - sw;
    int totalW = 0;
    for (int i = d; i < N; ++i)
        totalW += items[i].w;
    rw = std::min(rw, totalW);

    int rv = bestV + 1 - sv;
    if (rw == 0) return false;

    // Heuristic: items[d].v / items[d].w >= rv / rw ⇔
    // items[d].v * rw >= rv * items[d].w
    return 1LL * items[d].v * rw >= 1LL * rv * items[d].w;
}

void go(int sw, int sv, int d) {
    cost++; // Count every recursive call

    if (d == N) {
        if (sv > bestV) {
            bestV = sv;
            // Optional: save solution
        }
    } else if (sv > bestV || heuristic(sw, sv, d)) {
        if (sw + items[d].w <= W) {
            // Pick item d
            go(sw + items[d].w, sv + items[d].v, d + 1);
            // Drop item d (backtrack implicitly)
        }
        // Skip item d
        go(sw, sv, d + 1);
    }
}

int solve(int w, const std::vector<Item>& input) {
    W = w;
    items = input;
    N = items.size();
    bestV = 0;
    cost = 0;

    std::sort(items.begin(), items.end(), betterDensity);

    go(0, 0, 0);
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
    int optw = 0, iter = 10000;
    vector<int> options = {1, 2, 3, 5, 8};
    for (int __ = 0; __ < iter; ++__) {
        vector<int> a(24), b(24);
        for (auto& x : a) x = options[rnd(0, 4)];
        for (auto& x : b) x = options[rnd(0, 4)];
        sort(all(a)), sort(all(b));
        vector<ii> caras;
        int w = 0;
        for (int i = 0; i < 24; ++i) caras.pb({a[i], b[i]}), w += a[i];
        w /= 3;
        cout << "test: " << __ << ' ';
        vector<Item> items;
        for (auto [x, y] : caras) items.push_back(Item(x, y)); 
        sort(all(items), betterDensity);
        int old = items.back().w;
        items.back().w *= 5, items.back().v *= 5;
        w += items.back().w - old;
        int z = solve(w, items);
        cout << w << ' ' << z << endl;
        if (ckmax(best_cost, z)) opt_c = caras, optw = w;
    }
    vector<Item> items;
    for (auto [x, y] : opt_c) items.push_back(Item(x, y)); 
    best_cost = solve(optw, items);
    cout << best_cost << ' ' << bestV << ' ';
    cout << optw << endl;
    for (auto [x, y] : opt_c) cout << x << ' ' << y << endl;
}
