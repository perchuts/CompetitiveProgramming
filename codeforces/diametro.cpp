/*
    Seletiva IOI 2019
    Diâmetro
    https://codeforces.com/group/2k70zKp2Ci/contest/352783/problem/A
    por Gabriel Lucas    

    Essa solve não pega todos os pontos. Ela funciona só pras 5 primeiras subtasks
    A solve full usa Treap + small to large e é muito extensa
*/

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
const int maxn = 2e5+100;
 
template<typename X, typename Y> bool ckmin(X& x, const Y& y) { return (y < x) ? (x=y,1):0; }
template<typename X, typename Y> bool ckmax(X& x, const Y& y) { return (x < y) ? (x=y,1):0; }
 
vector<int>g[maxn];
int lvl[maxn], par[maxn];
ll n,l,r, weight[maxn];
ll leaves, tamDiametro;
bool leaf[maxn];
 
void build(int u,int p){
    par[u] = p, lvl[u] = lvl[p]+1;
    bool flag = 1;
    for(auto v:g[u]){
        if(v!=p){
            flag = 0;
            build(v,u);
        }
    }
    if((u==1&&sz(g[u])==1)||flag)++leaves, leaf[u] = 1;
}
 
ll paintPath(int i,int j){
    ll resp = 0;
    for(int i=2;i<=n;++i)weight[i] = l;
    if(lvl[i]<lvl[j])swap(i,j);
    while(lvl[i]!=lvl[j])weight[i] = r, i = par[i], resp++;
    while(i!=j){
        weight[i] = weight[j] = r, i = par[i], j = par[j], resp+=2;
    }
    return resp*r;
}
 
int best, idxbest;
 
void dfs1(int u,int p, ll d){
    if(ckmax(best,d))idxbest = u;
    for(auto v:g[u]){
        if(v==p)continue;
        ll w = (lvl[v]>lvl[u]?weight[v]:weight[u]);
        dfs1(v,u,d+w);
    }
}
 
ll findDiam(){
    best = -1;
    dfs1(1,1,0);
    dfs1(idxbest,idxbest,0);
    return best;
}
 
bool can(int i,int j){
    ll p = paintPath(i,j), diam = findDiam();
    return p==diam;
}
 
int subt[maxn];
bool vis[maxn];
 
int dfs2(int u,int p){
    subt[u] = 1;
    for(auto v:g[u]){
        if(v==p||vis[v])continue;
        subt[u] += dfs2(v,u);
    }
    return subt[u];
}
 
int find_centroid(int u,int p, int n){
    for(auto v:g[u]){
        if(v==p||vis[v])continue;
        if(subt[v]>2*n)return find_centroid(v,u,n);
    }
    return u;
}
ll dist[maxn], current[maxn];
 
void processa(int u,int p,int lvl){
    ++current[lvl];
    for(auto v:g[u]){
        if(vis[v]||v==p)continue;
        processa(v,u,lvl+1);
    }
}
 
ll decomposition(){
    queue<int>q;
    q.push(1);
    ll resp = 0;
    while(!q.empty()){
        int u = q.front();q.pop();
        int centroid = find_centroid(u,u,dfs2(u,u));
        vis[centroid] = 1;
        int m = min(subt[u]/2+1,int(tamDiametro));
        for(int i=0;i<=m;++i)dist[i] = 0;
        dist[0] = 1;
        for(auto v:g[centroid]){
            if(vis[v])continue;
            for(int i=0;i<=m;++i)current[i] = 0;
            processa(v,centroid,1);
            for(int i=1;i<=m;++i)resp += current[i]*dist[tamDiametro-i];
            for(int i=1;i<=m;++i)dist[i] += current[i];
            q.push(v);
        }
    }
    return resp;
}
 
ll resp = 0;
 
int dp[maxn], up[maxn]; 
 
pair<ll,ll> dfs3(int u,int p){// height, leaves
    ll lv = 0, bigL = 0, alt = 1ll, rest = 0;
    vector<int>pref(sz(g[u])+3,0),suf(sz(g[u])+3,0);
    for(int i=0;i<sz(g[u]);++i){
        int v = g[u][i];
        if(v==p)continue;
        pair<ll,ll> cur = dfs3(v,u);
        pref[i+1] = cur.first+1;//height of i+1-th child
        if(!leaf[v]){
            if(2*cur.first>n)bigL = cur.second;
            else rest += cur.second;
        }else ++lv;
        ckmax(alt, cur.first+1ll);
    }
 
    for(int i=sz(g[u]);i>=1;--i)suf[i] = max(suf[i+1],pref[i]);
 
    for(int i=1;i<=sz(g[u]);++i)ckmax(pref[i],pref[i-1]);
 
    for(int i=0;i<sz(g[u]);++i){
        int v = g[u][i];
        if(v==p)continue;
        dp[v] = max(pref[i],suf[i+2]);
    }
 
    if(bigL){
        resp += (lv*(lv-1ll))/2;
        resp += lv*(leaves - lv - bigL);
    }
    
    return {alt,bigL + lv + rest + ll(leaf[u])};
}
 
ll dfs4(int u,int p){
    ll rest = 0, lv = 0;
    if(u!=p)up[u] = max(up[p]+1, dp[u]);
    for(auto v:g[u]){
        if(v==p)continue;
        if(leaf[v])++lv;
        else rest += dfs4(v,u);
    }
    if(2*up[u]>n){
        resp += lv*rest;
        resp += (lv*(lv-1ll))/2;
    }
    return lv+rest+ll(leaf[u]);
}
 
int main(){_
    cin>>n>>l>>r;
    for(int i=1;i<n;++i){
        int u,v;cin>>u>>v;
        g[u].pb(v);g[v].pb(u);
    }    
    build(1,1);
    if(n<=300){//brute force - Subtasks 1 + 2
        int ans = 0;
        for(int i=1;i<=n;++i){
            for(int j=i+1;j<=n;++j){
                ans += can(i,j);
            }
        }
        cout<<ans<<endl;
    }else if(l==1&&r==n){//Subtask 3
        cout<<(leaves*(leaves-1ll))/2<<endl;
    }else if(l==n&&r==n+1){//Subtask 4
        for(int i=2;i<=n;++i)weight[i] = 1;
        tamDiametro = findDiam();
        cout<<decomposition()<<endl;
    }else{//Subtask 5
        int st = 1;
        for(int i=1;i<=n;++i){
            if(!leaf[i]){
                st = i;break;
            }
        }
        ll tot = (leaves*(leaves-1ll))/2;
        dfs3(st,st);dfs4(st,st);
        cout<<tot - resp<<endl;
    }
}