#include <bits/stdc++.h>
#define pb push_back
#define sz(x) (int) x.size()
using namespace std;

typedef long long ll;
#define fast_io cin.tie(0)->sync_with_stdio(0);
#define endl '\n'

const int INF = 0x3f3f3f3f;
const ll LINF = 0x3f3f3f3f3f3f3f3f;

int32_t main() { fast_io;
	//auto apply = [&] (string s, int k) {
	//	while (k--) {
	//		string ans(s.size(), '0');
	//		int search = 1;
	//		for (int i = 0; i < s.size(); ++i) {
	//			if ('0' + search == s[i]) search ^= 1, ans[i] = '1';
	//		}
	//		s = ans;
	//	}
	//	return s;
	//};
	// we actually have a pretty good guess about the size of the cycle
	// if the number has N digits, then its cycle has size 2^ceil(log(N))
	// why this is true is a good question
	// B x B
	// first number is always 1
	// second alternates 1 - 0 - 1 - 0
	// what abt third?
	// i think i got it!
	// after some inspection, the consecutive strings of a cycle written one below of the other
	// looks like a sierpinski triangle. this motivates us to conclude that
	// s^k[i] = sum_{j=i-k,...,i} ( binom(k)(i-j) * s^0[j]) mod 2
	// and the most interesting thing is that binom(2^p)(i) = 1 iff i = 0 or i = 2^p
	// this can be proven easily by induction.
	// with this, we can derive that the size of the cycle of a N digit number is 2^ceil(log(N)),
	// and also arrive at a pretty neat solution. O(NlogK)	
	int n, k; cin >> n >> k;
	string s; cin >> s;
	for (int bit = 0; (1 << (max(0, bit-1))) < n; ++bit) {
		if (k % 2 == 0) { k /= 2; continue; }
		string new_s(n, '0');
		int pt = 1 << bit;
		for (int i = 0; i < n; ++i) {
			int prv = (i >= pt ? s[i-pt] - '0' : 0);
			int mee = s[i] - '0';
			if (prv ^ mee) new_s[i] = '1';
		}
		k /= 2, swap(new_s, s);
	}
	cout << s << endl;
}

