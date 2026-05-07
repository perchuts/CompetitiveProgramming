#include <bits/stdc++.h>
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
// Suffix Array - O(n log n)
//
// kasai recebe o suffix array e calcula lcp[i],
// o lcp entre s[sa[i],...,n-1] e s[sa[i+1],..,n-1]
//
// Complexidades:
// suffix_array - O(n log(n))
// kasai - O(n)

vector<int> suffix_array(vector<int> s) {
	s.pb(0);
	int n = s.size(), N = max(n, 260);
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

vector<int> kasai(vector<int> s, vector<int> sa) {
	int n = s.size(), k = 0;
	vector<int> ra(n), lcp(n);
	for (int i = 0; i < n; i++) {
        ra[sa[i]] = i;
    }

	for (int i = 0; i < n; i++, k -= !!k) {
		if (ra[i] == n-1) { k = 0; continue; }
		int j = sa[ra[i]+1];
		while (i+k < n and j+k < n and s[i+k] == s[j+k]) k++;
		lcp[ra[i]] = k;
	}
	return lcp;
}

void solve() {
    int n, q; cin >> n >> q;
    vector<int> s;
    int shift = q + 1;
    for (int i = 0; i < n; ++i) {
        char c; cin >> c;
        s.pb(int(c)+shift);
    }
    vector<vector<int>> v(q);
    for (auto& x : v) {
        string t; cin >> t;
        x.resize(sz(t));
        for (int j = 0; j < sz(t); ++j) x[j] = int(t[j])+shift;
    }
    vector<int> ini(q+1), dono(n, q);
    vector<int> grandao = s;
    for (int i = 0; i < q; ++i) {
        grandao.pb(i+1);
        dono.pb(-1);
        ini[i] = sz(grandao);
        for (auto x : v[i]) grandao.pb(x), dono.pb(i);
    }
    int N = sz(grandao);
    auto sa = suffix_array(grandao);
    auto lcp = kasai(grandao, sa);
    auto onde = v;
    vector<int> onde_s(n);
    for (int i = 0; i < N; ++i) {
        if (dono[sa[i]] == -1) continue;
        if (dono[sa[i]] == q) onde_s[sa[i]] = i;
        else onde[dono[sa[i]]][sa[i]-ini[dono[sa[i]]]] = i;
    }
    vector<int> ans(q), tam(q+1);
    for (int i = 0; i < q; ++i) tam[i] = sz(v[i]);
    tam[q] = sz(s);
    // min lcp, biggest size seen so far, best answer from here
    vector<array<int, 3>> st;
    for (int i = 0; i < q; ++i) ans[i] = tam[i];
    for (int i = 0; i < N-1; ++i) {
         if (dono[sa[i]] == -1) continue;
        array<int, 3> eu;
        eu[0] = lcp[i];
        // tamanho desse sufixo
        eu[1] = (tam[dono[sa[i]]] - (sa[i]-ini[dono[sa[i]]]));
        //cout << "chegando dono " << dono[sa[i]] << " de tamanho " << eu[1] << endl;
        if (dono[sa[i]] != q) eu[1] = 0;
        eu[2] = -2*N;
        while (!st.empty() and st.back()[0] >= lcp[i]) {
            ckmax(eu[1], st.back()[1]);
            st.pop_back();
        }
        ckmax(eu[2], eu[1]-2*eu[0]);
        if (!st.empty()) ckmax(eu[2], st.back()[2]), ckmax(eu[1], st.back()[1]);
        st.pb({eu[0], eu[1], eu[2]});
        int prox = dono[sa[i+1]];
        if (prox != -1 and prox != q) {
            ckmax(ans[prox], st.back()[2] + (tam[prox] - (sa[i+1]-ini[prox])));
        }
    }
    st.clear();
    for (int i = N-2; ~i; --i) {
         if (dono[sa[i]] == -1) continue;
        array<int, 3> eu;
        eu[0] = lcp[i];
        // tamanho desse sufixo
        eu[1] = (tam[dono[sa[i+1]]] - (sa[i+1]-ini[dono[sa[i+1]]]));
        eu[2] = -2*N;
        while (!st.empty() and st.back()[0] >= lcp[i]) {
            ckmax(eu[1], st.back()[1]);
            st.pop_back();
        }
        ckmax(eu[2], eu[1]-2*eu[0]);
        if (!st.empty()) ckmax(eu[2], st.back()[2]), ckmax(eu[1], st.back()[1]);
        st.pb({eu[0], eu[1], eu[2]});
        int prox = dono[sa[i]];
        if (prox != -1 and prox != q) {
            ckmax(ans[prox], st.back()[2] + (tam[prox] - (sa[i]-ini[prox])));
        }
    }
    for (auto x : ans) cout << x << ' ';
    cout << endl;
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
