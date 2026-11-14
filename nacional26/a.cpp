#include <bits/stdc++.h>
using namespace std;

#define fast_io cin.tie(0)->sync_with_stdio(0)
#define pb push_back
#define mp make_pair
typedef long long ll;

int32_t main() {
    fast_io;
    int n; cin >> n;
    vector<int> v;
    if (n % 4) v = {1, 2};
    else v = {1, 1};
    v.resize(n);
    for (int i = 2; i < n; ++i) v[i] = 3 - v[i-2];
    cout << 2 << " ";
    for (auto x : v) cout << x << " ";
    cout << endl;
    int q; cin >> q;
    while (q--) {
        int m; cin >> m;
        vector<int> c(m);
        for (auto& x : c) cin >> x;
        vector<int> dir;
        for (int l = 0, r = 0; l != m; l = r) {
            while (r != m and c[l] == c[r]) r++;
            if (l % 2 == r % 2) dir.push_back(+1);
            else dir.push_back(-1);
        }
        dir.pop_back();
        reverse(begin(dir), end(dir));
        if (!dir.empty()) dir.pop_back();
        reverse(begin(dir), end(dir));
        int l = 0, r = 0, z = 0, cur = 1;
        for (auto x : dir) {
            int prox;
            if (cur == 0) {
                prox = -x * z;
            } else {
                if (x == -1) prox = z; 
                else prox = 2*cur-z; 
            }
            l = min(l, cur);
            r = max(r, cur);
            z = cur, cur = prox;
        }
        l = min(l, cur);
        r = max(r, cur);
        auto trajeto = [&] (int start) {
            int pos = start;
            for (int i = 1; i < m; ++i) {
                int prox = -1;
                if (pos != 0 and v[pos-1] == c[i]) prox = pos-1;
                if (pos != n-1 and v[pos+1] == c[i]) prox = pos+1;
                if (prox == -1) return vector<int>();
                pos = prox;
            }
            pos = start;
            vector<int> ans = {pos};
            for (int i = 1; i < m; ++i) {
                int prox = -1;
                if (pos != 0 and v[pos-1] == c[i]) prox = pos-1;
                if (pos != n-1 and v[pos+1] == c[i]) prox = pos+1;
                pos = prox;
                ans.push_back(pos);
            }
            return ans;
        };
        vector<int> ans;
        int mn = 2 * abs(l);
        for (int i = mn-1; i < min(n, mn+4) and ans.empty(); ++i) {
            if (0 <= i and i < n) {
                if (v[i] != c[0]) continue;
                auto Z = trajeto(i);
                if (!Z.empty()) {
                    ans = Z;
                }
            }
        }
        int id = n-1 - 2 * abs(l);
        for (int i = id-3; i <= id+1 and ans.empty(); ++i) {
            if (0 <= i and i < n) {
                if (v[i] != c[0]) continue;
                auto Z = trajeto(i);
                if (!Z.empty()) {
                    ans = Z;
                }
            }
        }
        for (auto x : ans) cout << x+1 << " ";
        cout << endl;
    }
}
