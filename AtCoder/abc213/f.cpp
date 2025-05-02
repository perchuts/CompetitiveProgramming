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
// Suffix Array - O(n log n)
//
// kasai recebe o suffix array e calcula lcp[i],
// o lcp entre s[sa[i],...,n-1] e s[sa[i+1],..,n-1]
//
// Complexidades:
// suffix_array - O(n log(n))
// kasai - O(n)

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

vector<int> kasai(string s, vector<int> sa) {
	int n = s.size(), k = 0;
	vector<int> ra(n), lcp(n);
	for (int i = 0; i < n; i++) ra[sa[i]] = i;

	for (int i = 0; i < n; i++, k -= !!k) {
		if (ra[i] == n-1) { k = 0; continue; }
		int j = sa[ra[i]+1];
		while (i+k < n and j+k < n and s[i+k] == s[j+k]) k++;
		lcp[ra[i]] = k;
	}
	return lcp;
}
void solve(){
    int n; cin >> n;
    string s; cin >> s;
    auto sa = suffix_array(s);
    auto lcp = kasai(s, sa);
    vector<int> ans(n), ans2(n);
    vector<ii> caras;
    caras.pb({0, 0});
    for (int i = 1; i < n; ++i) {
        int idx = sa[i];
        while (caras.back().first > lcp[i-1]) caras.pop_back();
        int j = caras.back().second;
        ans[idx] = (j!=-1?ans[sa[j]]:0) + (i-j)*lcp[i-1];
        caras.pb({lcp[i-1], i});
    }
    caras.clear();
    caras.pb({0, n-1});
    for (int i = n-2; ~i; --i) {
        int idx = sa[i];
        while (caras.back().first > lcp[i]) caras.pop_back();
        int j = caras.back().second;
        ans2[idx] = (j!=n?ans2[sa[j]]:0) + (j-i)*lcp[i];
        caras.pb({lcp[i], i});
    }
    //cout << "sa: ";
    //for (auto x : sa) cout << x << ' ';
    //cout << endl;
    //cout << "lcp: ";
    //for (auto x : lcp) cout << x << ' ';
    //cout << endl;
    //cout << "ans: ";
    //for (auto x : ans) cout << x << ' ';
    //cout << endl;
    //cout << "ans2: ";
    //for (auto x : ans2) cout << x << ' ';
    //cout << endl;
    for (int i = 0; i < n; ++i) cout << ans[i] + ans2[i] + n-i << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
