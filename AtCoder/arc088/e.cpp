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

void solve() {
    string s; cin >> s;
    int n = sz(s), freq = 0;
    vector<vector<int>> occ(26);
    for (int i = 0; i < n; ++i) {
        freq ^= (1 << (s[i]-'a'));
        occ[s[i]-'a'].pb(i);
    }
    if (__builtin_popcount(freq) > 1) {
        cout << -1 << endl;
        exit(0);
    }
    vector<int> val(n);
    for (int i = 0; i < 26; ++i) {
        for (int j = 0; j < sz(occ[i]); ++j) {
            if (j < sz(occ[i])/2) val[occ[i][j]] = 0;
            else if (2 * j >= sz(occ[i])) val[occ[i][j]] = 2;
            else val[occ[i][j]] = 1;
        }
    }
    vector<int> qtd(3), S, T;
    int ans = 0;
    for (int i = 0; i < n; ++i) {
        if (val[i] == 0) S.pb(s[i]-'a');
        if (val[i] == 2) T.pb(s[i]-'a');
        for (int j = val[i]+1; j < 3; ++j) ans += qtd[j];
        qtd[val[i]]++;
    }
    reverse(all(S));
    // min swaps in T to make S == T
    for (int i = 0; i < 26; ++i) occ[i].clear();
    for (int i = 0; i < sz(S); ++i) occ[S[i]].pb(i);
    for (int i = 0; i < 26; ++i) reverse(all(occ[i]));
    ord_set<int> ss;
    for (int i = 0; i < sz(T); ++i) {
        int eu = occ[T[i]].back();
        ans += i - ss.order_of_key(eu);
        ss.insert(eu);
        occ[T[i]].pop_back();
    }
    cout << ans << endl;
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
