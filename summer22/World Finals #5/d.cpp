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
#define mp make_pair
using namespace std;

template<typename X, typename Y> bool ckmin(X& x, const Y& y) { return (y < x) ? (x=y,1):0; }
template<typename X, typename Y> bool ckmax(X& x, const Y& y) { return (x < y) ? (x=y,1):0; }

vector<ii>g[maxn];
map<pair<ii,int>,bool>can;
int dist[maxn];
int p,t;
void dijkstra(){
    for(int i=0;i<=p;i++)dist[i] = inf;
    dist[0] = 0;
    priority_queue<ii,vector<ii>,greater<ii>>pq;
    vector<bool>vis(p+1,false);
    pq.push({0,0});
    while(!pq.empty()){
        int u = pq.top().second, d = pq.top().first;
        pq.pop();
        if(vis[u])continue;
        vis[u] = 1;
        for(auto x:g[u]){
            int v = x.second, w = x.first;
            if(dist[v]>d+w){
                dist[v] = d+w;
                pq.push({dist[v],v});
            }
        }
    }
}
int vis[maxn],ret[maxn];
bool dfs(int u,int d){
    if(u==p-1)return true;
    if(vis[u])return ret[u];
    vis[u] = 1;
    bool ok = 0;
    for(auto x:g[u]){
        int v = x.second, w = x.first;
        if(d+w==dist[v]&&dfs(v,d+w))can[{{max(u,v),min(u,v)},w}] = 1,ok = 1;
    }
    return ret[u] = ok;
}
vector<pair<ii,int>>edges;
int main(){_    
    while(cin>>p>>t){
        for(int i=1;i<=t;i++){
            int a,b,w;cin>>a>>b>>w;
            g[a].pb({w,b});
            g[b].pb({w,a});
            edges.pb({{max(a,b),min(a,b)},w});
        }
        dijkstra();
        dfs(0,0);
        int ans = 0;
        for(auto x:edges){
            ans+=can[x]*x.second;
        }
        cout<<2*ans<<endl;
        for(int i=0;i<=p;i++){
            g[i].clear();
            ret[i] = 0,vis[i] = 0;
        }
        can.clear();
        edges.clear();
    }    
}
