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
#define mod 1000000000 //998244353
#define _ ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);

using namespace std;

template<typename X, typename Y> bool ckmin(X& x, const Y& y) { return (y < x) ? (x=y,1):0; }
template<typename X, typename Y> bool ckmax(X& x, const Y& y) { return (x < y) ? (x=y,1):0; }

unordered_set<int>g[maxn],rev[maxn];
bool ok[maxn];
ll vis[maxn],ways[maxn],reachable[maxn];
map<ii,ll>qnt;

void dfs(int u){
    reachable[u]=(u==2);
    for(auto v:g[u]){
        if(reachable[v]==-1)dfs(v);
        reachable[u]|=reachable[v];
    }
}

bool dfs2(int u){
    vis[u] = 1;
    for(auto v:g[u]){
        if(!reachable[v])continue;
        if(vis[v]==1)return 1;
        if(!vis[v]&&dfs2(v))return 1;
    }
    vis[u] = 2;
    return 0;
}

bool big;

void modsum(ll &x,ll y){
    x+=y;
    if(x>mod)big=1,x%=mod;
}

ll dfs3(int u){
    if(ok[u])return ways[u];
    ok[u]=1;
    for(auto v:rev[u]){
        if(!reachable[v])continue;
        modsum(ways[u],dfs3(v)*qnt[{v,u}]);
    }
    return ways[u];
}

int main(){_
    int n,m;cin>>n>>m;
    for(int i=1;i<=m;i++){
        int a,b;cin>>a>>b;
        qnt[{a,b}]++;
        g[a].insert(b);
        rev[b].insert(a);
    }
    for(int i=1;i<=n;i++)reachable[i] = -1;
    dfs(1);
    if(!reachable[2]){
        cout<<0<<endl;
        return 0;
    }
    if(dfs2(1)){
        cout<<"inf"<<endl;
    }else{
        ways[1] = 1,ok[1]=1;
        ll ans = dfs3(2);
        if(big)for(int i=1;i<=8-floor(log10(ans));i++)cout<<"0";
        cout<<ans<<endl;
    }
}