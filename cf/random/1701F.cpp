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
const int n = 2e5; 
 
template<typename X, typename Y> bool ckmin(X& x, const Y& y) { return (y < x) ? (x=y,1):0; }
template<typename X, typename Y> bool ckmax(X& x, const Y& y) { return (x < y) ? (x=y,1):0; }
 
ll lazy[4*maxn], bit[maxn];
pair<ll,ll> seg[4*maxn];
bool presente[maxn];
 
void insert(int x,ll d){
    for(;x<=n;x+=x&(-x))bit[x] += d;
}
 
ll query(int x){
    ll ans = 0;
    while(x){
        ans += bit[x];
        x -= x&(-x);
    }
    return ans;
}
 
void push(int i,int l,int r){
    seg[i].second += lazy[i], seg[i].first += lazy[i]*(query(r)-query(l-1));
    if(l!=r)lazy[2*i] += lazy[i], lazy[2*i+1] += lazy[i];
    lazy[i] = 0;
}
 
void update(int i,int l,int r,int x,int y,int d){
    push(i,l,r);
    if(l>y||r<x)return;
    if(x<=l&&r<=y){
        lazy[i] += d;
        push(i,l,r);
        return;
    }
    int md = (l+r)/2;
    update(2*i,l,md,x,y,d), update(2*i+1,md+1,r,x,y,d);
    seg[i].first = seg[2*i].first + seg[2*i+1].first;
}
 
void update(int i,int l,int r,int x){
    push(i,l,r);
    if(l>x||r<x)return;
    if(l==r){
        presente[x]^=1;
        seg[i].first = (presente[x]?seg[i].second:0);
        return;
    }
    int md = (l+r)/2;
    update(2*i,l,md,x), update(2*i+1,md+1,r,x);
    seg[i].first = seg[2*i].first + seg[2*i+1].first;
}
 
ll query(int i,int l,int r,int x,int y){
    push(i,l,r);
    if(l>y||r<x)return 0;
    if(x<=l&&r<=y){
        return seg[i].first;
    }
    int md = (l+r)/2;
    return query(2*i,l,md,x,y) + query(2*i+1,md+1,r,x,y);
}
 
int main(){_
    int q,d;cin>>q>>d;
    ll ans = 0;
    for(int i=1;i<=q;++i){
        int x;cin>>x;
        if(presente[x]){
            ll exl = query(1,1,n,x,x);
            ans -= (exl*(exl-1))/2;
            insert(x,-1);
            if(x!=n)update(1,1,n,min(n,x+1),min(n,x+d),-1); 
            update(1,1,n,x);
            ans -= (x!=n?query(1,1,n,min(x+1,n),min(x+d,n)):0);
        }else{
            ans += (x!=n?query(1,1,n,min(x+1,n),min(x+d,n)):0);
            if(x!=n)update(1,1,n,min(x+1,n),min(x+d,n),1);
            update(1,1,n,x), insert(x,1);
            ll exl = query(1,1,n,x,x);
            ans += (exl*(exl-1))/2;
        }
        cout<<ans<<endl;
    }
}