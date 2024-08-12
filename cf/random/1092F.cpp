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
ll a[2*maxn], sub[2*maxn], dentro[2*maxn], fora[2*maxn];

ll dfs(int u,int p){
    ll sum = a[u];
    for(auto v:g[u]){
        if(v==p)continue;
        sum += dfs(v,u);
    }
    return sub[u] = sum;
}

ll dfs2(int u,int p){
    ll sum = 0;
    for(auto v:g[u]){
        if(v==p)continue;
        sum += dfs2(v,u) + sub[v];
    }
    dentro[u] = sum;
    for(auto v:g[u]){
        if(v==p)continue;
        fora[v] = dentro[u] - dentro[v] - sub[v] + sub[u] - sub[v]; 
    }
    return dentro[u];
}

void dfs3(int u,int p){
    fora[u] += fora[p] + sub[1] - sub[p];
    for(auto v:g[u]){
        if(v==p)continue;
        dfs3(v,u);
    }
}

int main(){_
    int n;cin>>n;
    for(int i=1;i<=n;++i)cin>>a[i];    
    for(int i=1;i<n;++i){
        int a,b;cin>>a>>b;
        g[a].pb(b);
        g[b].pb(a);
    }
    dfs(1,1);dfs2(1,1);dfs3(1,1);
    ll ans = 0;
    for(int i=1;i<=n;++i){
        ckmax(ans,dentro[i]+fora[i]);
    }
    cout<<ans<<endl;
}