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

int grid[505][505],dp[505][505],n,m;

bool possible(int x){
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(i>1&&j>1)dp[i][j] = max(dp[i-1][j],dp[i][j-1]);
            else if(i>1)dp[i][j] = dp[i-1][j];
            else if(j>1)dp[i][j] = dp[i][j-1];
            else dp[i][j] = x;                
            if(dp[i][j]+grid[i][j] <= 0)dp[i][j] = -inf;
            else dp[i][j]+=grid[i][j];
        }
    }
    return dp[n][m]!=-inf;
}


void solve(){
    cin>>n>>m;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            cin>>grid[i][j];
    int l=0, r = 1e9,ans = 0;
    while(l<=r){
        int md = l + (r-l+1)/2;
        if(possible(md)){
            ans = md;
            r = md-1;
        }else{
            l = md + 1;
        }
    }
    cout<<ans<<endl;
}

;
int main(){_
    //freopen("in.in", "r", stdin);
    //freopen("out.out", "w", stdout);
    int t;cin>>t;
    while(t--)solve();
}