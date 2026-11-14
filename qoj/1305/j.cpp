#include <bits/stdc++.h>
using namespace std;
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <class T>
	using ord_set = tree<T, null_type, less<T>, rb_tree_tag,
	tree_order_statistics_node_update>;
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
// Suffix Array - O(n log n)
//
// kasai recebe o suffix array e calcula lcp[i],
// o lcp entre s[sa[i],...,n-1] e s[sa[i+1],..,n-1]
//
// Complexidades:
// suffix_array - O(n log(n))
// kasai - O(n)

vector<int> suffix_array(string s) {
	s += "$";
	int n = s.size(), N = max(n, 260LL);
	vector<int> sa(n), ra(n);
	for(int i = 0; i < n; i++) sa[i] = i, ra[i] = s[i];

	for(int k = 0; k < n; k ? k *= 2 : k++) {
		vector<int> nsa(sa), nra(n), cnt(N);

		for(int i = 0; i < n; i++) nsa[i] = (nsa[i]-k+n)%n, cnt[ra[i]]++;
		for(int i = 1; i < N; i++) cnt[i] += cnt[i-1];
		for(int i = n-1; i+1; i--) sa[--cnt[ra[nsa[i]]]] = nsa[i];

		for(int i = 1, r = 0; i < n; i++) nra[sa[i]] = r += ra[sa[i]] !=
			ra[sa[i-1]] or ra[(sa[i]+k)%n] != ra[(sa[i-1]+k)%n];
		ra = nra;
		if (ra[sa[n-1]] == n-1) break;
	}
	return vector<int>(sa.begin()+1, sa.end());
}

vector<int> kasai(string s, vector<int> sa) {
	int n = s.size(), k = 0;
	vector<int> ra(n), lcp(n);
	for (int i = 0; i < n; i++) ra[sa[i]] = i;

	for (int i = 0; i < n; i++, k -= !!k) {
		if (ra[i] == n-1) { k = 0; continue; }
		int j = sa[ra[i]+1];
		while (i+k < n and j+k < n and s[i+k] == s[j+k]) k++;
		lcp[ra[i]] = k;
	}
	return lcp;
}
void solve() {
    string s; cin >> s;
    int q; cin >> q;
    auto sa = suffix_array(s);
    auto lcp = kasai(s, sa);
    int n = sz(s);
    vector<int> qtd = {n - sa[0]}, pos_sa(n);
    for (int i = 0; i < n; ++i) pos_sa[sa[i]] = i;
    vector<vector<int>> entra(n+2), sai(n+2);
    entra[1].pb(sa[0]), sai[n-sa[0]+1].pb(sa[0]);
    for (int i = 1; i < n; ++i) {
        qtd.pb(n - sa[i] - lcp[i-1]);
        entra[lcp[i-1]+1].pb(sa[i]);
        sai[n-sa[i]+1].pb(sa[i]);
    }
    //cout << "sa: ";
    //for (auto x : sa) cout << x << " ";
    //cout << endl;
    //cout << "lcp: ";
    //for (auto x : lcp) cout << x << " ";
    //cout << endl;
    //cout << "ps: ";
    //for (int i = 1; i <= n; ++i) cout << ps[i] << " ";
    //cout << endl;
    //cout << s << endl;
    vector<int> qu(q), ord(q);
    vector<ii> ans(q, {-2, -2});
    for (auto& x : qu) cin >> x, --x;
    iota(all(ord), 0);
    sort(all(ord), [&] (int x, int y) { return qu[x] < qu[y]; });
    ord_set<ii> alive;
    int t = 1, cs = 0;
    vector<vector<iii>> qry(n+1);
    for (int i = 1; i < n; ++i) qry[lcp[i-1]].pb({0, sa[i], sa[i-1]});
    for (auto idx : ord) {
        int pos = qu[idx];
        while (t <= n and cs <= pos) {
            for (auto i : entra[t]) alive.insert({pos_sa[i], i});
            for (auto i : sai[t]) alive.erase({pos_sa[i], i});
            cs += sz(alive);
            t++;
        }
        if (cs <= pos) break;
        auto it = alive.find_by_order(pos - (cs - sz(alive)));
        int l = it->second;
        qry[t-1].pb({1, l, idx});
    }
    vector<int> par(n), lvl(n), leader(n);
    iota(all(par), 0);
    leader = par;
    auto findp = [&] (auto&& self, int u) -> int {
        return par[u] = (par[u] == u ? u : self(self, par[u]));
    };
    auto merge = [&] (int u, int v) {
        u = findp(findp, u), v = findp(findp, v);
        assert(u != v);
        if (lvl[u] < lvl[v]) swap(u, v);
        par[v] = u;
        ckmin(leader[u], leader[v]);
        if (lvl[u] == lvl[v]) lvl[u]++;
    };
    for (int i = n; i; --i) {
        sort(all(qry[i]));
        for (auto [tipo, a, b] : qry[i]) {
            if (tipo) {
                ans[b].first = leader[findp(findp, a)];
                ans[b].second = ans[b].first + i - 1;
            } else merge(a, b);
        }
    }
    for (auto [l, r] : ans) cout << l+1 << " " << r+1 << endl;

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

