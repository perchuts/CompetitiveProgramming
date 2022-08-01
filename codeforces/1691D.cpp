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
 
ll v[maxn], pr[maxn], suf[maxn];
ii limits[maxn];
pair<ll,ll>seg[4*maxn];
int n;
void build(int i=1,int l=1,int r=n){
    if(l==r){
        seg[i] = {pr[l],suf[l]};
        return;
    }
    int md = (l+r)/2;
    build(2*i,l,md), build(2*i+1,md+1,r);
    seg[i].first = min(seg[2*i].first,seg[2*i+1].first);
    seg[i].second = min(seg[2*i+1].second,seg[2*i].second);
}
 
ll query(int i,int l,int r,int x,int y,bool mode){
    if(l>y||r<x)return 1e18;
    if(x<=l&&r<=y)return (mode?seg[i].second:seg[i].first);
    int md = (l+r)/2;
    return min(query(2*i,l,md,x,y,mode),query(2*i+1,md+1,r,x,y,mode));
}
 
void solve(){
    cin>>n;
    for(int i=1;i<=n;++i)cin>>v[i];
    stack<pair<ll,int>>st;
    for(int i=1;i<=n;++i){
        while(!st.empty()&&st.top().first<=v[i])st.pop();
        limits[i].first = (st.empty()?0:st.top().second);
        st.push({v[i],i});
    }
    while(!st.empty())st.pop();
    for(int i=n;i>=1;--i){
        while(!st.empty()&&st.top().first<=v[i])st.pop();
        limits[i].second = (st.empty()?n+1:st.top().second);
        st.push({v[i],i});
    }
    suf[n+1] = 0;
    for(int i=1;i<=n;++i)pr[i] = pr[i-1] + v[i];
    for(int i=n;i>=1;--i)suf[i] = suf[i+1] + v[i];
    build();
    bool ok = 1;
    for(int i=1;i<=n;++i){
        ll le = (i==1?0:pr[i-1]-query(1,1,n,max(1,limits[i].first),i-1,0)),
        ri = (i==n?0:suf[i+1]-query(1,1,n,i+1,min(n,limits[i].second),1));
        if(limits[i].first==0)ckmax(le,pr[i-1]);
        if(limits[i].second==n+1)ckmax(ri,suf[i+1]);
        // cout<<le<<" "<<ri<<endl;
        if(le+ri>0)ok = 0;
    }
    cout<<(ok?"YES":"NO")<<endl;
}
 
 
int main(){_
    //freopen("in.in", "r", stdin);
    //freopen("out.out", "w", stdout);
    int t;cin>>t;
    while(t--)solve();
}