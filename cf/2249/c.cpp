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

const int MAX = 3e5 + 10;
namespace seg {
	ll seg[4*MAX], lazy[4*MAX];
	int n;

ll build(int p, int l, int r) {
    lazy[p] = 0;
    if (l == r) return seg[p] = 0;
    int m = (l+r)/2;
    return seg[p] = build(2*p, l, m) + build(2*p+1, m+1, r);
}
    void build(int n2) {
		n = n2;
		build(1, 0, n-1);
	}
	void prop(int p, int l, int r) {
		seg[p] += lazy[p];
		if (l != r) lazy[2*p] += lazy[p], lazy[2*p+1] += lazy[p];
		lazy[p] = 0;
	}
	ll update(int a, int b, int x, int p=1, int l=0, int r=n-1) {
    if (a > b) return 0LL;
		prop(p, l, r);
		if (a <= l and r <= b) {
			lazy[p] += x;
			prop(p, l, r);
			return seg[p];
		}
		if (b < l or r < a) return seg[p];
		int m = (l+r)/2;
		return seg[p] = max(update(a, b, x, 2*p, l, m),
			update(a, b, x, 2*p+1, m+1, r));
	}
};

void solve() {
    int n; cin >> n;
    vector<int> p(n);
    for (auto& x : p) cin >> x, --x;
    seg::build(2*n+10);
    vector<int> pos(n+1);
    pos[n] = 2*n+9;
    for (int i = 0; i < n; ++i) pos[p[i]] = i;
    for (int i = 0; i < n; ++i) {
        if (pos[i+1] > pos[i]) seg::update(pos[i], pos[i+1]-1, 1);
    }
    int ans = (seg::seg[1] < 3);
    //if (ans) cout << "ok ";
    //else cout << "no ";
    for (int i = 0; i < n-1; ++i) {
        int val = p[i];
        if (val != 0) {
            if (pos[val-1] < pos[val]) seg::update(pos[val-1], pos[val]-1, -1);
        }
        if (pos[val] < pos[val+1]) seg::update(pos[val], pos[val+1]-1, -1);
        pos[val] += n;
        if (val != 0) {
            if (pos[val-1] < pos[val]) seg::update(pos[val-1], pos[val]-1, 1);
        }
        if (pos[val] < pos[val+1]) seg::update(pos[val], pos[val+1]-1, 1);
        if (seg::seg[1] < 3) {
            //cout << "ok" << " ";
            ans++;
        } else {
            //cout << "no ";
        }
    }
    cout << ans << endl;
    // for each prefix, take the range [L, R] of elements that appear in it.
    // there can be at most one value i \in (L, R) such that i does not exists in the prefix but i-1 does.
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
