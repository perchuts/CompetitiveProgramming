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

void solve() {
    int n, k, x; cin >> n >> k >> x;
    vector<int> a(n);
    for (auto& x : a) cin >> x;
    sort(all(a));
    reverse(all(a));
    priority_queue<pair<int, vector<int>>> pq;
    vector<int> sexo(n);
    sexo[0] = k;
    set<vector<int>> s;
    s.insert(sexo);
    pq.push({k*a[0], sexo});
    for (int turn = 0; turn < x; ++turn) {
        auto [cost, v] = pq.top();
        pq.pop();
        cout << cost << endl;
        for (int i = 0; i < n-1; ++i) {
            if (!v[i]) continue;
            v[i]--;
            v[i+1]++;
            if (s.find(v) == end(s)) {
                s.insert(v);
                pq.push({cost+a[i+1]-a[i], v});
            }
            v[i]++;
            v[i+1]--;
        }
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
