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
    int n, k; cin >> n >> k;
    vector<int> v(n);
    for (auto& x : v) cin >> x;
    set<ii> ss;
    map<int, int> freq;
    for (int i = 0; i < k; ++i) freq[v[i]]++;
    for (auto [x, y] : freq) ss.insert({-y, x});
    cout << (begin(ss)->second) << ' ';
    for (int i = k; i < n; ++i) {
        ss.erase({-freq[v[i]], v[i]});
        freq[v[i]]++;
        ss.insert({-freq[v[i]], v[i]});
        ss.erase({-freq[v[i-k]], v[i-k]});
        freq[v[i-k]]--;
        ss.insert({-freq[v[i-k]], v[i-k]});
        cout << (begin(ss)->second) << ' ';
    }
    cout << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
