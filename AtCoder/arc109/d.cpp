#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
#define endl '\n'
#define pb push_back
#define _ ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
//#define int ll

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

map<array<int, 6>, int> dist; void normalize(array<int, 6> &cx); bool eh_L(array<int, 6> cx);

void solve() {
    array<int, 6> cc;
    for (int i = 0; i < 6; ++i) cin >> cc[i];
    normalize(cc);
    // corner
    if (cc == array<int, 6>{1, 1, 0, 1, 1, 0}) {
        cout << 1 << endl;
        return;
    }
    if (cc == array<int, 6>{0, 0, 1, 0, 0, 1}) {
        cout << 0 << endl;
        return;
    }
    int mx = max(abs(cc[0]), abs(cc[1]));
    // +2 soh aq
    if (cc[0] == cc[1] and cc[0] <= 0 and cc[2] < cc[0] and cc[5] < cc[1]) {
        cout << mx*2+2 << endl;
        return;
    }
    // corner
    if (cc[0] == cc[1]) {
        if (cc[0] <= 0) {
            cout << 2*mx+1 << endl;
            return;
        }
        if (cc[0] < cc[2] and cc[1] < cc[5]) {
            cout << 2*mx+1 << endl;
            return;
        }
        cout << 2*mx << endl;
        return;
    }
    auto a = cc;
    // -1 soh aq
    if (a[0] > a[1] and abs(a[0]) > abs(a[1]) and a[2] < a[0]) {
        cout << 2*mx-1 << endl;
        return;
    }
    if (a[1] > a[0] and abs(a[1]) > abs(a[0]) and a[5] < a[1]) {
        cout << 2*mx-1 << endl;
        return;
    }
    if (a[0] < a[1] and a[2] < a[0] and abs(a[0]) >= abs(a[1])) {
        cout << 2*mx+1 << endl;
        return;
    }
    if (a[0] > a[1] and a[5] < a[1] and abs(a[1]) >= abs(a[0])) {
        cout << 2*mx+1 << endl;
        return;
    }
    cout << 2*mx << endl;
}

void normalize (array<int, 6> &cx) {
    // peca central fica no zero
    if (cx[0] != cx[2] and cx[1] != cx[3]) swap(cx[0], cx[4]), swap(cx[1], cx[5]);
    else if (cx[0] != cx[4] and cx[1] != cx[5]) swap(cx[0], cx[2]), swap(cx[1], cx[3]);
    if (cx[1] != cx[3]) swap(cx[2], cx[4]), swap(cx[3], cx[5]);
}

bool eh_L(array<int, 6> cx) { return (cx[1] == cx[3] and cx[0] == cx[4] and abs(cx[0]-cx[2]) == abs(cx[1]-cx[5]) and abs(cx[0]-cx[2]) == 1); }

int32_t main() {_
    // movimentos:
    // ......     ......     ......     ......     ......     ......     ......     ......
    // ......     ......     ......     ......     ......     ......     ......     ......
    // ..x...  >  ..xx..  ~  ..x...  ~  ......  ~  .xx...  ~  ...x..  ~  ......  ~  ..xx..
    // ..xx..  >  ...x..  ~  .xx...  ~  ..xx..  ~  ..x...  ~  ..xx..  ~  ..xx..  ~  ..x...
    // ......     ......     ......     ...x..     ......     ......     ..x...     ......
    // ......     ......     ......     ......     ......     ......     ......     ......
    //
    vector<iii> moves;
    moves.pb({0, 1, 1});
    moves.pb({1, -2, 0});
    moves.pb({1, -2, 1});
    moves.pb({1, 0, 1});
    moves.pb({2, 0, -2});
    moves.pb({2, 1, -2});
    moves.pb({2, 1, 0});
    array<int, 6> st = {0, 0, 1, 0, 0, 1};
    dist[st] = 0;
    queue<array<int, 6>> q; q.push(st);
    // eu sei que consigo em uns 2*dist centro passos
    while (!q.empty()) {
        auto a = q.front(); q.pop();
        if (max({abs(a[0]), abs(a[1]), abs(a[2]), abs(a[3]), abs(a[4]), abs(a[5])}) > 3) continue;
        assert(dist[a] <= 2*(abs(a[0])+abs(a[1])+1));
        int mx = max(abs(a[0]), abs(a[1]));
        assert(dist[a] <= 2*mx+2);
        // -1, 0, 1, 2
        assert(dist[a] >= 2*mx-1);
        if (dist[a] == 2*mx+1 and a[0] != a[1]) {
            assert(min(a[0], a[1]) < 0);
            if (a[0] < a[1]) assert(a[2] < a[0]), assert(abs(a[0]) >= abs(a[1]));
            else assert(a[5] < a[1]), assert(abs(a[1]) >= abs(a[0]));
            //printf("(%d, %d) - (%d, %d) - (%d, %d) -> %d\n", a[0], a[1], a[2], a[3], a[4], a[5], dist[a]);
        }
        if (a[0] < a[1] and a[2] < a[0] and abs(a[0]) >= abs(a[1])) assert(dist[a] == 2*mx+1);
        if (a[0] > a[1] and a[5] < a[1] and abs(a[1]) >= abs(a[0])) assert(dist[a] == 2*mx+1);
        int dd = dist[a];
        int dx = a[2]-a[0], dy = a[5]-a[1];
        for (auto [id, mx, my] : moves) {
            auto b = a;
            b[2*id] += dx*mx;
            b[1+2*id] += dy*my;
            normalize(b);
            if (!dist.count(b)) dist[b] = 1 + dd, q.push(b);
        }
    }
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
