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

void solve(){
    int n; cin >> n;
    int N = 27*27*27;
    vector<int> vals(N);
    auto get_hash = [] (string s) {
        reverse(all(s));
        int h = 0, pot = 1;
        for (auto x : s) {
            h += (x - 'a' + 1) * pot;
            pot *= 27;
        }
        return h;
    };
    auto rev_hash = [] (int x) {
        string s;
        while (x) s += char('a' + (x % 27) - 1), x /= 27;
        reverse(all(s));
        return s;
    };
    for (int i = 0; i < n; ++i) {
        string t; cin >> t;
        reverse(all(t));
        cin >> vals[get_hash(t)];
    }
    vector<int> d(N, 1e18);
    d[0] = 0;
    //vector<vector<ii>> g(N);
    vector<iii> edg;
    for (int i = 0; i < N; ++i) {
        string eu = rev_hash(i);
        for (char c = 'a'; c <= 'z'; ++c) {
            string temp = eu + c;
            if (sz(temp) > 3) assert(sz(temp) == 4), temp = temp.substr(1, 3);
            int h = get_hash(temp);
            int ss = 0;
            for (int j = 1; j <= sz(temp); ++j) ss -= vals[get_hash(temp.substr(sz(temp)-j, j))];
            edg.emplace_back(i, h, ss);
        }
    }
    auto bellman_ford = [&] () {
        int lim = 2000;
        for (int i = 0; i <= lim; i++) {
            for (auto [u, v, w] : edg) {
                if (d[v] > d[u] + w) {
                    if (i == lim) return 1;
                    d[v] = d[u] + w;
                }
            }
        }
        return 0;
    };
    if (bellman_ford()) {
        cout << "Infinity" << endl;
        exit(0);
    }
    int ans = -1e18;
    for (int i = 1; i < N; ++i) ckmax(ans, -d[i]);
    cout << ans << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
