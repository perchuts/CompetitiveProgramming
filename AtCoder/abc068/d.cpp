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
    auto go = [] (vector<int> v) {
        int n = sz(v);
        int steps = 0;
        while (true) {
            sort(all(v));
            if (v.back() < n) return steps;
            v.back() -= n;
            for (int i = 0; i < n-1; ++i) v[i]++;
            steps++;
        }
        return steps;
    };
    int k; cin >> k;
    int lim = 2e16;
    if (k <= lim) {
        if (k == 0) {
            cout << "2" << endl;
            cout << "1 1" << endl;
            exit(0);
        }
        if (k == 1) {
            cout << "2" << endl;
            cout << "2 0" << endl;
            exit(0);
        }
        if (k % 2) {
            vector<int> v = {1+(k-3)/2, 4+(k-3)/2};
            //cout << "A: " << go(v) << endl;
            cout << 2 << endl;
            for (auto x : v) cout << x << ' ';
            cout << endl;
            exit(0);
        }
        vector<int> v = {1+(k/2), 1+(k/2)};
        //cout << "A: " << go(v) << endl;
        cout << 2 << endl;
        for (auto x : v) cout << x << ' ';
        cout << endl;
        exit(0);
    }
    int n = 50, m = k % n;
    vector<int> v(n, n-1+(k/n)-m);
    for (int i = 0; i < m; ++i) v[i] += n+1;
    cout << n << endl;
    for (auto x : v) cout << x << ' ';
    cout << endl;

}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
