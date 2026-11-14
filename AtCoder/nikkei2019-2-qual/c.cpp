#include <bits/stdc++.h>
#define endl '\n'
#define pb push_back
#define int ll
#define _ ios_base::sync_with_stdio(0);cin.tie(0);

using namespace std;

using ll = long long;

int32_t main() {_
    int n; cin >> n;
    vector<int> a(n), b(n), ord_b(n);
    for (auto& x : a) cin >> x;
    for (auto& x : b) cin >> x;
    auto a2 = a; auto b2 = b; sort(begin(a2), end(a2)); sort(begin(b2), end(b2));
    for (int i = 0; i < n; ++i) {
        if (a2[i] > b2[i]) {
            cout << "No" << endl;
            return 0;
        }
    }
    for (int i = 0; i < n-1; ++i) {
        if (a2[i+1] <= b2[i]) {
            cout << "Yes" << endl;
            return 0;
        }
    }
    vector<int> p(n);
    iota(begin(p), end(p), 0);
    sort(begin(p), end(p), [&] (int x, int y) { return a[x] < a[y]; });
    iota(begin(ord_b), end(ord_b), 0);
    sort(begin(ord_b), end(ord_b), [&] (int x, int y) { return b[x] < b[y]; });
    vector<int> p2(n);
    for (int i = 0; i < n; ++i) p2[p[i]] = ord_b[i];
    p = p2;
    int vis = 1, cur = p[0];
    while (cur) vis++, cur = p[cur];
    cout << (vis == n ? "No" : "Yes") << endl;
}

