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
#define lim 35
using namespace std;
 
template<typename X, typename Y> bool ckmin(X& x, const Y& y) { return (y < x) ? (x=y,1):0; }
template<typename X, typename Y> bool ckmax(X& x, const Y& y) { return (x < y) ? (x=y,1):0; }
 
queue<ll>seg[4*maxn];
int lazy[4*maxn];
int n,q,k;
 
ll front(queue<ll>& x){return x.empty()?0LL:x.front();}
 
void updateNode(int i){
    queue<ll>l = seg[2*i], r = seg[2*i+1];
    if(sz(l)<sz(r))swap(l,r);
    while(!seg[i].empty())seg[i].pop();
    while(!l.empty()){
        ll sum = front(l) + front(r);
        l.pop();if(!r.empty())r.pop();
        seg[i].push(sum);
    }
}
 
void push(int i,int l,int r){
    if(k==1)return;
    if(l!=r)lazy[2*i]+=lazy[i],lazy[2*i+1]+=lazy[i];
    for(;lazy[i]&&!seg[i].empty();lazy[i]--)seg[i].pop();
    lazy[i] = 0;
}
 
void update(int i,int l,int r,int x,ll d){
    push(i,l,r);
    if(l>x||r<x)return;
    if(l==r){
        while(!seg[i].empty())seg[i].pop();
        for(;d&&sz(seg[i])<lim;d/=k)seg[i].push(d);
        return; 
    }
    int md = (l+r)/2;
    update(2*i,l,md,x,d);
    update(2*i+1,md+1,r,x,d);
    updateNode(i);
}
 
ll query(int i,int l,int r,int x,int y){
    push(i,l,r);
    if(l>y||r<x)return 0;
    if(x<=l&&r<=y)return front(seg[i]);
    int md = (l+r)/2;
    return query(2*i,l,md,x,y) + query(2*i+1,md+1,r,x,y);
}   
 
void spray(int i,int l,int r,int x,int y){
    if(k==1)return;
    push(i,l,r);
    if(l>y||r<x)return;
    if(x<=l&&r<=y){
        lazy[i]++;
        push(i,l,r);
        return;
    }
    int md = (l+r)/2;
    spray(2*i,l,md,x,y);
    spray(2*i+1,md+1,r,x,y);
    updateNode(i);
}
 
 
int main(){_
    cin>>n>>q>>k;
    for(int i=1;i<=n;i++){
        ll x;cin>>x;
        update(1,1,n,i,x);
    }   
    while(q--){
        int t,a,b;cin>>t>>a>>b;
        if(t==1){
            update(1,1,n,a,1LL*b);
        }else if(t==2){
            if(k!=1)spray(1,1,n,a,b);
        }else{
            cout<<query(1,1,n,a,b)<<endl;
        }
    }
}