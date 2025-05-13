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
vector<int> suffix_array(string s) {
	s += "$";
	int n = s.size(), N = max(n, 260LL);
	vector<int> sa(n), ra(n);
	for(int i = 0; i < n; i++) sa[i] = i, ra[i] = s[i];

	for(int k = 0; k < n; k ? k *= 2 : k++) {
		vector<int> nsa(sa), nra(n), cnt(N);

		for(int i = 0; i < n; i++) nsa[i] = (nsa[i]-k+n)%n, cnt[ra[i]]++;
		for(int i = 1; i < N; i++) cnt[i] += cnt[i-1];
		for(int i = n-1; i+1; i--) sa[--cnt[ra[nsa[i]]]] = nsa[i];

		for(int i = 1, r = 0; i < n; i++) nra[sa[i]] = r += ra[sa[i]] !=
			ra[sa[i-1]] or ra[(sa[i]+k)%n] != ra[(sa[i-1]+k)%n];
		ra = nra;
		if (ra[sa[n-1]] == n-1) break;
	}
	return vector<int>(sa.begin()+1, sa.end());
}
void solve(){
    int n; cin >> n;
    vector<int> suf(n), onde(n);
    for (auto& x : suf) cin >> x, --x;
    for (int i = 0; i < n; ++i) onde[suf[i]] = i;
    vector<int> quebra(n);
    for (int i = 1; i < n; ++i) {
        int a = suf[i-1], b = suf[i], ok = 1;
        while (min(a, b) < n) {
            ok &= (onde[a] < onde[b]);
            a++, b++;
        }
        if (!ok) quebra[i] = 1;
    }
    string ans(n, 'a');
    for (auto x : quebra) cout << x << ' ';
    cout << endl;
    for (int i = 1; i < n; ++i) {
        ans[suf[i]] = ans[suf[i-1]];
        if (quebra[i]) ans[suf[i]]++;
        if (ans[suf[i]] > 'z') {
            cout << -1 << endl;
            exit(0);
        }
    }
    auto sa = suffix_array(ans);
    for (auto x : sa) cout << x + 1 << ' ';
    cout << endl;
    cout << ans << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
