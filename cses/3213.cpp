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

void solve(){
    int A, B, x; cin >> A >> B >> x;
    vector<vector<int>> dist(A+1, vector<int>(B+1, inf)), tipo = dist;
    vector<vector<ii>> tr(A+1, vector<ii>(B+1, pair(-1, -1)));
    priority_queue<iii, vector<iii>, greater<>> pq;
    dist[0][0] = 0;
    vector<string> moves = {"FILL A", "FILL B", "EMPTY A", "EMPTY B", "MOVE B A", "MOVE A B"};
    pq.push({0, 0, 0});
    while (!pq.empty()) {
        auto [d, a, b] = pq.top(); pq.pop();
        if (dist[a][b] != d) continue;
        if (dist[A][b] > d+A-a) {
            dist[A][b] = d+A-a;
            tipo[A][b] = 0;
            tr[A][b] = {a, b};
            pq.push({d+A-a, A, b});
        }
        if (dist[a][B] > d+B-b) {
            dist[a][B] = d+B-b;
            tipo[a][B] = 1;
            tr[a][B] = {a, b};
            pq.push({d+B-b, a, B});
        }
        if (dist[0][b] > d+a) {
            dist[0][b] = d+a;
            tipo[0][b] = 2;
            tr[0][b] = {a, b};
            pq.push({d+a, 0, b});
        }
        if (dist[a][0] > d+b) {
            dist[a][0] = d+b;
            tipo[a][0] = 3;
            tr[a][0] = {a, b};
            pq.push({d+b, a, 0});
        }
        int k = min(b, A-a);
        int na = a+k, nb = b-k;
        if (dist[na][nb] > d+k) {
            dist[na][nb] = d+k;
            tipo[na][nb] = 4;
            tr[na][nb] = {a, b};
            pq.push({d+k, na, nb});
        }
        k = min(a, B-b);
        na = a-k, nb = b+k;
        if (dist[na][nb] > d+k) {
            dist[na][nb] = d+k;
            tipo[na][nb] = 5;
            tr[na][nb] = {a, b};
            pq.push({d+k, na, nb});
        }
    }
    ii cur = {-1, -1};
    int best = inf;
    if (x <= A) {
        for (int i = 0; i <= B; ++i) {
            if (ckmin(best, dist[x][i])) cur = {x, i};
        }
    }
    if (x <= B) {
        for (int i = 0; i <= A; ++i) {
            if (ckmin(best, dist[i][x])) cur = {i, x};
        }
    }
    if (best == inf) {
        cout << -1 << endl;
        exit(0);
    }
    vector<string> ans;
    while (cur != pair(0LL, 0LL)) {
        ans.pb({moves[tipo[cur.first][cur.second]]});
        cur = tr[cur.first][cur.second];
    }
    reverse(all(ans));
    cout << sz(ans) << ' ' << best << endl;
    for (auto y : ans) cout << y << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
