#include <bits/stdc++.h>
//#define gato
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
const int MAX = maxn;
namespace seg {
	ll seg[4*MAX], lazy[4*MAX];
	int n;
vector<int> v;

	ll build(int p=1, int l=0, int r=n-1) {
		lazy[p] = 0;
		if (l == r) return seg[p] = v[l];
		int m = (l+r)/2;
		return seg[p] = max(build(2*p, l, m), build(2*p+1, m+1, r));
	}
	void build(int n2, vector<int> v2) {
		n = n2, v = v2;
		build();
	}
int get_left(int a, int b, int val, int p=1, int l=0, int r=n-1) {
    if (b < l or r < a or seg[p] < val) return -1;
    if (r == l) return l;
    int m = (l+r)/2;
    int x = get_left(a, b, val, 2*p, l, m);
    if (x != -1) return x;
    return get_left(a, b, val, 2*p+1, m+1, r);
}
};


// Se tiver uma seg de max, da pra descobrir em O(log(n))
// o primeiro e ultimo elemento >= val numa range:

// primeira posicao >= val em [a, b] (ou -1 se nao tem)
int solve(vector<int> v, int n){
    int ptr = n-1, ans = 1;
    vector<int> aa(n);
    stack<int> maior, menor;
    for (int i = 0; i < n; ++i) {
        while (!maior.empty() and v[maior.top()] < v[i]) maior.pop();
        while (!menor.empty() and v[menor.top()] > v[i]) menor.pop();
        int p1 = (maior.empty() ? -1 : maior.top());
        int p2 = (menor.empty() ? -1 : menor.top());
        maior.push(i);
        menor.push(i);
        aa[i] = min(p1, p2);
    }
    while (!maior.empty()) maior.pop();
    while (!menor.empty()) menor.pop();
    maior.push(n-1);
    menor.push(n-1);
    seg::build(n, aa);
    for (int i = n-2; ~i; --i) {
        while (!maior.empty() and v[maior.top()] < v[i]) maior.pop();
        while (!menor.empty() and v[menor.top()] > v[i]) menor.pop();
        int p1 = (maior.empty() ? n : maior.top());
        int p2 = (menor.empty() ? n : menor.top());
        maior.push(i);
        menor.push(i);
        int seta = max(p1, p2);
        if (seta <= ptr) {
            int x = seg::get_left(seta, ptr, i);
            if (x != -1) ckmin(ptr, x-1);
        }
        ans += ptr - i + 1;
    }
    return ans;
}

int32_t main(){_
    #ifndef gato
    int t = 1;
    cin >> t;
    while (t--) {
        int n; cin >> n;
        vector<int> a(n);
        for (auto& x : a) cin >> x;
        cout << solve(a, n) << endl;
    }
    #else
    auto W = [] (vector<int> p) {
        int n = sz(p);
        int lis = 0, lds = 0;
        vector<int> dp1(n), dp2(n);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < i; ++j) {
                if (p[i] < p[j]) ckmax(dp2[i], dp2[j]);
                else ckmax(dp1[i], dp1[j]);
            }
            dp1[i]++, dp2[i]++;
            ckmax(lis, dp1[i]);
            ckmax(lds, dp2[i]);
        }
        return (lis + lds == n+1);
    };
    int t = 1;
    while (true) {
        int n = rnd(5, 6);
        vector<int> p(n); iota(all(p), 1);
        shuffle(all(p), rng);
        int ans = 0;
        for (int l = 0; l < n; ++l) {
            vector<int> pp;
            for (int r = l; r < n; ++r) {
                pp.pb(p[r]);
                ans += W(pp);
            }
        }
        int my = solve(p, n);
        if (my != ans) {
            cout << "Wrong answer on test " << t << endl;
            cout << n << endl;
            for (auto x : p) cout << x << ' ';
            cout << endl;
            exit(0);
        }
        cout << "Accepted on test " << t++ << endl;
    }
    #endif
}
