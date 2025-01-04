#include <bits/stdc++.h>
using namespace std;

#define int ll
#define fast_io cin.tie(0)->sync_with_stdio(0);
#define endl '\n'
typedef long long ll;

vector<int> suffix_array(string s) {
	s += "#";
	int n = s.size(), N = max(n, 260ll);
	vector<int> sa(n), ra(n);
	for(int i = 0; i < n; i++) sa[i] = i, ra[i] = s[i];

	for (int k = 0; k < n; k ? k*= 2 : k++) {
		vector<int> nsa(sa), nra(n), cnt(N);

		for (int i = 0; i < n; i++) nsa[i] = (nsa[i] - k + n) % n, cnt[ra[i]]++;
		for (int i = 1; i < N; i++) cnt[i] += cnt[i-1];
		for (int i  = n-1; i+1;i--) sa[--cnt[ra[nsa[i]]]] = nsa[i];

		for (int i = 1, r = 0; i < n; i++) nra[sa[i]] = r += ra[sa[i]] != 
			ra[sa[i-1]] or ra[(sa[i] + k)%n] != ra[(sa[i-1] + k)%n];
		ra = nra;
		if (ra[sa[n-1]] == n - 1) break;
	}

	//for (auto foo : sa) {
	//	cout << foo << ' ';
	//	cout << s.substr(foo) << endl;
	//}
	//exit(1);
	return vector<int>(sa.begin()+1, sa.end());
}

vector<int> kasai(string s, vector<int> sa) {
	int n = s.size(), k = 0;
	vector<int> ra(n), lcp(n);
	for (int i = 0; i < n; i++) ra[sa[i]] = i;

	for (int i = 0; i < n; i++, k -= !!k) {
		if (ra[i] == n - 1) {k = 0; continue;}
		int j = sa[ra[i] + 1];
		while (i + k < n and j+k < n and s[i+k] == s[j+k]) k++;
		lcp[ra[i]] = k;
	}
	return lcp;
}

int32_t main() {
	fast_io;

	int n; cin >> n;

	string s, t; cin >> s >> t;
	swap(s, t);

	string f = s + s + "$" + t + t;

	int tot_f = n;
	auto sa = suffix_array(f);
	auto lcp = kasai(f, sa);
	//for (int i = 0; i < sa.size(); i++) {
	//	cout << sa[i] << ' ' << lcp[i] << ' ';
	//	cout << f.substr(sa[i]) << endl;
	//}

	vector<ll> pre(sa.size(), 0);
	for (int i = 0; i < sa.size(); i++) {
		if (i > 0) pre[i] = pre[i-1];
		bool si = false;
		if (sa[i] <= 2*n) si = true;

		int sz;
		if (si) {
			sz = 2*n - sa[i];
		} else {
			sz = 4*n + 1 - sa[i];
		}
		if (sz <= n) continue;

		if (!si) pre[i]++; 
	}

	auto qq = [&] (int l, int r) {
		if (l > 0) return pre[r] - pre[l-1];
		else return pre[r];
	};

	ll ans = 0;
	int right = -1;
	for (int i = sa.size() - 1; i>=0; i--) {
		// markings
		//if (sa[i] == 2*n or sa[i] == 4*n + 1) continue;
		if (lcp[i] < n) right = -1;
		else right = max(right, i);

		bool si = false;
		if (sa[i] <= 2*n) si = true;
		int sz;
		if (si) {
			sz = 2*n - sa[i];
		} else {
			sz = 4*n + 1 - sa[i];
		}
		if (sz <= n) continue;

		if (!si) {
			tot_f--;
			continue;
		}

		ll cur = qq(0, i);
		if (right != -1) {
			cur += qq(i, right+1);
		}
		//cerr << sa[i] << ' ' << lcp[i] << endl;
		ans += cur;
	}

	cout << ans << endl;

}
