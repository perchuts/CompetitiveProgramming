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

struct node{  
    ll cntMenor = 0, cntMaior = 0, qntMenor = 0, qntMaior = 0;
}seg1[4*maxn];

ll alturaFinal[maxn];

void upd(int i,ll x,bool type){
    if(type){
        seg1[i].qntMaior += x, seg1[i].cntMaior++;
    }else{
        seg1[i].qntMenor += x, seg1[i].cntMenor++;
    }
}

void update(int i,int l,int r,int x,int y,ll d,bool type){
    if(x>y)return;
    if(l>y||r<x)return;
    if(x<=l&&r<=y){
        upd(i,d,type);
        return;
    }
    int md = (l+r)/2;
    update(2*i,l,md,x,y,d,type);
    update(2*i+1,md+1,r,x,y,d,type);
}

vector<tuple<ll,ll,int>>pos;

void compute(int i,int l,int r){
    if(l==r){
        auto [coord, p, idx] = pos[l];
        alturaFinal[l] = seg1[i].qntMaior + seg1[i].qntMenor + (seg1[i].cntMaior-seg1[i].cntMenor)*coord;
        return;
    }
    int md = (l+r)/2;
    seg1[2*i].qntMaior += seg1[i].qntMaior, seg1[2*i].qntMenor += seg1[i].qntMenor;
    seg1[2*i].cntMaior += seg1[i].cntMaior, seg1[2*i].cntMenor += seg1[i].cntMenor;
    seg1[2*i+1].qntMaior += seg1[i].qntMaior, seg1[2*i+1].qntMenor += seg1[i].qntMenor;
    seg1[2*i+1].cntMaior += seg1[i].cntMaior, seg1[2*i+1].cntMenor += seg1[i].cntMenor;
    compute(2*i,l,md), compute(2*i+1,md+1,r);
}

pair<ll,ll> seg[4*maxn];//maximo somando, maximo subtraindo

void build(int i,int l,int r){
    if(l==r){
        auto [coord, p, idx] = pos[l];
        seg[i] = {alturaFinal[l]-coord,alturaFinal[l]+coord};
        return;
    }
    int md = (l+r)/2;
    build(2*i,l,md), build(2*i+1,md+1,r);
    seg[i].first = max(seg[2*i].first,seg[2*i+1].first);
    seg[i].second = max(seg[2*i].second,seg[2*i+1].second);
}

ll query(int i,int l,int r,int x,int y,bool type){
    if(l>y||r<x)return -1e18;
    if(x<=l&&r<=y)return (type?seg[i].first:seg[i].second);
    int md = (l+r)/2;
    return max(query(2*i,l,md,x,y,type), query(2*i+1,md+1,r,x,y,type));
}

ll pr[maxn], suf[maxn];

void solve(){
    //unica coisa que importa sao os xi
    int n,m;cin>>n>>m;
    for(int i=0;i<=4*n;++i){
        seg1[i].qntMaior = 0, seg1[i].qntMenor = 0;
        seg1[i].cntMaior = 0, seg1[i].cntMenor = 0;
        seg[i] = {-1e18,-1e18};
    }

    for(int i=1;i<=n;++i)alturaFinal[i] = 0, pr[i] = suf[i] = -1e18;

    pos.clear();

    vector<pair<ll,ll>>v(n);

    pos.pb({-1,-1,-1});
    
    int cnt = 0;

    for(auto& [x,y]:v){
        cin>>x>>y;
        pos.pb({x,y,cnt++});
    }

    sort(all(pos));

    for(int i=1;i<=n;++i){
        auto [coord, p, idx] = pos[i];
        //atualizar pros que tao atras
        int x = lower_bound(all(pos),make_tuple(coord-p,0,0)) - begin(pos);
        // pi - (xi-j)
        // pi - xi + j => pi - xi
        update(1,1,n,x,i-1, p - coord,1);

        x = upper_bound(all(pos),make_tuple(coord+p,inf,inf)) - begin(pos) - 1;
       // pi - (j-xi)
       // pi + xi - j => pi + xi 
        update(1,1,n,i,x, p + coord,0);
    }

    compute(1,1,n);

    build(1,1,n);
    
    cnt = 1;

    pr[0] = suf[n+1] = -1e18;

    string resp(n,'1');

    for(int i=1;i<=n;++i)pr[i] = max(pr[i-1], alturaFinal[i]);
    for(int i=n;i>=1;--i)suf[i] = max(suf[i+1], alturaFinal[i]);

    for(auto [coord,p,idx]:pos){
        int x = lower_bound(all(pos),make_tuple(coord-p,0,0)) - begin(pos);

        ll mx = pr[x-1];

        ckmax(mx, query(1,1,n,x,cnt-1,1)+coord-p);

        x = upper_bound(all(pos),make_tuple(coord+p,inf,inf)) - begin(pos) - 1;

        ckmax(mx, query(1,1,n,cnt,x,0)-p-coord);

        ckmax(mx, suf[x+1]);

        if(mx>m)resp[idx] = '0';

        ++cnt;
    }

    cout<<resp<<endl;

}

int main(){_
    int t;cin>>t;
    while(t--)solve();
}