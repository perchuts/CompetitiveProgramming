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

int solve(int n, vector<array<int, 2>> v) {
    for (int i = 0; i < n; ++i) if (v[i][0] > v[i][1]) swap(v[i][0], v[i][1]);
    // plota os pontos no 2d. quero minimizar uma area ai.
    // f(x) = menor comprimento do outro se eu fixo que um <= x.
    // f eh obviamente monotona nao crescente.
    auto eval = [&] (vector<int> mark) {
        array<int, 2> a{inf, 0}, b = a;
        for (int i = 0; i < n; ++i) {
            ckmin(a[0], v[i][mark[i]]);
            ckmax(a[1], v[i][mark[i]]);
            ckmin(b[0], v[i][mark[i]^1]);
            ckmax(b[1], v[i][mark[i]^1]);
        }
        return (a[1]-a[0])*(b[1]-b[0]);
    };
    int mx = 0, mn = inf, p, q;
    for (int i = 0; i < n; ++i) {
        if (ckmax(mx, v[i][1])) p = i;
        if (ckmin(mn, v[i][0])) q = i;
    }
    if (mx == mn) { return 0; }
    int ans = eval(vector<int>(n, 0));
    if (p == q) {
        // ja garantidamente sei que um lado vai ter o maximo, o outro o minimo, guloso eh optimal
        return ans;
    }
    // agora vou tentar fazer tanto o mn quanto o mx serem de um cara. ent queremos minimizar a janela do outro random
    vector<int> mark(n, -1);
    mark[p] = 1, mark[q] = 0;
    int L = min(v[p][0], v[q][1]), R = max(v[p][0], v[q][1]);
    vector<int> ids;
	int nr = R, nl = L;
    for (int i = 0; i < n; ++i) {
        if (i == p or i == q) continue;
        if (L <= v[i][0] and v[i][0] <= R) mark[i] = 1;
        else if (L <= v[i][1] and v[i][1] <= R) mark[i] = 0;
        else if (v[i][1] < L) mark[i] = 0, ckmin(nl, v[i][1]);
        else if (R < v[i][0]) mark[i] = 1, ckmax(nr, v[i][0]);
        else ids.pb(i);
    }
	R = nr, L = nl;
    vector<int> nids;
    for (auto i : ids) {
        if (L <= v[i][0] and v[i][0] <= R) mark[i] = 1;
        else if (L <= v[i][1] and v[i][1] <= R) mark[i] = 0;
        else nids.pb(i);
    }
    swap(ids, nids);
    sort(all(ids), [&] (int x, int y) { return v[x][0] > v[y][0]; });
    if (ids.empty()) {
        return min(ans, eval(mark));
    }
    vector<int> suf(sz(ids)); suf.back() = v[ids.back()][1];
    for (int i = sz(ids)-2; i >= 0; --i) suf[i] = max(suf[i+1], v[ids[i]][1]);
    ckmin(ans, (v[p][1]-v[q][0])*(suf[0]-L));
    ckmin(ans, (v[p][1]-v[q][0])*(R-v[ids.back()][0]));
    for (int i = 0; i < sz(ids)-1; ++i) ckmin(ans, (v[p][1]-v[q][0])*(suf[i+1]-v[ids[i]][0]));
    return ans;
}


int brute(int n, vector<array<int, 2>> v) {
    auto eval = [&] (vector<int> mark) {
        array<int, 2> a{inf, 0}, b = a;
        for (int i = 0; i < n; ++i) {
            ckmin(a[0], v[i][mark[i]]);
            ckmax(a[1], v[i][mark[i]]);
            ckmin(b[0], v[i][mark[i]^1]);
            ckmax(b[1], v[i][mark[i]^1]);
        }
        return (a[1]-a[0])*(b[1]-b[0]);
    };
    int ans = 1e18;
    for (int i = 0; i < (1 << n); ++i) {
        vector<int> mark(n);
        for (int j = 0; j < n; ++j) mark[j] = (i >> j & 1);
        ckmin(ans, eval(mark));
    }
    return ans;
}

int32_t main() {_
#ifndef gato
    int n; cin >> n;
    vector<array<int, 2>> v(n);
    for (int i = 0; i < n; ++i) cin >> v[i][0] >> v[i][1];
    cout << solve(n, v) << endl;
#else
    int t = 1;
    while (true) {
        int n = rnd(2, 8);
        vector<array<int, 2>> a(n);
        for (int i = 0; i < n; ++i) a[i][0] = rnd(1, 7), a[i][1] = rnd(1, 7);
        auto my = solve(n, a);
        auto ans = brute(n, a);
        if (my != ans) {
            cout << "Wrong answer on test " << t << endl;
            cout << n << endl;
            for (int i = 0; i < n; ++i) cout << a[i][0] << " " << a[i][1] << endl;
            cout << "Solve: " << my << endl;
            cout << "Brute: " << ans << endl;
            exit(0);
        }
        cout << "Accepted on test " << t++ << endl;
    }
#endif
}
