#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
#define endl '\n'
#define pb push_back
#define _ ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);

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
    int n, k; cin >> n >> k;
    vector<int> a(n);
    for (auto& x : a) cin >> x;
    if (k == n) {
        cout << 0 << ' ' << k << endl;
        exit(0);
    }
    // dp[i][j] = menor numero de bichos pra remover pra chegar ate aqui usando j passos
    // transicao: dp[qualquer numero >= 2*eu][j+1] + quantos bichos tem entre eu e ele.
    // nlog^2
    struct segtree {
        vector<int> seg;
        segtree(){}
        segtree(int n) {
            seg = vector<int>(4*n, inf);
        }
        void upd(int i, int l, int r, int x, int y) {
            if (r < x or x < l) return;
            if (l == r) {
                seg[i] = y;
                return;
            }
            int md = (l + r) / 2;
            upd(2*i, l, md, x, y), upd(2*i+1, md+1, r, x, y);
            seg[i] = min(seg[2*i], seg[2*i+1]);
        }
        int query(int i, int l, int r, int x, int y) {
            if (x <= l and r <= y) return seg[i];
            if (r < x or y < l) return inf;
            int md = (l + r) / 2;
            return min(query(2*i, l, md, x, y), query(2*i+1, md+1, r, x, y)); 
        }
    };
    sort(rbegin(a), rend(a));
    a.pb(0);
    vector<segtree> dp(32);
    vector<int> prv(32, inf); prv[0] = -1;
    for (int i = 0; i < 32; ++i) dp[i] = segtree(n);
    int ptr = -1;
    //for (auto x : a) cout << x << ' ';
    //cout << endl;
    for (int i = 0; i <= n; ++i) {
        int lx = i+1, rx = n, id = i+1;
        while (lx <= rx) {
            int md = lx + (rx-lx+1)/2;
            if (2*a[md] <= a[i]) id = md, rx = md-1;
            else lx = md+1;
        }
        while (ptr+1 < i and a[ptr+1] >= 2 * a[i]) ptr++;
        for (int j = 0; j < 32; ++j) {
            int my = min((j?dp[j-1].query(1, 0, n-1, 0, ptr) + i : inf), prv[j]+1);
            prv[j] = my;
            //if (j < 5) cout << my << ' ';
            if (i == n and my <= k) {
                //cout << endl;
                //cout << "Answer: ";
                cout << j << ' ' << my << endl;
                exit(0);
            }
            if (i != n) dp[j].upd(1, 0, n-1, i, my-id);
        }
        //cout << endl;
    }
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}

