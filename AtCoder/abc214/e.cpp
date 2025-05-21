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

void solve(){
    int n; cin >> n;
    vector<int> l(n), r(n);
    for (int i = 0; i < n; ++i) cin >> l[i] >> r[i];
    vector<int> ord(n); iota(all(ord), 0);
    sort(all(ord), [&] (int x, int y) {
        return l[x] < l[y];
    });
    priority_queue<int, vector<int>, greater<>> pq;
    int i = 0, fr = l[ord[0]];
    while (i != n or !pq.empty()) {
        while (i != n and l[ord[i]] == fr) pq.push(r[ord[i++]]);
        if (pq.empty()) fr = l[ord[i]];
        else {
            int k = pq.top();
            pq.pop();
            if (k < fr) {
                cout << "No" << endl;
                return;
            }
            fr++;
        }
    }
    cout << "Yes" << endl;
}

int32_t main(){_
    int t = 1; cin >> t;
    while(t--) solve();
}
