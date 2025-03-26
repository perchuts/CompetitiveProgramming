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
const int mod2 = 998244353;
const int mod3 = 998244853;
const int maxn = 3e5+100;

template<typename X, typename Y> bool ckmin(X& x, const Y& y) { return (y < x) ? (x=y,1):0; }
template<typename X, typename Y> bool ckmax(X& x, const Y& y) { return (x < y) ? (x=y,1):0; }

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int rnd(int l, int r) {
    uniform_int_distribution<int> uid(l, r);
    return uid(rng);
}

int freq[4*maxn];

int solve(int n, vector<int> a, vector<int> b){
    sort(all(a)), sort(all(b));
    for (int i = 0; i < n; ++i) freq[b[i]]++;
    if (a == b) return (119<<23)+1;
    int sb = 0, sa = 0;
    for (int i = 0; i < n; ++i) sb += b[i], sa += a[i];
    if (sb >= sa) return -1;
    int x = sa - sb;
    for (int i = 1; i * i <= x; ++i) {
        if (x % i) continue;
        auto check = [&] (int k) {
            int i = 0;
            for (; i < n; ++i) {
                int m = a[i] % k;
                if (freq[m] == 0) break;
                freq[m]--;
            }
            bool nice = (i == n);
            --i;
            for (; i >= 0; --i) {
                int m = a[i] % k;
                freq[m]++;
            }
            return nice;
        };
        if (check(i)) return i;
        if (check(x/i)) return x/i;
    }
    return -1;   
}

int brute(int n, vector<int> a, vector<int> b) { 
    vector<int> ans = {-1};
    sort(all(a)), sort(all(b));
    for (int i = 1; i <= a.back()+1; ++i) {
        vector<int> a2(n);
        for (int j = 0; j < n; ++j) a2[j] = a[j] % i;
        sort(all(a2));
        if (a2 == b) ans.pb(i);
    }
    return ans.back();
}

int32_t main(){_
    int t = 1; cin >> t;
    while(t--) {
        int n; cin >> n;
        vector<int> a(n), b(n);
        for (auto& x : a) cin >> x;
        for (auto& x : b) cin >> x;
        cout << solve(n, a, b) << endl;
        for (int i = 0; i < n; ++i) freq[b[i]]--;
    }
}
