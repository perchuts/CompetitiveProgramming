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
// SegTree
//
// Recursiva com Lazy Propagation
// Query: soma do range [a, b]
// Update: soma x em cada elemento do range [a, b]
// Pode usar a seguinte funcao para indexar os nohs:
// f(l, r) = (l+r)|(l!=r), usando 2N de memoria
//
// Complexidades:
// build - O(n)
// query - O(log(n))
// update - O(log(n))

const int MAX = 4e6;

void solve() {
    int n, m; cin >> n >> m;
    vector<int> a(n);
    for (auto& x : a) cin >> x;
    sort(all(a));
    unordered_map<int, int> vis;
    vector<int> bichos;
    auto exp = [&] (auto&& self, int x) -> void {
        if (vis[x] or x == 1) return;
        vis[x] = 1;
        bichos.pb(x);
        self(self, x/2);
        self(self, (x+1)/2);
    };
    for (auto x : a) exp(exp, x);
    sort(all(bichos));
    int N = sz(bichos);
    struct node {
        int cnt = 0, ss = 0;
    } nulo, fake;
    fake.cnt = -1;
    vector<node> seg(4*N);
    const int INF = 3*(n+m) + 1e10;
    auto add = [&] (int& x, int y) {
        x += y;
    };
    auto upd = [&] (auto&& self, int i, int l, int r, int x, int c, int s) -> void {
        if (l == r) {
            add(seg[i].cnt, c);
            add(seg[i].ss, s);
            return;
        }
        int md = (l+r)/2;
        if (x <= md) self(self, 2*i, l, md, x, c, s);
        else self(self, 2*i+1, md+1, r, x, c, s);
        seg[i] = seg[2*i];
        add(seg[i].ss, seg[2*i+1].ss);
        add(seg[i].cnt, seg[2*i+1].cnt);
    };
    int val;
    auto query = [&] (auto&& self, int i, int l, int r, int k) -> int { 
        // encontre a soma de ss dos k menores nodes
        if (seg[i].cnt < k) return -1LL;
        if (l == r) {
            assert(k);
            assert(k <= seg[i].cnt);
            val = bichos[l];
            return min(INF, k * bichos[l]);
        }
        int md = (l+r)/2;
        if (seg[2*i].cnt < k) return min(INF, seg[2*i].ss + self(self, 2*i+1, md+1, r, k-seg[2*i].cnt));
        return self(self, 2*i, l, md, k);
    };
    vector<int> tot(N);
    for (int i = 0; i < n; ++i) tot[lower_bound(all(bichos), a[i])-begin(bichos)]++;
    for (int i = 0; i < N; ++i) {
        if (tot[i]) upd(upd, 1, 0, N-1, i, tot[i], (bichos[i]-1) * tot[i]);
    }
    int need = (n+m+1)/2, ts = n;
    auto cut = [&] (int i, int k) {
        int x1 = lower_bound(all(bichos), bichos[i]/2) - begin(bichos);
        int x2 = lower_bound(all(bichos), (bichos[i]+1)/2) - begin(bichos);
        upd(upd, 1, 0, N-1, x1, tot[i], (bichos[x1]-1)*k);
        upd(upd, 1, 0, N-1, x2, tot[i], (bichos[x2]-1)*k);
        add(tot[x1], k);
        add(tot[x2], k);
        add(ts, k);
    };
    int ans = 1;
    for (auto x : a) cout << x << " ";
    cout << endl;
    for (int i = N-1; ~i; --i) {
        if (bichos[i] == 1) break;
        if (!tot[i]) continue;
        
        if (ts + tot[i] >= need) {
            cut(i, tot[i]);
            int k = query(query, 1, 0, N-1, ts-need); 
            if (k + ts >= n+m) {
                cout << "can acheive it at " << bichos[i] << endl;
                cut(i, -tot[i]);
                int l = 0, r = tot[i];
                while (l <= r) {
                    int md = l + (r-l+1)/2;
                    cut(i, md);
                    k = query(query, 1, 0, N-1, ts-need);
                    if (ts >= need and k + ts >= n+m) {
                        query(query, 1, 0, N-1, ts-need+1);
                        ckmax(ans, val);
                        r = md-1;
                    } else l = md+1;
                    cut(i, -md);
                }
                break;
            } else cut(i, -tot[i]);
        }
        cut(i, tot[i]);
    }
    cout << ans << endl;
}

int32_t main() {_
#ifndef gato
    int t = 1; cin >> t;
    while(t--) solve();
#else
    int t = 1;
    while (true) {
        int my = solve(), ans = brute();
        if (my != ans) {
            cout << "Wrong answer on test " << t << endl;
            cout << "Solve: " << my << endl;
            cout << "Brute: " << ans << endl;
            exit(0);
        }
        cout << "Accepted on test " << t++ << endl;
    }
#endif
}
