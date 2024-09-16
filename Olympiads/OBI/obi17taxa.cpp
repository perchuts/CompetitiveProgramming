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

int dp[401][401],pr[401],v[401];//dp[i][j] = custo para formar os terrenos no intervalo [i,j] (i<=j) 

int interval(int l,int r){return pr[r]-pr[l-1];}

int solve(int l,int r){
    if(l==r)return 0;
    if(dp[l][r]!=-1)return dp[l][r];
    int tot = interval(l,r);
    dp[l][r] = inf;
    for(int i=l;i<r;i++){
        int t1 = interval(l,i);
        int t2 = tot - t1;
        int t3 = solve(l,i)+solve(i+1,r);
        ckmin(dp[l][r],t3+max(t1,t2));
    }
    return dp[l][r];
}

int main(){_
    int n;double f;cin>>n>>f;
    int tot = 0;
    for(int i=1;i<=n;i++){
        cin>>v[i];    
        v[i+n] = v[i];
        tot += v[i];
    }
    for(int i=1;i<=2*n;i++)pr[i] = pr[i-1] + v[i];
    int ans = inf;

    for(int i=1;i<=2*n;i++)for(int j=1;j<=2*n;j++)dp[i][j] = -1;

    for(int i=1;i<=n;i++){
        for(int j=i;j<=n;j++){
            int t1 = interval(i,j);
            int t2 = tot - t1;
            int t3 = solve(i,j)+solve(j+1,n+i-1);
            ckmin(ans,max(t1,t2)+t3);
        }
    }
    cout<<fixed<<setprecision(2)<<f*(double)ans<<endl;
}