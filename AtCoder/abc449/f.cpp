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
#define int64 long long
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
#define FOR(i, a, b) for (int i = a; i <= b; i++)
#define maxN 450000

int rnd(int l, int r) {
    uniform_int_distribution<int> uid(l, r);
    return uid(rng);
}
struct Edge {
    bool open;
    int x, yMin, yMax;
    Edge(int x, int y1, int y2, bool op) {
        this->x = x;
        yMin = y1, yMax = y2;
        open = op;
    }
    bool operator < (const Edge &e) const {
        return (x < e.x);
    }
};
int n, m, h[maxN << 1];
int sum[maxN << 5], counter[maxN << 5];
vector<Edge> edges;

void update(int p, int l, int r, int yMin, int yMax, bool open) {
    if (h[r] < yMin || yMax < h[l]) return;
    int c = p << 1, mid = (l + r) >> 1;
    if (yMin <= h[l] && h[r] <= yMax) {
        counter[p] += open ? 1 : -1;
        if (counter[p]) sum[p] = h[r] - h[l];
        else sum[p] = sum[c] + sum[c + 1];
        return;
    }
    if (l + 1 >= r) return;
    update(c, l, mid, yMin, yMax, open);
    update(c + 1, mid, r, yMin, yMax, open);
    if (counter[p]) sum[p] = h[r] - h[l];
    else sum[p] = sum[c] + sum[c + 1];
}

int64 go() {
    // process height
    sort(h + 1, h + m + 1);
    int k = 1;
    FOR (i, 2, m) if (h[i] != h[k])
        h[++k] = h[i];
    m = k;
    // init tree
    for (int i = 0, lm = maxN << 4; i < lm; i++)
        sum[i] = 0, counter[i] = 0;
    // solve
    int64 area = 0LL;
    sort(all(edges));
    update(1, 1, m, edges[0].yMin, edges[0].yMax, edges[0].open);
    for (int i = 1; i < edges.size(); i++) {
        area += sum[1] * (int64)(edges[i].x - edges[i - 1].x);
        update(1, 1, m, edges[i].yMin, edges[i].yMax, edges[i].open);
    }
    return area;
}

void solve() {
    int N, M, n, mz, k; cin >> N >> M >> n >> mz >> k;
    vector<ii> pts(k);
    vector<int> cc;
    for (auto& x : pts) cin >> x.first >> x.second, cc.pb(x.first), cc.pb(x.second);
    //sort(all(cc)), cc.erase(unique(all(cc)), end(cc));
    //vector<ii> cmp;
    //for (auto& [x, y] : pts) cmp.pb({lower_bound(all(cc), x) - begin(cc), lower_bound(all(cc), y) - begin(cc)});
    int x1 = 1, x2 = N - n + 1, y1 = 1, y2 = M - mz + 1;
    using rect = pair<ii, ii>;
    vector<rect> bichos;
    auto inter = [&] (int a1, int b1, int c1, int d1, int a2, int b2, int c2, int d2) {
        rect ans;
        int lx = max(a1, a2), rx = min(c1, c2);
        int ly = max(b1, b2), ry = min(d1, d2);
        if (lx > rx or ly > ry) {
            ans.first.first = -1;
            return ans;
        }
        ans = {{lx, ly}, {rx+1, ry+1}};
        return ans;
    };
    //bichos = {{{1, 1}, {2, 5}}};
    m = 0;
    for (auto [x, y] : pts) {
        int a = x - n + 1, b = y - mz + 1, c = x, d = y;
        //cout << "eu: " << a << " " << b << " " << c << " " << d << endl;
        auto rt = inter(a, b, c, d, x1, y1, x2, y2);
        auto [x1, y1] = rt.first;
        auto [x2, y2] = rt.second;
        if (x1 != -1) {
            edges.pb(Edge(x1, y1, y2, true));
            edges.pb(Edge(x2, y1, y2, false));
            h[++m] = y1;
            h[++m] = y2;
        }
        //cout << "inter: ";
    }
    if (m == 0) {
        cout << x2*y2 << endl;
    } else {
        int bloq = go();
        cout << x2*y2 - bloq << endl; 
    }
}

int32_t main() {_
#ifndef gato
    int t = 1; //cin >> t;
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
