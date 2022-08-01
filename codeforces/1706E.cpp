#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
#define endl '\n'
#define pb push_back
#define _ ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
 
using namespace std;
 
using ll = long long;
using ull = unsigned long long;
using ii = pair<int,int>;
using iii = tuple<int,int,int>;
 
const int inf = 2e9+1;
const int mod = 1e9+7;
const int maxn = 3e5+100;
 
template<typename X, typename Y> bool ckmin(X& x, const Y& y) { return (y < x) ? (x=y,1):0; }
template<typename X, typename Y> bool ckmax(X& x, const Y& y) { return (x < y) ? (x=y,1):0; }
 
vector<ii>parents[maxn];
vector<int>componente[maxn];
int par[maxn], lvl[maxn];
 
int findp(int x){return par[x] = (par[x]==x?x:findp(par[x]));}
 
void merge(int u,int v,int idx){
    u = findp(u), v = findp(v);
    if(u==v)return;
    if(lvl[u]<lvl[v])swap(u,v);
    par[v] = u;
    for(auto x:componente[v]){
        parents[x].pb({u,idx});
        componente[u].pb(x);
    }
    if(lvl[u]==lvl[v])++lvl[u];
}
 
vector<ii>seg[4*maxn];
 
int tmp[maxn];
 
void build(int i,int l,int r){
    if(l==r){
        seg[i] = parents[l];
        return;
    }
    int md = (l+r)/2;
    build(2*i,l,md), build(2*i+1,md+1,r);
    for(auto [a,b]:seg[2*i]){
        tmp[a] = b;
    }
    bool ok = 0;
    for(auto [a,b]:seg[2*i+1]){
        if(!ok&&tmp[a]!=-1){
            ok = 1;
            seg[i].pb({a,max(tmp[a],b)});
        }else if(ok){
            seg[i].pb({a,b});
        }
    }
    for(auto [a,b]:seg[2*i]){
        tmp[a] = -1;
    }
}
 
vector<ii> query(int i,int l,int r,int x,int y){
    if(l>y||r<x)return {};
    else if(x<=l&&r<=y)return seg[i];
    int md = (l+r)/2;
    vector<ii>v1 = query(2*i,l,md,x,y), v2 = query(2*i+1,md+1,r,x,y);
    if(v1.empty())return v2;
    else if(v2.empty())return v1;
    vector<ii>res;
    for(auto [a,b]:v1){
        tmp[a] = b;
    }
    bool ok = 0;
    for(auto [a,b]:v2){
        if(!ok&&tmp[a]!=-1){
            ok = 1;
            res.pb({a,max(tmp[a],b)});
        }else if(ok){
            res.pb({a,b});
        }
    }
    for(auto [a,b]:v1){
        tmp[a] = -1;
    }
    return res;
}
 
void solve(){
    int n, m, q;cin>>n>>m>>q;
 
    for(int i=1;i<=n;++i){
        par[i] = i, lvl[i] = 0, tmp[i] = -1;
        componente[i].pb(i);
        parents[i].pb({i,0});
    }
 
    for(int i=1;i<=m;++i){
        int u,v;cin>>u>>v;
        merge(u,v,i);
    }
 
    build(1,1,n);
 
    while(q--){
        int l,r;cin>>l>>r;
        cout<<query(1,1,n,l,r)[0].second<<" ";
    }
 
    cout<<endl;
 
    for(int i=1;i<=n;++i){
        componente[i].clear();
        parents[i].clear();
    }
 
    for(int i=1;i<=4*n;++i)seg[i].clear();
}
 
int main(){_
    //freopen("in.in", "r", stdin);
    //freopen("out.out", "w", stdout);
    int t;cin>>t;
    while(t--)solve();
}