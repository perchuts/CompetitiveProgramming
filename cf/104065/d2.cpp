#include <bits/stdc++.h>
#define int long long
#define RI register int
#define CI const int&
using namespace std;
typedef long double LDB;
const int N=1e6+500;
struct ifo
{
	int c; LDB p;
	friend inline bool operator < (const ifo& A,const ifo& B)
	{
		return A.p>B.p;
	}
}o[N],t[N]; int n,m,pfx[N],sfx[N]; LDB ans;
LDB solve(int n, vector<pair<double, int>> pp) {
	//freopen("D.in","r",stdin); freopen("D.out","w",stdout);
	ans = 0;
	for (int i = 0; i <= n + 100; ++i) {
		t[i].c = 0, t[i].p = 0;
		pfx[i] = sfx[i] = 0;
	}
	RI i, j;
	for (i = 1; i <= n; ++i) o[i].p = pp[i-1].first, o[i].c = pp[i-1].second;
	for (sort(o+1,o+n+1),t[m=1]=o[1],i=2;i<=n;++i)
	if (o[i].p==t[m].p) t[m].c+=o[i].c; else t[++m]=o[i];
	for (i=1;i<=m;++i) pfx[i]=pfx[i-1]+t[i].c;
	for (i=m;i>=1;--i) sfx[i]=sfx[i+1]+t[i].c;
	for (i=1;i<=m;++i) if (t[i].p!=1.0L)
	{
		LDB y=1.0L/(1.0L-t[i].p); ans=max(ans,sfx[i]*(1.0L-y));
		auto calc=[&](CI j)
		{
			if (t[j].p==0.0L) return -1e18L; LDB x=1.0L/t[j].p;
			return pfx[j]+sfx[i]-max(pfx[j]*x,sfx[i]*y);
		};
		int l=1,r=i-1; while (r-l>2)
		{
			int lmid=l+(r-l)/3,rmid=r-(r-l)/3;
			if (calc(lmid)>=calc(rmid)) r=rmid; else l=lmid;
		}
		int pos=l; for (j=l+1;j<=r;++j) if (calc(j)>calc(pos)) pos=j;
		ans=max(ans,calc(pos));
	}
	return ans;
}

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
double solve_my(int n, vector<pair<double, int>> bet){

	vector<pair<double, int>> tmp;

	for (int i = 0, j = 0; i < n; i = j) {
		int tot = 0;
		while (j < n && abs(bet[i].first-bet[j].first) < 1e-7) tot += bet[j++].second;
		tmp.pb({bet[i].first, tot});
	}

	swap(tmp, bet);

	n = sz(bet);

	sort(bet.rbegin(), bet.rend());

	vector<double> pref(n+1), suf(n+2);

	for (int i = 1; i <= n; ++i) pref[i] = pref[i-1] + bet[i-1].second;
	for (int i = n; i >= 1; --i) suf[i] = suf[i+1] + bet[i-1].second;

	double ans = 0;

	int ii, jj;
    
	
	auto f = [&] (int i, int j) {
	    if (min(i, j) < 0 || i > n || j > n+1) return;
        assert(i < j);
	    if(ckmax(ans, pref[i] + suf[j] - max((i==0?0:pref[i]/bet[i-1].first), (j>n?0:suf[j]/(1.0-bet[j-1].first))))) ii = i, jj = j;
	    
	};

	for (int i = 1, j = n; i <= n; ++i) {
		auto [p, sexo] = bet[i-1];
		if (p == 0) continue;
		while (j >= 1 && bet[j-1].first != 1.0) {
			auto [p2, sexo2] = bet[j-1];
			double x2 = 1.0/(1.0-p2);
			if (suf[j]*x2 <= pref[i]/p) j--;
			else break;
		}
		for (int p = max(i, j)+1; p <= max(i, j)+3; ++p) f(i, p);
	}

	for (int i = n, j = 1; i >= 1; --i) {
		auto [p, sexo] = bet[i-1];
		if (p == 1) continue;
		while (j <= n && bet[j-1].first != 0) {
			auto [p2, sexo2] = bet[j-1];
			double x2 = 1.0/p2;
			if (pref[j]*x2 <= suf[i]/(1.0-p)) j++;
			else break;
		}
		for (int p = min(i,j)-3; p <= min(i,j)-1; ++p) f(p, i);
	}
    //p maior implica em 1-p menor que implica em 1/(1-p) ainda menor
    // isso impiica em pegar um x = 1/p e um y = 1/(1-p')
	// serase isso tem algum corner? o caso que da errado tem ii = compl(jj)
    // pro jj->1/0.706 * 0.294 
	return ans;
}

mt19937 rng(time(0));

double rnd(double l, double r) {
	uniform_real_distribution<double> uid(l, r);
	return uid(rng);
}
double rnd_int(double l, double r) {
	uniform_int_distribution<int> uid(l, r);
	return uid(rng);
}
int32_t main() {
	int tt = 0;
	while (true) {
		int n = 100000;
		vector<pair<double, int>> vv(n);
		for (auto& [x, y] : vv) {
			x = rnd(0, 1);
			y = rnd(1, 1e8);
		}
		double ans1 = solve(n, vv), ans2 = solve_my(n, vv);
		double diff = abs(ans1-ans2)/max(ans1,1.0);
		if (diff > 1e-6) {
			cout << "Wrong answer on test " << tt << endl;
			cout << n << endl;
			for (auto [x, y] : vv) cout << x << ' ' << y << endl;
			cout << "Your output: " << fixed << setprecision(12) << ans2 << endl;
			cout << "Correct answer" << fixed << setprecision(12) << ans1 << endl;
			exit(0);
		}
		cout << "Accepted on test " << tt++ << endl;
	}
}


