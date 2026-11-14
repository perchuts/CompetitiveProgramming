#include <bits/stdc++.h>
#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define int ll
#define pb push_back
#define endl '\n'

using namespace std;

using ll = long long;

int32_t main() {_
    int n; cin >> n;
    map<string, int> t;
    int ok = 1;
    while (n--) {
        string a, b; cin >> a >> b;
        if (a == "pickup") ok &= (t[b] == 0), t[b] = 1;
        else ok &= (t[b] == 1), t[b] = 2;
    }
    for (auto [x, y] : t) ok &= (y == 2);
    cout << (ok ? "yes" : "no") << endl;
}
