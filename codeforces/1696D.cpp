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
 
int seg[4*maxn][2];
 
void build(int n){
    for(int i=1;i<=4*n;++i)seg[i][0] = seg[i][1] = inf;
}
 
void update(int i,int l,int r,int x,int d,int t){
    if(l>x||r<x)return;
    if(l==r){
        seg[i][t] = d;
        return;
    }
    int md = (l+r)/2;
    update(2*i,l,md,x,d,t), update(2*i+1,md+1,r,x,d,t);
    seg[i][t] = min(seg[2*i][t],seg[2*i+1][t]);
}
int query(int i,int l,int r,int x,int y,int t){
    if(l>y||r<x)return inf;
    if(x<=l&&r<=y)return seg[i][t];
    int md = (l+r)/2;
    return min(query(2*i,l,md,x,y,t), query(2*i+1,md+1,r,x,y,t));
}
 
int p_maior[maxn], p_menor[maxn];
 
void solve(){
    int n;cin>>n;
    vector<int>v(n);
    for(auto& x:v)cin>>x;
    if(n==1){
        cout<<0<<endl;
        return;
    }
 
    vector<ii>tmp = {{inf,1}};
 
    for(int i=1;i<=n;++i){
        while(!tmp.empty()&&tmp.back().first<v[i-1])tmp.pop_back();
        p_maior[i] = tmp.back().second;
        tmp.pb({v[i-1],i});
    }
    tmp = {{0,1}};
    for(int i=1;i<=n;++i){
        while(!tmp.empty()&&tmp.back().first>v[i-1])tmp.pop_back();
        p_menor[i] = tmp.back().second;
        tmp.pb({v[i-1],i});
    }
    build(n);
 
    vector<ii>subindo = {{inf,0}}, descendo = {{0,0}};
 
    update(1,1,n,1,0,0), update(1,1,n,1,0,1);
    descendo.pb({v[0],1}), subindo.pb({v[0],1});
 
    for(int i=2;i<=n;++i){
        int resp;
        if(v[i-2]>v[i-1]){
            resp = query(1,1,n,p_menor[i],i-1,0) + 1;
            while(!descendo.empty()&&descendo.back().first>v[i-1]){
                update(1,1,n,descendo.back().second,inf,1);
                descendo.pop_back();
            }
        }else{
            resp = query(1,1,n,p_maior[i],i-1,1) + 1;
            while(!subindo.empty()&&subindo.back().first<v[i-1]){
                update(1,1,n,subindo.back().second,inf,0);
                subindo.pop_back();
            }
        }
        descendo.pb({v[i-1],i}), subindo.pb({v[i-1],i});
        update(1,1,n,i,resp,0), update(1,1,n,i,resp,1);
        if(i==n)cout<<resp<<endl;
    }
}
 
 
int main(){_
    int t;cin>>t;
    while(t--)solve();
}