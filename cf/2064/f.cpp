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
namespace sparse {
	int m[18][maxn], n;
	void build(int n2, vector<int> v) {
		n = n2;
		for (int i = 0; i < n; i++) m[0][i] = v[i];
		for (int j = 1; (1<<j) <= n; j++) for (int i = 0; i+(1<<j) <= n; i++)
			m[j][i] = max(m[j-1][i], m[j-1][i+(1<<(j-1))]);
	}
	int query(int a, int b) {
		int j = __builtin_clz(1) - __builtin_clz(b-a+1);
		return max(m[j][a], m[j][b-(1<<j)+1]);
	}
}
void solve(){
    int n, k; cin >> n >> k;
    vector<int> a(n);
    for (auto& x : a) cin >> x;
    sparse::build(n, a);
    vector<int> ans(n+1), seta(n+1);
    stack<ii> st, st2;
    st.push({-inf, n});
    st2.push({inf, n});
    st.push({a.back(), n-1});
    int tot = 0;
    map<int, int> occ;
    for (int i = n-2; ~i; --i) {
        while (!st.empty() and st.top().first >= a[i]) st.pop();
        while (!st2.empty() and st2.top().first <= a[i]) st2.pop();
        seta[i] = st2.top().second;
        ans[i] = ans[st.top().second];
        if (occ[k-a[i]] != 0) {
            int j = occ[k-a[i]];
            int l = st.top().second, r = n-1, ptr = st.top().second;
            while (l <= r) {
                int md = l + (r-l+1)/2;
                if (sparse::query(st.top().second, md) <= k-a[i]) ptr = md, l = md+1;
                else r = md-1;
            }
            ans[i] += max(0LL, min(st.top().second,ptr)-j);
            // depois daqui, nao posso ter ninguem maior ou igual a esse bicho!
        }
        occ[a[i]] = i;
        tot += ans[i];
        st.push({a[i], i});
        st2.push({a[i], i});
    }
    for (int i = 0; i < n; ++i) cout << ans[i] << ' ';
    cout << endl;
    cout << tot << endl;
}

int32_t main(){_
    int t = 1; cin >> t;
    while(t--) solve();
}
