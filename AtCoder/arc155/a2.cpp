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

int solve(int n, int k, string s){
	if (k >= 2 * n) {
		int espaco = k % (2*n);
		int rodadas = k / (2*n);
		string la_dentro(espaco+2*n, '-');
		string sr = s; reverse(all(sr));
		if (rodadas % 2 == 0) swap(s, sr);
		for (int i = 0; i < n; ++i) la_dentro[i] = la_dentro[espaco+n+i] = sr[i];
		bool ok = 1;
		for (int i = 0; i < n; ++i) {
			if (la_dentro[n+i] == '-') la_dentro[n+i] = s[i];
			else ok &= (la_dentro[n+i] == s[i]); 
		}
		for (int i = 0; i < n; ++i) {
			if (la_dentro[espaco+i] == '-') la_dentro[espaco+i] = s[i];
			else ok &= (la_dentro[espaco+i] == s[i]);
		}	
		string s1, s2;
		for (int i = 0; i < espaco+n; ++i) s1 += la_dentro[i];
		for (int i = 0; i < espaco+n; ++i) s2 += la_dentro[n+i];
		string s3 = s1, s4 = s2;
		reverse(all(s3)), reverse(all(s4));
		return ((s1 == s3) && (s2 == s4));
	}
	else {
		string ss(k, '-');
		for (int i = 0; i < min(n, k); ++i) ss[k-1-i] = s[i];
		bool ok = 1;
		for (int i = 0; i < min(n, k); ++i) {
			if (ss[i] == '-') ss[i] = s[n-1-i];
			else ok &= (ss[i] == s[n-1-i]);
		}
		string a = s + ss, b = ss + s, a2 = a, b2 = b;
		reverse(all(a2)), reverse(all(b2));
		ok &= (a == a2 && b == b2);
		return ok;
	}
	return false;
}

mt19937 rng(time(0));

int rnd(int l, int r) {
	uniform_int_distribution<int> uid(l, r);
	return uid(rng);
}

int32_t main(){_
	int tt = 0;
	while (true) {
		int n = rnd(1, 10), k = rnd(1, 100);
		string s;
		for (int i = 0; i < n; ++i) {
			char c = char('a'+rnd(0, 25));
			s += c;
		}
		int my = solve(n, k, s);
		string s2(k, '-');
		int falta = k, p1 = n+k-1, p2 = 0, turn = 0, id1 = k-1, id2 = 0;
		bool ok = 1;
		while (falta) {
			if (turn) {
				int mirror = n+k-1-p2;
				char want = (mirror >= k ? s[mirror-k] : s2[mirror]);
				assert(want != '-');
				if (s2[id2] == '-') falta--, s2[id2++] = want;
				else ok &= (s2[id2++] == mirror);
				p2++;
			} else {
				// vou descobrir coisas da direita!
				int mirror = n+k-1-p1;
				char want = (mirror < n ? s[mirror] : s2[mirror-n]);
				assert(want != '-');
				if (s2[id1] == '-') falta--, s2[id1--] = want;
				else ok &= (s2[id1--] == mirror);
				p1--;
			}
			turn ^= 1;
		}
		string a = s + s2, b = s2 + s, a2 = a, b2 = b;
		reverse(all(a2)), reverse(all(b2));
		bool my_res = (a == a2 && b == b2);
		ok = my_res;
		if (my != ok) {
			cout << "Wrong answer on test " << tt << endl;
			cout << n << ' ' << k << endl;
			cout << s << endl;
			cout << "Your output: " << my << endl;
			cout << "Correct answer: " << ok << endl;
			cout << s2 << endl;
			exit(0);
		}
		cout << "Accepted on test " << ++tt << endl;
	}
}
