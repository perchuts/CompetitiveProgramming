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
 
vector<int>g[2*maxn];
pair<int,int>dp[2*maxn][2];
bool mark[2*maxn][2];
int w[2*maxn];
ii mx(ii a,ii b){
    if(a.first!=b.first)return max(a,b);
    else return min(a,b);
}

void add(ii& a,ii b){
    a.first += b.first, a.second += b.second;
}

pair<int,int> dfs(int u,int p,bool type){
    if(mark[u][type])return dp[u][type];
    mark[u][type] = 1;
    dp[u][type].first = type;
    if(type)dp[u][type].second += sz(g[u]);
    else dp[u][type].second = 1;
    for(auto v:g[u]){
        if(v==p)continue;
        if(type)add(dp[u][type],dfs(v,u,0));
        else add(dp[u][type],mx(dfs(v,u,0),dfs(v,u,1)));
    }
    return dp[u][type];
}

void dfs2(int u,int p,int type){    
    if(!type)w[u] = 1;
    else w[u] = sz(g[u]);
    for(auto v:g[u]){
        if(v==p)continue;
        if(type)dfs2(v,u,0);
        else dfs2(v,u,mx(dp[v][0],dp[v][1])==dp[v][1]); 
    }
}
 
int main(){_
    int n;cin>>n;
    for(int i=1;i<n;++i){
        int a,b;cin>>a>>b;
        g[a].pb(b);g[b].pb(a);
    }    
    if(n==2){
        cout<<"2 2\n1 1\n";
    }else{
        ii answer = mx(dfs(1,1,0),dfs(1,1,1));
        cout<<answer.first<<" "<<answer.second<<endl;   
        dfs2(1,1,mx(dp[1][1],dp[1][0])==dp[1][1]);
        for(int i=1;i<=n;++i)cout<<w[i]<<" ";
        cout<<endl;
    }
}