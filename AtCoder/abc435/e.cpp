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
// Range color
//
// update(l, r, c) colore o range [l, r] com a cor c,
// e retorna os ranges que foram coloridos {l, r, cor}
// query(i) returna a cor da posicao i
//
// Complexidades (para q operacoes):
// update - O(log(q)) amortizado
// query - O(log(q))

const int INF = 2e9;
template<typename T> struct color {
	set<tuple<int, int, T>> se;
    int ans = 0;
	vector<tuple<int, int, T>> update(int l, int r, T val) {
		auto it = se.upper_bound({r, INF, val});
		if (it != se.begin() and get<1>(*prev(it)) > r) {
			auto [L, R, V] = *--it;
            ans -= (R-L+1);
			se.erase(it);
			se.emplace(L, r, V), se.emplace(r+1, R, V);
            ans += (r-L+1);
            ans += (R-r-1+1);
		}
		it = se.lower_bound({l, -INF, val});
		if (it != se.begin() and get<1>(*prev(it)) >= l) {
			auto [L, R, V] = *--it;
            ans -= (R-L+1);
			se.erase(it);
            ans += (l-1-L+1);
            ans += (R-l+1);
			se.emplace(L, l-1, V), it = se.emplace(l, R, V).first;
		}
		vector<tuple<int, int, T>> ret;
		for (; it != se.end() and get<0>(*it) <= r; it = se.erase(it)) {
            auto [L, R, V] = *it;
            ans -= (R-L+1);
			ret.push_back(*it);
        }
		se.emplace(l, r, val);
        ans += (r-l+1);
		return ret;
	}
	T query(int i) {
		auto it = se.upper_bound({i, INF, T()});
		if (it == se.begin() or get<1>(*--it) < i) return -1; // nao tem
		return get<2>(*it);
	}
};
void solve() {
    int n, q; cin >> n >> q;
    color<int> sexo;
    while (q--) {
        int l, r; cin >> l >> r;
        sexo.update(l, r, 1);
        cout << n-sexo.ans << endl;
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
