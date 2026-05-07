#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
#define pb push_back
#define _ ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#define int ll
//#define gato

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

void solve(int n, vector<int> a) {
    vector<int> ord(n), win(n), mov(n); iota(all(ord), 0);
    sort(all(ord), [&] (int i, int j) { return a[i] < a[j]; });
    int choice = -1;
    for (int i = n-1; ~i; --i) {
        for (int j = i + 1; j < n; ++j) {
            if (a[ord[i]] < a[ord[j]] and !win[ord[j]]) win[ord[i]] = 1, mov[ord[i]] = ord[j];
        }
        if (win[ord[i]] == 0 and (a[ord[i]] & 1)) mov[ord[i]] = ord[i], win[ord[i]] = 1;
        if (win[ord[i]]) choice = ord[i];
    }
    cout << (choice == -1 ? "Bob" : "Alice") << endl;
    if (choice != -1) cout << choice+1 << " " << mov[choice]+1 << endl;
    while (true) {
        int x, y; cin >> x >> y;
        if (x == 0 and y == 0) break;
        --x, --y;
        cout << y + 1 << " " << (a[y] > a[x] ? mov[y] : x) + 1 << endl;
    }
}

int32_t main() {_
    int t = 1; cin >> t;
    while(t--) {
        int n; cin >> n;
        vector<int> a(n);
        for (auto& x : a) cin >> x;
        solve(n, a);
    }
}
