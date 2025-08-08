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

vector<int> solve(int n, vector<ii> a, vector<ii> b) {
    vector<int> p(n);
    set<ii> s;
    vector<iii> ev;
    for (int i = 0; i < n; ++i) ev.pb({a[i].first, a[i].second, i});
    for (int i = 0; i < n; ++i) ev.pb({b[i].first, b[i].second, i+n});
    sort(all(ev));
    for (auto [x, y, id] : ev) {
        if (id >= n) {
            id -= n;
            auto it = s.upper_bound({y, inf});
            if (it == begin(s)) return vector<int>();
            it = prev(it);
            auto [aa, par] = *it;
            p[par] = id;
            s.erase(it);
        } else {
            auto it = s.upper_bound({y, inf});
            if (it != begin(s)) {
                it = prev(it);
            }
            s.insert({y, id});
        }
    }
    auto check = [&] (int i, int j) {
        bool ok = true;
            auto [xa1, ya1] = a[i];
            auto [xa2, ya2] = a[j];
            auto [xb1, yb1] = b[p[i]];
            auto [xb2, yb2] = b[p[j]];
            int i1 = (max(xa1, xa2) > min(xb1, xb2));
            int i2 = (max(ya1, ya2) > min(yb1, yb2));
            int d1 = ((xa1 < xa2 and xb2 < xb1) and (ya1 < ya2 and yb2 < yb1));
            int d2 = ( (xa2 < xa1 and xb1 < xb2) and (ya2 < ya1 and yb1 < yb2));
            ok &= ((i1 or i2) or (d1 and d2));
        return ok;
    };
    bool ok = true;
	// retas do mesmo tipo
    for (int __ = 0; __ < 2; ++__) {
        map<int, vector<ii>> mx;
        for (int i = 0; i < n; ++i) {
            mx[a[i].first].pb({a[i].second, b[p[i]].second});
            if (a[i].first != b[p[i]].first) mx[b[p[i]].first].pb({a[i].second, b[p[i]].second});
            swap(a[i].first, a[i].second);
            swap(b[p[i]].first, b[p[i]].second);
        }
        for (auto [c, v] : mx) {
            sort(all(v));
            int lst = -1;
            for (auto [lx, rx] : v) {
                ok &= (lst < lx);
				lst = rx;
            }
        }
    }
	if (!ok) return vector<int>();
	vector<array<int, 4>> ev2;
	vector<multiset<int>> add(n);
	for (int i = 0; i < n; ++i) {
		ev2.pb({a[i].second, 2, i, 0});
		if (b[p[i]].second != a[i].second) ev2.pb({b[p[i]].second, 2, i, 0});
		if (a[i].second == b[p[i]].second) continue;
		ev2.pb({a[i].second, 1, a[i].first, i});
		ev2.pb({b[p[i]].second, -1, a[i].first, i});
		if (b[p[i]].first != a[i].first) {
			ev2.pb({a[i].second, 1, b[p[i]].first, i});
			ev2.pb({b[p[i]].second, -1, b[p[i]].first, i});
		}
	}
	sort(all(ev2));
	multiset<int> mt;
	for (auto [col, tipo, l, r] : ev2) {
		if (tipo == 2) {
			int id = l;
			int lx = a[id].first, rx = b[p[id]].first;
			for (auto z : add[id]) mt.erase(mt.find(z));
			auto k = mt.lower_bound(lx);
			if (k != end(mt) and (*k) <= rx) return vector<int>();
			for (auto z : add[id]) mt.insert(z);
		} else if (tipo == 1) {
			mt.insert(l);
			add[r].insert(l);
		} else {
			mt.erase(mt.find(l));
			add[r].erase(add[r].find(l));
		}
	}
	return p;
}

vector<int> brute(int n, vector<ii> a, vector<ii> b) {
    vector<int> p(n); iota(all(p), 0);
    do {
        bool ok = 1;
        for (int i = 0; i < n; ++i) {
            ok &= (a[i].first <= b[p[i]].first and a[i].second <= b[p[i]].second);
        }
        if (!ok) continue;
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                auto [xa1, ya1] = a[i];
                auto [xa2, ya2] = a[j];
                auto [xb1, yb1] = b[p[i]];
                auto [xb2, yb2] = b[p[j]];
                int i1 = (max(xa1, xa2) > min(xb1, xb2));
                int i2 = (max(ya1, ya2) > min(yb1, yb2));
                int d1 = ((xa1 < xa2 and xb2 < xb1) and (ya1 < ya2 and yb2 < yb1));
                int d2 = ( (xa2 < xa1 and xb1 < xb2) and (ya2 < ya1 and yb1 < yb2));
                ok &= ((i1 or i2) or (d1 or d2));
				if (!ok) break;
            }
			if (!ok) break;
        }
        if (ok) return p;
    } while (next_permutation(all(p)));
    return vector<int>();
}

int32_t main() {_
#ifndef gato
    int t = 1; //cin >> t;
	int n; cin >> n;
	vector<ii> a(n), b(n);
	for (auto& [x, y] : a) cin >> x >> y;
	for (auto& [x, y] : b) cin >> x >> y;
	auto ans = solve(n, a, b);
	//auto ans = brute(n, a, b);
	if (ans.empty()) cout << "syntax error" << endl;
	else {
		for (auto x : ans) cout << x + 1 << endl;
	}
#else
    int t = 1;
    while (true) {
        int n = rnd(1, 10), c = 150;
        vector<ii> a(n), b(n);
        for (auto& [x, y] : a) x = rnd(0, c), y = rnd(0, c);
        for (auto& [x, y] : b) x = rnd(0, c), y = rnd(0, c);
        bool ok  =0;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                ok |= (a[i] == b[j]);
            }
        }
        if (ok) continue;
        auto ans = brute(n, a, b);
        auto my = solve(n, a, b);
        auto print = [&] (vector<int> x) {
            if (x.empty()) cout << "Empty" << endl;
            else {
                for (auto y : x) cout << y + 1 << ' ';
                cout << endl;
            }
        };
        if (my.empty() != ans.empty()) {
            cout << n << endl;
            for (auto [x, y] : a) cout << x << ' ' << y << endl;
            cout << endl;
            for (auto [x, y] : b) cout << x << ' ' << y << endl;
            cout << "Sus answer on test " << t << endl;
            cout << "Your output: "; print(my);
            cout << "Answer: "; print(ans);
            exit(0);
        }
        cout << "Accepted on test " << t++ << endl;
    }
#endif
}
