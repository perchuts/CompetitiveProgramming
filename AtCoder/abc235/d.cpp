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

void solve(){
    int a, n; cin >> a >> n;
    int lim = 1000000;
    vector<int> dist(lim, -1);
    dist[1] = 0;
    queue<int> q;
    q.push(1);
    while (!q.empty()) {
        int x = q.front(); q.pop();
        int d = dist[x];
        string s = to_string(x);
        if (s.back() != '0') {
            string s2; s2 += s.back(); s2 += s;
            s2.pop_back();
            int k = stoi(s2);
            if (x < lim and dist[k] == -1) dist[k] = 1 + d, q.push(k);
        }
        if (x * a < lim and dist[x*a] == -1) dist[x*a] = 1 + d, q.push(x*a);
    }
    cout << dist[n] << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
