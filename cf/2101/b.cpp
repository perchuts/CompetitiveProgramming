#include <bits/stdc++.h>
//#define gato
using namespace std;
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <class T>
	using ord_set = tree<T, null_type, less<T>, rb_tree_tag,
	tree_order_statistics_node_update>;
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
//#define endl '\n'
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

void solve(vector<int> a, int n){
    vector<int> quem(n+1);
    for (int i = 0; i < n; ++i) quem[a[i]] = i;
    vector<vector<int>> sexo(2);
    for (int i = 0; i < n; ++i) sexo[i&1].pb(a[i]);
    sort(all(sexo[0])), sort(all(sexo[1]));
    reverse(all(sexo[0])), reverse(all(sexo[1]));
    vector<int> ans;
    for (int i = 0; i < n; ++i) ans.pb(sexo[i&1].back()), sexo[i&1].pop_back();
    int pp = 0;
    ord_set<ii> s;
    for (int i = n-1; ~i; --i) {
        pp += s.order_of_key({quem[ans[i]], inf});
        s.insert({quem[ans[i]], i});
    }
    if (pp&1) swap(ans[n-3], ans[n-1]);
    for (auto x : ans) cout << x << ' ';
    cout << endl;

}

int32_t main(){_
#ifndef gato
    int t = 1; cin >> t;
    while (t--) { 
        int n; cin >> n;
        vector<int> a(n);
        for (auto& x : a) cin >> x;
        solve(a, n);
    }
#else
int t = 0;
while (true) {
        t++;
        int n = rnd(4, 8);
        vector<int> p(n); iota(all(p), 1);
        shuffle(all(p), rng);
        cout << "Test " << t << endl;
        solve(p, n);
    }
#endif
}
