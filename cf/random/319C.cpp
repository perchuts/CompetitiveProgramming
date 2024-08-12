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
 
template<typename X, typename Y> bool ckmin(X& x, const Y& y) { return (y < x) ? (x=y,1):0; }
template<typename X, typename Y> bool ckmax(X& x, const Y& y) { return (x < y) ? (x=y,1):0; }
 
ll a[maxn], b[maxn];
 
long double interceptX(pair<ll,ll>pi, pair<ll,ll>pj){
    return (pi.second - pj.second)/(long double)(pj.first-pi.first);
}
 
int main(){_
    int n;cin>>n;
    for(int i=1;i<=n;++i)cin>>a[i];
    for(int i=1;i<=n;++i)cin>>b[i];
    ll resp = 0;
    deque<pair<ll,ll>>dq;
    dq.push_back({-b[1], 0});
    for(int i=2;i<=n;++i){
        //quero a melhor resposta pra x = a[i]
        ll l = 0, r = ll(sz(dq) - 1), best = 0, dpi;
        pair<ll,ll>me;
        if(r==0)dpi = dq[0].second + dq[0].first*a[i];
        else{
            while(l<=r){
                ll md = l + (r-l+1ll)/2;
                ll lx, rx;
                if(md==0)lx = -inf, rx = interceptX(dq[md],dq[md+1]);
                else if(md==sz(dq)-1)lx = interceptX(dq[md],dq[md-1]), rx = inf;
                else lx = interceptX(dq[md-1],dq[md]), rx = interceptX(dq[md], dq[md+1]);
                if(lx<=a[i]&&a[i]<=rx){
                    best = md;break;
                }else if(a[i]<lx)r = md - 1ll;
                else l = md + 1ll;
            }
            dpi = dq[best].second + dq[best].first*a[i];
        }
        me = {-b[i], dpi};
        while(sz(dq)>=2&&interceptX(me,dq[sz(dq)-1])<=interceptX(dq[sz(dq)-1],dq[sz(dq)-2]))dq.pop_back();
        dq.push_back(me);
        resp = -dpi;
    }
    cout<<resp<<endl;
}