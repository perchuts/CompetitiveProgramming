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
 
int start[50],m,n,l;
map<ii,set<int>>adj;//regioes que compartilham uma mesma aresta
vector<int>inside[500];// quais regioes o meu vertice faz parte
vector<ii>edges[500];//arestas de uma regiao
 
ll dist[500][500];//dist[i][j] = distancia da regiao i para a regiao j
 
int calcula(int x){
    int resp = 0;
    for(int i=1;i<=l;i++){
        int mn = inf;
        for(auto st:inside[start[i]]){
            ckmin(mn,dist[st][x]);
        }
        resp += mn;
    }
    return resp;
}
 
 
int main(){_
    cin>>m>>n>>l;
    for(int i=1;i<=l;i++)cin>>start[i];
    for(int i=1;i<=m;i++){//le o input
        int x;cin>>x;
        int first,last;
        for(int j=1;j<=x;j++){
            int cur;cin>>cur;
            if(j==1)first = cur;
            if(j>1)adj[{max(last,cur),min(last,cur)}].insert(i);
            if(j>1)edges[i].pb({max(last,cur),min(last,cur)});
            inside[cur].pb(i); 
            last = cur;
        }
        adj[{max(last,first),min(last,first)}].insert(i);
        edges[i].pb({max(last,first),min(last,first)});
    }
    ///precalcula a distancia entre todos os pares de regioes
    for(int i=1;i<=m;i++)
        for(int j=1;j<=m;j++)
            dist[i][j] = inf;
    for(int u=1;u<=m;u++){
         for(auto e:edges[u]){
             for(auto v:adj[e]){
                 dist[u][v] = u!=v;
            }
        }
    }
    for(int k=1;k<=m;k++)
        for(int i=1;i<=m;i++)
            for(int j=i+1;j<=m;j++)
                if(dist[i][k]+dist[k][j]<dist[i][j])dist[i][j] = dist[j][i] = dist[i][k] + dist[k][j];          
    int ans = inf;
    int region = 0;
    for(int i=1;i<m;i++){//tenta todas as regioes como ponto de encontro
        if(ckmin(ans,calcula(i)))region = i;
    }
    cout<<ans<<endl<<region;
}