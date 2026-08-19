#include <bits/stdc++.h>

using namespace std;

using ll = long long;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, k; cin >> n >> k;
    vector<vector<int>> intr(k+1);
    for (int i = 0; i < n; ++i) { int l, r; cin >> l >> r; intr[r-l].push_back(l); }
    ll ans = 0, cur = 0;
    vector<int> cb(2*k), mnr(2*k+2, k+9);
    for (int i = k; i; --i) {
        for (auto l : intr[i]) {
            int r = l + i;
            mnr[l+r] = min(mnr[l+r], r);
            auto calc = [&] (int pos) {
                cur -= cb[pos];
                int z = min(mnr[pos]+1, max(mnr[pos-2]+2, mnr[pos+2]));
                cb[pos] = max(0, min(pos-z+1, k-z+1));
                cur += cb[pos];
            };
            calc(l+r);
            if (l+r > 2) calc(l+r-2);
            if (l+r < 2*k-2) calc(l+r+2);
        }
        ans += cur;
    }
    ll w = ll((k+1)) * k / 2;
    ll g = gcd(w, ans);
    cout << ans / g << " " << w / g << endl;
}
