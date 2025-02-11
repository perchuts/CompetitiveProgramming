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
    int n; cin >> n;
    vector<vector<int>> cnt(n, vector<int>(10));
    vector<string> ss(n);
    for (int i = 0; i < n; ++i) {
        cin >> ss[i];
        for (auto c : ss[i]) {
            if (c == 'X') cnt[i][0]++;
            else cnt[i][c-'0']++;
        }
    }
    vector<int> p(n); iota(all(p), 0);
    sort(all(p), [&] (int a, int b) {
            int score1 = 0, score2 = 0;
            for (int i = 1; i <= 9; ++i) score1 += i * cnt[a][i] * cnt[b][0], score2 += i * cnt[b][i] * cnt[a][0];
            return score1 < score2;
    });
    int ans = 0, x = 0;
    for (auto i : p) {
        for (auto c : ss[i]) {
            if (c == 'X') x++;
            else ans += (c - '0') * x;
         }
    }
    cout << ans << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
