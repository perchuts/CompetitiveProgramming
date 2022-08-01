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
 
int v[maxn];
void solve(){
    int n,m;cin>>n>>m;
    for(int i=1;i<=n;++i)cin>>v[i];
    
    set<pair<ii,int>>s;
 
    int cur = v[1], ini = 1;
 
    for(int i=1;i<=n;++i){
        if(cur>v[i]){
            s.insert({{i-1,ini},cur});
            cur = v[i], ini = i;
        }
    }
 
    s.insert({{n,ini},cur});
    // for(auto [a,b]:s)cout<<"("<<a.second<<", "<<a.first<<") "<<b<<endl;
    // cout<<endl;
    
    while(m--){
        int x,d;cin>>x>>d;
        if(d==0){
            cout<<sz(s)<<" ";
            continue;
        }
        auto eu = s.lower_bound(make_pair(make_pair(x,0),0));
        v[x]-=d;
        auto [p, valor] = *eu;
        auto [r,l] = p;
        if(v[x]<valor){
            auto it = next(eu);
            s.erase(eu);
            int newE = r;
            while(it!=s.end()){
                auto [px, vx] = *it;
                auto [rx,lx] = px;
                if(v[x]>vx)break;
                newE = rx;
                it = next(it);
                s.erase(prev(it));
            }
            if(x!=l)s.insert({{x-1,l},valor});
            s.insert({{newE,x},v[x]});
            // for(auto [a,b]:s)cout<<"("<<a.second<<", "<<a.first<<") "<<b<<endl;
            // cout<<endl;
        }
        cout<<sz(s)<<" ";
    }
    cout<<endl;
    
}
 
 
int main(){_
    //freopen("in.in", "r", stdin);
    //freopen("out.out", "w", stdout);
    int t;cin>>t;
    while(t--)solve();
}