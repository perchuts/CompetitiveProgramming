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
// struct custom_hash {
//     static uint64_t splitmix64(uint64_t x) {
//         // http://xorshift.di.unimi.it/splitmix64.c
//         x += 0x9e3779b97f4a7c15;
//         x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
//         x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
//         return x ^ (x >> 31);
//     }

//     size_t operator()(uint64_t x) const {
//         static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
//         return splitmix64(x + FIXED_RANDOM);
//     }
// };
map<ll,bool>vis;
map<ll,int>cnt;
set<ll>s;
int ans;
ll x;
void dfs(ll v,ll par){
    vis[v] = 1;
    bool ok = 0;
    if(v%x==0){
        if(cnt[v/x]!=0&&!vis[v/x]){
            ok = 1;
            dfs(v/x,v);
        }
    }
    if(cnt[v*x]&&!vis[v*x]){
        ok = 1;
        dfs(v*x,v);
    }
    // cout<<v<<" "<<par<<" "<<cnt[v]<<" "<<cnt[par]<<endl;
    if(v!=par){
        int p = cnt[par];
        cnt[par] = max(cnt[par]-cnt[v],0);
        cnt[v] = max(cnt[v]-p,0);
    }
    // cout<<v<<" "<<par<<" "<<cnt[v]<<" "<<cnt[par]<<endl;
    ans += cnt[v];
}

void solve(){
    int n;cin>>n>>x;
    for(int i=1;i<=n;++i){
        ll y;cin>>y;s.insert(y);
        cnt[y]++;
    }
    for(auto a:s){
        if(!vis[a]){
            dfs(a,a);
        }
    }
    cout<<ans<<endl;
    s.clear();vis.clear();cnt.clear();
    ans = 0;
}


int main(){_
    //freopen("in.in", "r", stdin);
    //freopen("out.out", "w", stdout);
    int t;cin>>t;
    while(t--)solve();
}