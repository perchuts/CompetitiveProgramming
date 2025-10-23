#include <bits/stdc++.h>

using namespace std;
#define pb push_back
#define int ll
#define endl '\n'
#define _ ios_base::sync_with_stdio(0);cin.tie(0);
//#define gato

using ll = long long;

vector<int> solve(int n, int q, vector<int> a, vector<pair<int, int>> qq) {
    struct node {
        int pref, suf, sum, opt;
        int pref_min, suf_min;
        int pref_max, suf_max;
        node(int x) {
            sum = x;
            pref = suf = opt = max(0LL, x);
            pref_max = suf_max = pref_min = suf_min = x;
        }
        node() {
        }
    };
    auto nulo = node(0);
    auto merge = [&] (node a, node b) {
        node c;
        c.sum = a.sum + b.sum;
        c.pref = max(a.pref, a.sum + b.pref);
        c.suf = max(b.suf, b.sum + a.suf);
        c.pref_min = min({a.pref_min, a.sum + b.pref_min});
        c.suf_min = min({b.suf_min, b.sum + a.suf_min});
        c.pref_max = max(a.pref_max, a.sum + b.pref_max);
        c.suf_max = max(b.suf_max, b.sum + a.suf_max);
        c.opt = max({a.opt, b.opt, a.suf+b.pref});
        return c;
    };
    vector<node> seg(4*n);
    auto build = [&] (auto&& self, int i, int l, int r) -> void {
        if (l == r) {
            seg[i] = node(a[l]);
            return;
        }
        int md = (l+r)/2;
        self(self, 2*i, l, md), self(self, 2*i+1, md+1, r);
        seg[i] = merge(seg[2*i], seg[2*i+1]);
    };
    auto query = [&] (auto&& self, int i, int l, int r, int x, int y) -> node {
        if (r < x or y < l or x > y) return nulo;
        if (x <= l and r <= y) return seg[i];
        int md = (l+r)/2;
        auto lx = self(self, 2*i, l, md, x, y);
        auto rx = self(self, 2*i+1, md+1, r, x, y);
        if (y <= md) return lx;
        if (md < x) return rx;
        return merge(lx, rx);
    };

    vector<int> pref = a;
    for (int i = 1; i < n; ++i) pref[i] += pref[i-1];

    auto walkL = [&] (auto&& self, int i, int l, int r, int x, int k) -> int {
        if (l == r) return (seg[i].pref_min <= -k ? l : -1);
        if (x <= l) {
            if (seg[i].pref_min <= k) {
                int md = (l+r) / 2;
                if (seg[2*i].pref_min <= -k) return self(self, 2*i, l, md, x, k);
                return self(self, 2*i+1, md+1, r, x, k+seg[2*i].sum);
            }
            return -1;
        }
        int md = (l+r)/2;
        if (md < x) return self(self, 2*i+1, md+1, r, x, k);

        auto ansL = self(self, 2*i, l, md, x, k);
        if (ansL != -1) return ansL;
        return self(self, 2*i+1, md+1, r, x, k+(pref[md] - pref[x-1]));
    };

    build(build, 1, 0, n-1);

    vector<int> ans;


    vector<vector<array<int, 3>>> bl(n, vector<array<int, 3>>(20));

    auto findNext = [&] (int i, int val) {
        array<int, 3> arr;
        int k = (i == n-1 ? -1 : walkL(walkL, 1, 0, n-1, i+1, val));
        if (k == -1) {
            arr[0] = i;
            arr[1] = val;
            arr[2] = 0;
            return arr;
        }
        arr[0] = k;
        int S = val + (pref[k] - pref[i]);
        assert(S <= 0);
        arr[1] = val + max(0LL, query(query, 1, 0, n-1, i+1, k).pref_max);
        arr[2] = -S + 1;
        return arr;
    };
    for (int j = 0; j < 20; ++j) {
        for (int i = 0; i < n; ++i) {
            if (j == 0) {
                // want to find first time i become negative 
                bl[i][j] = findNext(i, 1);
            } else {
                auto arr1 = bl[i][j-1];
                auto arr2 = bl[arr1[0]][j-1];
                bl[i][j][0] = arr2[0];
                bl[i][j][1] = max(arr1[1], arr2[1]);
                bl[i][j][2] = arr1[2] + arr2[2];
            }
        }
    }

    for (auto [l, r] : qq) {
        bool ok = true;
        auto eu = query(query, 1, 0, n-1, l, r);
        int mx = 0;
        if (l != 0) {
            auto esq = query(query, 1, 0, n-1, 0, l-1);
            if (esq.suf_max >= 0) {
                ok = false;
            }
            mx = max(mx, esq.opt);
        }
        if (r != n-1) {
            auto dir = query(query, 1, 0, n-1, r+1, n-1);
            if (dir.pref_max >= 0) {
                ok = false;
            }
            mx = max(mx, dir.opt);
        }
        if (ok == false) ans.push_back(-1);
        else {
            if (l == r) {
                ans.push_back(max(0LL, mx - a[l] + 1));
            } else {
                int cur, cost, mxp;
                if (a[l] <= 0) {
                    cur = l, cost = -a[l] + 1, mxp = 1;
                } else {
                    auto arr = findNext(l, a[l]);
                    if (arr[0] > r) cur = l, cost = 0, mxp = 1;
                    else cur = arr[0], cost = arr[2], mxp = arr[1];
                }
                if (cur == l and cost == 0) {
                    cost += max(0LL, query(query, 1, 0, n-1, l, r-1).pref_max - eu.sum + 1);
                } else {
                    for (int i = 19; ~i; --i) {
                        if (bl[cur][i][0] == cur) break;
                        if (bl[cur][i][0] <= r) {
                            cost += bl[cur][i][2];
                            mxp = max(mxp, bl[cur][i][1]);
                            cur = bl[cur][i][0];
                        }
                    }
                    mxp = max(mxp, query(query, 1, 0, n-1, cur+1, r-1).pref_max + 1);
                    cost += max(0LL, mxp - (pref[r] - pref[cur] + 1) + 1);
                }
                ans.pb(max(cost, mx - eu.sum + 1));
            }
        }
    }
    return ans;
}

