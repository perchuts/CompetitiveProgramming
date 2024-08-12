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

vector<int>g[maxn];
ll dp[50001][501],qnt[501];
int n,k;
ll ans = 0;

void dfs(int u,int p){
    for(auto v:g[u]){
        if(v==p)continue;
        dfs(v,u);
    }
    dp[u][0] = 1;
    for(auto v:g[u]){
        if(v==p)continue;
        for(int i=0;i<k;i++){
            if(dp[v][i]==0)break;
            else dp[u][i+1]+=dp[v][i];
        }
    }   
    ans+=dp[u][k];
}

void dfs2(int u,int p){//kinda like query-insertion operations while building a centroid decomposition 
    for(auto v:g[u]){
        if(v==p)continue;
        dfs2(v,u);
    }
    for(int i=0;i<=k;i++)qnt[i]=0;
    
    for(auto v:g[u]){
        if(v==p)continue;
        
        for(int i=0;i<k-1;i++)//query
            ans += dp[v][i]*qnt[k-2-i];

        for(int i=0;i<k-1;i++)//insertion
            qnt[i]+=dp[v][i];
        
    }
}

int main(){_
    cin>>n>>k;
    for(int i=1;i<n;i++){
        int a,b;cin>>a>>b;
        g[a].pb(b);
        g[b].pb(a);
    }   
    dfs(1,1);
    dfs2(1,1);
    cout<<ans<<endl;

}