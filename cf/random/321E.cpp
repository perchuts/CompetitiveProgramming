#include <bits/stdc++.h>
#define maxn (int)(1e5+51)
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
#define endl '\n'
#define ll long long
#define pb push_back
#define ull unsigned long long
#define ii pair<int,int>
#define iii tuple<int,int,int>
#define inf 2000000001
#define mod 1000000007 //998244353
#define _ ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);

using namespace std;

template<typename X, typename Y> bool ckmin(X& x, const Y& y) { return (y < x) ? (x=y,1):0; }
template<typename X, typename Y> bool ckmax(X& x, const Y& y) { return (x < y) ? (x=y,1):0; }

char d[4001][4001];

int dp[4001][2], cost[4001][4001], pref[4001][4001];

void compute(int k,int l,int r,int dx,int dy){
    if(l>r)return;
    int md = (l+r)/2, dmd = dx;
    dp[md][k&1] = inf;
    for(int i=dx;i<=min(dy,md-1);++i)if(ckmin(dp[md][k&1], dp[i][!(k&1)] + cost[i+1][md]))dmd=i;
    compute(k,l,md-1,dx,dmd);
    compute(k,md+1,r,dmd,dy);
}


int main(){_
    int n,k;cin>>n>>k;
    for(int i=1;i<=n;++i)
        for(int j=1;j<=n;++j)
            cin>>d[i][j];

    for(int i=1;i<=n;++i)
        for(int j=1;j<=n;++j)
            pref[i][j] = pref[i][j-1] + int(d[i][j]-'0');

    for(int i=1;i<=n;++i)
        for(int j=i;j<=n;++j)
            cost[i][j] = cost[i][j-1] + pref[j][j] - pref[j][i-1];

    for(int i=1;i<=n;++i)dp[i][0] = inf;

    for(int i=1;i<=k;++i)compute(i,1,n,i!=1,n-1);
    

    cout<<dp[n][k&1]<<endl;
}