mt19937 rng(time(0));

int rnd(int l, int r) {
    uniform_int_distribution<int> uid(l, r);
    return uid(rng);
}
vector<int> brute(int n, int q, vector<int> a, vector<pair<int, int>> qq) {
    vector<int> ans;
    auto get1 = [&] (int l, int r) {
        if (r < 0 or l > n) return 0LL;
        int cur = 0, mx = 0;
        for (int i = l; i <= r; ++i) {
            cur += a[i];
            cur = max(0LL, cur);
            mx = max(mx, cur);
        }
        return mx;
    };
    for (auto [l, r] : qq) {
        int fora = max(get1(0, l-1), get1(r+1, n-1));
        int sum = 0, custo = 0, cur = 0, mx = 0;
        for (int i = l; i <= r; ++i) {
            cur += a[i], sum += a[i];
            if (cur <= 0) custo += -cur + 1, cur = 1;
            if (i != r) mx = max(mx, cur);
        }
        if (l != 0) {
            int cur = 0, ok = true;
            for (int i = l-1; ~i; --i) {
                cur += a[i];
                if (cur >= 0) {
                    ok = false; break;
                }
            }
            if (ok == false) { ans.pb(-1); continue; }
        }
        if (r != n-1) {
            int cur = 0, ok = true;
            for (int i = r+1; i < n; ++i) {
                cur += a[i];
                if (cur >= 0) {
                    ok = false; break;
                }
            }
            if (ok == false) { ans.pb(-1); continue; }
        }
        custo += max(0LL, mx - cur + 1);
        ans.pb(max(custo, fora - sum + 1));
    }
    return ans;
}

int32_t main() {_ 
#ifndef gato
    int t; cin >> t;

    while (t--) {
        int n, q; cin >> n >> q;
        vector<int> a(n);
        for (auto& x : a) cin >> x;
        vector<pair<int, int>> qry(q);
        for (auto& [x, y] : qry) cin >> x >> y, --y, --x;
        auto ans = solve(n, q, a, qry);
        for (auto x : ans) cout << x << endl;
    }
#else
    int t = 1;
    while (true) {
        int n = rnd(1, 30), q = 1;
        vector<int> v(n);
        for (auto& x : v) x = rnd(-100, 100);
        vector<pair<int, int>> qq(q);
        for (auto& [l, r] : qq) l = rnd(0, n-1), r = rnd(l, n-1);
        auto my = solve(n, q, v, qq);
        auto ans = brute(n, q, v, qq);
        if (my != ans) {
            cout << "Wrong answer on test " << t << endl;
            cout << n << ' ' << q << endl;
            for (auto x : v) cout << x << ' ';
            cout << endl;
            for (auto [l, r] : qq) cout << l+1 << ' ' << r+1 << endl;
            cout << "Your output: ";
            for (auto x : my) cout << x << ' ';
            cout << endl;
            cout << "Answer: ";
            for (auto x : ans) cout << x << ' ';
            cout << endl;
            exit(0);
        }
        cout << "Accepted on test " << t++ << endl;
    }
#endif
}

