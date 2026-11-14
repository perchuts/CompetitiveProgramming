#include <bits/stdc++.h>
#define endl '\n'
#define pb push_back
#define int ll
#define _ ios_base::sync_with_stdio(0);cin.tie(0);

using namespace std;

using ll = long long;

int32_t main() {_
    int n, k; cin >> n >> k;
    vector<int> a(n);
    for (auto& x : a) cin >> x;
    vector<int> ps(n+1), vals;
    for (int i = 1; i <= n; ++i) ps[i] = ps[i-1] + a[i-1] - k, vals.pb(ps[i]);
    vals.pb(0);
    sort(begin(vals), end(vals));
    vals.erase(unique(begin(vals), end(vals)), end(vals));
    auto get = [&] (int x) {
        return lower_bound(begin(vals), end(vals), x) - begin(vals) + 1;
    };
    vector<int> bit(vals.size()+1);
    auto add = [&] (int x) {
        while (x <= vals.size()) bit[x]++, x += x & (-x);
    };
    auto query = [&] (int x) {
        int ans = 0;
        while (x) {
            ans += bit[x];
            x -= x & (-x);
        }
        return ans;
    };
    add(get(0));
    int ans = 0;
    for (int i = 1; i <= n; ++i) {
        ans += query(get(ps[i]));
        add(get(ps[i]));
    }
    cout << ans << endl;
}

