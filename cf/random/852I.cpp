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
const int maxn = 1e5+100;
const int _log = 20;

template<typename X, typename Y> bool ckmin(X& x, const Y& y) { return (y < x) ? (x=y,1):0; }
template<typename X, typename Y> bool ckmax(X& x, const Y& y) { return (x < y) ? (x=y,1):0; }


int n, lvl[maxn], par[maxn][_log], st[maxn], en[maxn], _time, block[2*maxn], who[2*maxn], vis[maxn];
ll answer[maxn];

vector<int>g[maxn];

void dfs(int u,int p){
    lvl[u] = lvl[p]+1, par[u][0] = p, who[_time] = u, st[u] = _time++;
    for(int i=1;i<_log;++i)
        if(par[u][i-1])par[u][i] = par[par[u][i-1]][i-1];

    for(auto v:g[u]){
        if(v==p)continue;
        dfs(v,u);
    }

    who[_time] = u, en[u] = _time++;
}

int lca(int u,int v){
    if(lvl[u]<lvl[v])swap(u,v);

    for(int i=_log-1;~i;--i)
        if(lvl[par[u][i]]>=lvl[v])u = par[u][i];
    if(u==v)return u;

    for(int i=_log-1;~i;--i)
        if(par[u][i]!=par[v][i])u = par[u][i], v = par[v][i];

    return par[u][0];
}


struct node{
    int color, value;
}v[maxn];

struct query{
    int idx, l, r, _lca;

    bool operator<(const query& x){
        if(block[l]==block[x.l])return r<x.r;
        else return block[l]<block[x.l];
    };

}queries[maxn];

ll qnt[maxn][2], resp = 0;

void check(int x){
    ll c = vis[x]==1?-1:1;
    resp += ll(c*qnt[v[x].value][!v[x].color]), qnt[v[x].value][v[x].color]+=ll(c);
    vis[x]^=1;
}

void solve(int q){
    int curL = queries[1].l, curR = queries[1].l-1;
    for(int i=1;i<=q;++i){
        int l = queries[i].l, r = queries[i].r, _lca = queries[i]._lca,
        idx = queries[i].idx;
        assert(l<=r);
		while (curR < queries[i].r) check(who[++curR]);
		while (curR > queries[i].r) check(who[curR--]);
		while (curL < queries[i].l) check(who[curL++]);
		while (curL > queries[i].l) check(who[--curL]);
        answer[idx] = resp;
        if(_lca!=-1)answer[idx] += ll(qnt[v[_lca].value][!v[_lca].color]);
    }
    //remember OVERFLOW!
}

int main(){_
    cin>>n;
    vector<int>cmp;
    for(int i=1;i<=n;++i)cin>>v[i].color;
    for(int i=1;i<=n;++i){
        cin>>v[i].value;
        cmp.pb(v[i].value);
    }

    sort(all(cmp));
    cmp.erase(unique(all(cmp)),end(cmp));

    for(int i=1;i<=n;++i)v[i].value = lower_bound(all(cmp),v[i].value) - begin(cmp);

    for(int i=1;i<n;++i){
        int u,v;cin>>u>>v;
        g[u].pb(v);g[v].pb(u);
    }

    dfs(1,0);
    // for(int i=0;i<_time;++i)cout<<who[i]<<" \n"[i==_time-1];
    int tam = sqrt(_time);

    for(int i=0;i<_time;++i)block[i] = i/tam;
    
    int q;cin>>q;
    for(int i=1;i<=q;++i){
        int u,v;cin>>u>>v;
        int _lca = lca(u,v);    
        queries[i].idx = i;
        if(_lca!=u&&_lca!=v){
            if(st[u]>st[v])swap(u,v);
            queries[i].l = en[u], queries[i].r = st[v], queries[i]._lca = _lca;
        }else{
            queries[i].l = st[_lca], queries[i].r = (_lca==u?st[v]:st[u]),
            queries[i]._lca = -1;
        }
    }

    sort(queries+1,queries+1+q);
    solve(q);

    for(int i=1;i<=q;++i)cout<<answer[i]<<endl;
}