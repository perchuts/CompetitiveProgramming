#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
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
	int n = s.size(), N = max(n, 260);
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

void solve2(int want) {
	vector<string> ss;
	vector<vector<int>> table = vector<vector<int>>(want, vector<int>(want));
	int tenta = 0;
	set<int> total, save;
	while (sz(ss) != want) {
		total = save;
		string s;
		for (int j = 0; j < rnd(1, want*want); ++j) {
			int k = rnd(0, 5);
			if (k == 5) k = 1;
			else k = 0;
			s += char('0'+k);
		}
		bool ok = 1;
		for (int w = 0; w < 2; ++w) {
			for (auto x : ss) {
				string s2 = (w ? x + s : s + x);
				auto sa = suffix_array(s2);
				auto lcp = kasai(s2, sa);
				int distinct = 0;
				for (int i = 0; i < sz(s2); ++i) distinct += sa[i] + 1 - lcp[i];	
				if (total.find(distinct) != end(total)) { 
					//cout << "failed: " << distinct << " already is in set!" << endl;
					ok = 0; break; }
				total.insert(distinct);
			}
			if (w == 0) ss.pb(s);
		}
		if (ok == false) {
			ss.pop_back();
			continue;
		}
		//cout << "passei -> " << sz(ss) << endl;
		//cout << "coloquei " << ss.back() << endl;
		//for (auto x : put) cout << x << ' ';
		//cout << endl;
		save = total;
		tenta++;
	}
	for (auto x : ss) {
		for (auto y : x) cout << (y == '1' ? "X" : "O");
		cout << endl;
	}
	//for (int i = 0; i < want; ++i) for (int j = 0; j < want; ++j) cout << table[i][j] << " \n"[j==want-1];
	for (int i = 0; i < want; ++i) for (int j = 0; j < want; ++j) {
		string s = ss[i] + ss[j];
		auto sa = suffix_array(s);
		auto lcp = kasai(s, sa);
		for (int k = 0; k < sz(s); ++k) table[i][j] += sa[k] + 1 - lcp[k];	
	}
	int q; cin >> q;
	int n = want;
	while (q--) {
		int p; cin >> p;
		bool ok = 0;
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < n; ++j) {
				if (table[i][j] == p) {
					cout << i + 1 << ' ' << j + 1 << endl;
					ok = 1;
					break;
				}
			}			
			if (ok) break;
		}		
		assert(ok);
	}
}
int32_t main(){_
	int n; cin >> n;
	solve2(n);
}
