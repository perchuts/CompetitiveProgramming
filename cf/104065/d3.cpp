#include<cstdio>
#include<iostream>
#include<algorithm>
#define int long long
#define RI register int
#define CI const int&
using namespace std;
typedef long double LDB;
const int N=1e6+5;
struct ifo
{
	int c; LDB p;
	friend inline bool operator < (const ifo& A,const ifo& B)
	{
		return A.p>B.p;
	}
}o[N],t[N]; int n,m,pfx[N],sfx[N]; LDB ans;
signed main()
{
	//freopen("D.in","r",stdin); freopen("D.out","w",stdout);
	RI i,j; for (scanf("%lld",&n),i=1;i<=n;++i) scanf("%Lf%lld",&o[i].p,&o[i].c);
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
	return printf("%.12Lf",ans),0;
}


