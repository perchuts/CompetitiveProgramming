#include <bits/stdc++.h>
//#define gato
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
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

double solve(int n, vector<tuple<int, int, char>> v){
    vector<int> id(256);
    vector<vector<ii>> bb(4, vector<ii>(4, make_pair(0, -1)));
    for (int i = 0; i < 4; ++i) for (int j = 0; j < 4; ++j) bb[i][j].first = (j < 2 ? -1e18 : 1e18);
    id['U'] = 0, id['R'] = 1, id['D'] = 2, id['L'] = 3;
    for (int i = 0; i < n; ++i) {
        auto [x, y, c] = v[i];
        int k = id[c];
        ckmax(bb[k][0], make_pair(y, i));
        ckmax(bb[k][1], make_pair(x, i));
        ckmin(bb[k][2], make_pair(y, i));
        ckmin(bb[k][3], make_pair(x, i));
    }
    vector<ii> dir(256);
    dir['U'] = {0, 1};
    dir['D'] = {0, -1};
    dir['R'] = {1, 0};
    dir['L'] = {-1, 0};
    vector<int> intr = {0};
    auto move = [&] (int i, double s) {
        auto [x, y, c] = v[i];
        double xx = s * dir[c].first + x, yy = s * dir[c].second + y;
        return make_pair(xx, yy);
    };
    for (int i = 0; i < 4; ++i) for (int j = 0; j < 4; ++j) for (int k = 0; k < 4; ++k) for (int l = 0; l < 4; ++l) {
        int id1 = bb[i][j].second;
        int id2 = bb[k][l].second;
        if (min(id1, id2) == -1 or i == k) continue;
        int lx = 0, rx = 1e9, h;
        auto check = [&] (double mid) {
            auto [xx1, yy1] = move(id1, mid);
            auto [xx2, yy2] = move(id2, mid);
            vector<int> who(4);
            who[0] = !(xx1 >= xx2);
            who[1] = !(xx1 <= xx2);
            who[2] = !(yy1 >= yy2);
            who[3] = !(yy2 <= yy2);
            return who;
        };
        auto z = check(0);
        if (check(rx) == z) continue;
        while (lx <= rx) {
            int md = lx + (rx-lx+1)/2;
            if (check(md) == z) lx = md+1;
            else rx = md-1, h = md;
        }
        for (int zz = 2*h-3; zz <= 2*h+3; ++zz) intr.pb(zz);
        lx = 0, rx = 1e9;
		z = check(rx);
        while (lx <= rx) {
            int md = lx + (rx-lx+1)/2;
            if (check(md) == z) rx = md-1;
            else lx = md+1, h = md;
        }
        for (int zz = 2*h-3; zz <= 2*h+3; ++zz) intr.pb(zz);
    }
    sort(all(intr));
    auto eval = [&] (double T) {
        vector<vector<pair<double, double>>> nbb(4, vector<pair<double, double>>(4, make_pair(-1, -1)));
        for (int i = 0; i < 4; ++i) for (int j = 0; j < 4; ++j) {
            if (bb[i][j].second != -1) {
                int k = bb[i][j].second;
                nbb[i][j] = move(k, T);
            }
        }
        int x1 = -1e18, x2 = 1e18, y1 = -1e18, y2 = 1e18;
        for (int i = 0; i < 4; ++i) for (int j = 0; j < 4; ++j) {
            if (bb[i][j].second != -1) {
                ckmax(x1, 2*nbb[i][j].first);
                ckmin(x2, 2*nbb[i][j].first);
                ckmax(y1, 2*nbb[i][j].second);
                ckmin(y2, 2*nbb[i][j].second);
            }
        }
        return (x1-x2)*(y1-y2);
    };
    int ans = 1e18;
	intr.erase(unique(all(intr)), end(intr));
    for (int i = 0; i < sz(intr); ++i) if (intr[i] >= 0) {
        ckmin(ans, eval(intr[i]/2.0));
    }
    return ans/4.0;
}
double maxC = 20;

double brute(int n, vector<tuple<int, int, char>> v) {
    double ans = 1e18;
    vector<ii> dir(256);
    dir['U'] = {0, 1};
    dir['D'] = {0, -1};
    dir['R'] = {1, 0};
    dir['L'] = {-1, 0};
    vector<double> intr = {0};
    auto move = [&] (int i, double s) {
        auto [x, y, c] = v[i];
        double xx = s * dir[c].first + x, yy = s * dir[c].second + y;
        return make_pair(xx, yy);
    };
    for (int t = 0; t <= 3*maxC; ++t){ 
        double x1 = -1e18, x2 = 1e18, y1 = -1e18, y2 = 1e18;
        for (int i = 0; i < n; ++i) {
            auto [x, y] = move(i, t);
            ckmax(x1, x);
            ckmin(x2, x);
            ckmax(y1, y);
            ckmin(y2, y);
        }
        if (ckmin(ans, (x1-x2)*(y1-y2))) {
#ifndef gato
            cout << t << endl;
#endif
        }
    }
    for (int t = 0; t <= 3*maxC; ++t){ 
        double x1 = -1e18, x2 = 1e18, y1 = -1e18, y2 = 1e18;
        for (int i = 0; i < n; ++i) {
            auto [x, y] = move(i, 0.5+t);
            ckmax(x1, x);
            ckmin(x2, x);
            ckmax(y1, y);
            ckmin(y2, y);
        }
        if (ckmin(ans, (x1-x2)*(y1-y2))) {
#ifndef gato
            cout << t + 0.5 << endl;
#endif
        }
    }
    return ans;
}
int32_t main(){_
#ifdef gato
    int t = 1;
    while (true) {
        int n = rnd(1, 30);
        vector<char> aaa = {'R', 'L', 'U', 'D'};
        vector<tuple<int, int, char>> v(n);
        for (auto& [x, y, z] : v) {
            z = aaa[rnd(0, 3)];
            x = rnd(-maxC, maxC);
            y = rnd(-maxC, maxC);
        }
        double my = solve(n, v);
        double ans = brute(n, v);
        if (my != ans) {
            cout << "Wrong answer on test " << t << endl;
            cout << n << endl;
            for (auto [x, y, z] : v) cout << x << ' ' << y << ' ' << z << endl;
            cout << "Your output: " << fixed << setprecision(10) << my << endl;
            cout << "Answer: " << fixed << setprecision(10) << ans << endl;
            exit(0);
        }
        cout << "Accepted on test " << t++ << endl;
    }
#else
    int n; cin >> n;
    vector<tuple<int, int, char>> v(n);
    for (auto& [x, y, z] : v) cin >> x >> y >> z;
    cout << fixed << setprecision(10) << solve(n, v) << endl;
#endif
}
