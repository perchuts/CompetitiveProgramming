#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
#define endl '\n'
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

vector<vector<int>> pre;

pair<int, vector<int>> brute(int n) {
    auto test = [&] (vector<int> v) {
        vector<int> qtd(3);
        qtd[0] = 1;
        int P = 0, ans = 0;
        for (auto x : v) {
            P += x;
            P = (P + 3) % 3;
            ans += qtd[P];
            qtd[P]++;
        }
        return ans;
    };
    vector<int> id(n), a(n);
    id[0] = 1;
    for (int i = 1; i < n; ++i) id[i] = -id[i-1];
    vector<int> opt = a;
    int ans = test(opt);
    for (int i = 0; i < n; ++i) {
        a[i] = id[i];
        if (ckmin(ans, test(a))) opt = a;
        a[i] = 0;
    }
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            a[i] = id[i];
            a[j] = id[j];
            if (ckmin(ans, test(a))) opt = a;
            a[i] = a[j] = 0;
        }
    }
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            for (int k = j + 1; k < n; ++k) {
            a[i] = id[i];
            a[j] = id[j];
            a[k] = id[k];
            if (ckmin(ans, test(a))) opt = a;
            a[i] = a[j] = a[k] = 0;
            }
        }
    }
    for (auto& x : opt) x = abs(x);
    return {ans, opt};
}

pair<int, vector<int>> solve(int n) {
    auto test = [&] (vector<int> v) {
        vector<int> qtd(3);
        qtd[0] = 1;
        int P = 0, ans = 0;
        for (auto x : v) {
            P += x;
            P = (P + 3) % 3;
            ans += qtd[P];
            qtd[P]++;
        }
        return ans;
    };
    vector<int> opt(n); opt[0] = 1;
    int ans = test(opt);
    vector<int> id(n), a(n);
    id[0] = 1;
    for (int i = 1; i < n; ++i) id[i] = -id[i-1];
    {
        int d = (n-2)/3;
        for (int k = 0; k <= 3; ++k) {
            for (int w = 0; w <= 3; ++w) {
                a[k+d] = id[k+d];
                a[k+d+1+d+w] = id[k+d+1+d+w];
                if (ckmin(ans, test(a))) opt = a;
                a[k+d] = a[k+d+1+d+w] = 0;
            }
        }
    }
    {
        int d = (n-2)/2;
        a[0] = 1;
        for (int k = 0; k <= 3; ++k) {
            a[k+d] = id[k+d];
            if (ckmin(ans, test(a))) opt = a;
            a[k+d] = 0;
        }
        a[0] = 0;
    }
    {
        int d = (n-3)/4;
        for (int k = 0; k <= 3; ++k) {
            for (int w = 0; w <= 3; ++w) {
                for (int z = 0; z <= 3; ++z) {
                    a[k+d] = id[k+d];
                    a[k+d+1+d+w] = id[k+d+1+d+w];
                    a[k+d+1+d+w+1+d+z] = id[k+d+1+d+w+1+d+z];
                    if (ckmin(ans, test(a))) opt = a;
                    a[k+d] = a[k+d+1+d+w] = a[k+d+1+d+w+1+d+z] = 0;
                }
            }
        }
    }
    {
        int d = (n-3)/3;
        a[0] = 1;
        for (int k = 0; k <= 3; ++k) {
            for (int w = 0; w <= 3; ++w) {
                a[k+d] = id[k+d];
                a[k+d+1+d+w] = id[k+d+1+d+w];
                if (ckmin(ans, test(a))) opt = a;
                a[k+d] = a[k+d+1+d+w] = 0;
            }
        }
        a[0] = 0;
    }
    return {ans, opt};
}

int32_t main() {_
#ifndef gato
    int t = 1; cin >> t;
    pre.resize(51);
    for (int i = 0; i < 50; ++i) {
        auto [a, b] = brute(i+1);
        pre[i+1] = b;
    }
    while(t--) {
        int n; cin >> n;
        if (n <= 50) {
            for (auto x : pre[n]) cout << x;
            cout << endl;
            continue;
        }
        auto [cost, v] = solve(n);
        for (auto x : v) cout << abs(x);
        cout << endl;
    }
#else
    int t = 1;
    for (int n = 51; n <= 150; ++n) {
        auto [my, a] = solve(n);
        auto [cost, ans] = brute(n);
        if (my != cost) {
            cout << "n = " << n << endl;
            cout << "my = " << my << endl;
            for (auto x : a) cout << abs(x);
            cout << endl;
            cout << "cost = " << cost << endl;
            for (auto x : ans) cout << abs(x);
            cout << endl;
            exit(0);
        }
        cout << "Accepted on test " << n-30 << endl;
    }
#endif
}
