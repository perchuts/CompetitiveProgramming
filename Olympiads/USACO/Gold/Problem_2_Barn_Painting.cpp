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

int color[maxn];
ll dp[maxn][3];

//dp[i][j] = prod(dp[v][x]) for all children of i = v and 1<=x<=3 not equal to j.
vector<int>g[maxn];
void dfs(int u,int p){
    for(auto v:g[u]){
        if(v==p)continue;
        dfs(v,u);
    }
    if(color[u]){
        dp[u][color[u]]=1;
        int ok=0;
        for(auto v:g[u]){
            if(v==p)continue;
            ll sum = (dp[v][1]+dp[v][2]+dp[v][3])%mod;
            sum = ((sum-dp[v][color[u]])%mod+mod)%mod;
            dp[u][color[u]] = (dp[u][color[u]]*sum)%mod;
        }
    }else{
        for(int i=1;i<=3;i++){
            dp[u][i]=1;
            int ok=0;
            for(auto v:g[u]){
                if(v==p)continue;
                ll sum = (dp[v][1]+dp[v][2]+dp[v][3])%mod;
                sum = ((sum-dp[v][i])%mod+mod)%mod;
                dp[u][i] = (dp[u][i]*sum)%mod;
            }
        }
    }
}


int main(){_
    freopen("barnpainting.in", "r", stdin);
    freopen("barnpainting.out", "w", stdout);
    int n,k;cin>>n>>k;
    for(int i=1;i<n;i++){
        int a,b;
        cin>>a>>b;
        g[a].pb(b);
        g[b].pb(a);
    }
    for(int i=1;i<=k;i++){
        int a,c;cin>>a>>c;
        color[a] = c;
    }
    dfs(1,1);
    cout<<((dp[1][1]+dp[1][2]+dp[1][3])%mod)<<endl;
}