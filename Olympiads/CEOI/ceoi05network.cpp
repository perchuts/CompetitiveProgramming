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
 
int a[maxn],b[maxn],vis[maxn],in[maxn],low[maxn],timer;    
vector<int>g[maxn];
vector<ii>edges;
map<ii,int>bridge;
//only consider bridges. very standard but interesting problem 
 
void dfs(int x,int p){
    vis[x] = 1;
    in[x] = low[x] = ++timer;
    for(auto v:g[x]){
        if(v==p)continue;
        if(!vis[v]){
            dfs(v,x);
            ckmin(low[x],low[v]);
            if(in[x]<low[v]){
                bridge[{max(x,v),min(x,v)}]=1;
                //cout<<x<<" "<<v<<" bridge"<<endl;
            }
        }else{
            ckmin(low[x],in[v]);
        }
    }
}
 
int n,m,k,l;
 
ii dfs2(int x,int p){
    vis[x] = 1;
    int q1 = a[x],q2 = b[x];
    for(auto v:g[x]){
        if(v==p||vis[v])continue;
        ii child = dfs2(v,x);
        q1+=child.first,q2+=child.second;
        if(bridge[{max(x,v),min(x,v)}])
            if(child.first==k||child.second==l
            ||child.first==0||child.second==0)edges.pb({x,v});
    }
    return {q1,q2};
}

int main(){_
    cin>>n>>m>>k>>l;
    for(int i=1;i<=k;i++){
        int x;cin>>x;
        a[x]=1;
    }
    for(int i=1;i<=l;i++){
        int x;cin>>x;
        b[x]=1;
    }
    for(int i=1;i<=m;i++){
        int a,b;cin>>a>>b;
        g[a].pb(b);
        g[b].pb(a);
    }
    dfs(1,1);
    for(int i=1;i<=n;i++)vis[i] = 0;
    dfs2(1,1);
    cout<<sz(edges)<<endl;
    for(auto [a,b]:edges){
        cout<<a<<" "<<b<<endl;
    }
}