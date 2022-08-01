/*
    Seletiva IOI 2019
    Ratinho
    https://codeforces.com/group/2k70zKp2Ci/contest/263343/problem/A
    por Gabriel Lucas

    Não lembro qual é a solução, mas é basicamente difícil
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
const int maxn = 1e5+100;
const int logn = 20;
const int exl = 100010;
 
template<typename X, typename Y> bool ckmin(X& x, const Y& y) { return (y < x) ? (x=y,1):0; }
template<typename X, typename Y> bool ckmax(X& x, const Y& y) { return (x < y) ? (x=y,1):0; }
 
vector<int>g[maxn];
int lvl[maxn], par[maxn][logn], tempo[maxn], cur = 1, color[10*maxn], n, q;
ii box[maxn];
 
void dfs(int u,int p){
    tempo[u] = cur++, lvl[u] = lvl[p]+1, par[u][0] = p;
 
    for(int i=1;i<logn;++i)
        if(par[u][i-1])par[u][i] = par[par[u][i-1]][i-1];
 
    for(auto v:g[u]){
        if(v==p)continue;
        dfs(v,u);
    }
}
 
int lca(int u,int v){
    if(lvl[u]<lvl[v])swap(u,v);
    for(int i=logn-1;~i;--i){
        if(lvl[par[u][i]]>=lvl[v])u = par[u][i];
    }
 
    if(u==v)return u;
 
    for(int i=logn-1;~i;--i){
        if(par[u][i]!=par[v][i])u = par[u][i], v = par[v][i];
    }
 
    return par[u][0];
}
 
int main(){_
    cin>>n;
    int z;
    for(int i=1;i<=n;++i)cin>>box[i].first>>z>>box[i].second>>z;
    sort(box+1,box+1+n);
    stack<ii>st;
    vector<ii>eventos;
    st.push({inf,exl});
    for(int i=1;i<=n;++i){
        auto [x,y] = box[i];
        eventos.pb({x,0}), eventos.pb({y,1});
        while(!st.empty()&&st.top().first<y)st.pop();
        int parent = st.top().second;
        g[parent].pb(i), g[i].pb(parent);
        st.push({y,i});
    }
 
    dfs(exl,0);
    
    sort(all(eventos));
    int act = 0, cor = 1;
    stack<int>cores;cores.push(exl);
 
    for(int i=0;i<=1000000;++i){
        if(act!=2*n&&i==eventos[act].first){
            if(eventos[act].second){
                color[i] = cores.top();
                cores.pop();
            }else{
                cores.push(cor++);
                color[i] = cores.top();
            } 
            ++act;
        }else color[i] = cores.top();
    }
    
    cin>>q;

    while(q--){
        int k;cin>>k;
        vector<int>menor_caixa;
        vector<ii>folha;
        int root = 0;
        for(int i=1;i<=k;++i){
            int x;cin>>x;
            if(color[x]!=exl)menor_caixa.pb(color[x]);
            else root = exl;
        }    
        if(sz(menor_caixa)){
            sort(all(menor_caixa)), menor_caixa.erase(unique(all(menor_caixa)),end(menor_caixa));
            if(root==0)root = menor_caixa.back();
            folha.pb({tempo[menor_caixa.back()],menor_caixa.back()});
            for(int i=0;i<sz(menor_caixa)-1;++i){
                if(box[menor_caixa[i]].second<box[menor_caixa[i+1]].second)
                    folha.pb({tempo[menor_caixa[i]],menor_caixa[i]});
                root = lca(root,menor_caixa[i]);
            }
        }
        sort(all(folha));
        int last = root, resp = 0;
        for(int i=0;i<sz(folha);++i){
            resp += lvl[folha[i].second] - lvl[lca(folha[i].second,last)], last = folha[i].second;
        }
        cout<<resp<<endl;
    }
}