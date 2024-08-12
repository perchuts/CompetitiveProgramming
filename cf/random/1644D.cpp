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
#define mod 998244353 //998244353
#define _ ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);

using namespace std;

template<typename X, typename Y> bool ckmin(X& x, const Y& y) { return (y < x) ? (x=y,1):0; }
template<typename X, typename Y> bool ckmax(X& x, const Y& y) { return (x < y) ? (x=y,1):0; }

bool col[2*maxn], row[2*maxn];
void solve(){
    ll n,m,k,q;cin>>n>>m>>k>>q;
    vector<ii>queries(q);
    for(auto& [a,b]:queries)cin>>a>>b;
    reverse(all(queries));
    ll ans = 1ll,maxa=0,maxb=0,sumr=0,sumc=0;
    for(auto [a,b]:queries){
        if((!row[a]||!col[b])&&(sumr!=n&&sumc!=m))ans = (ans*k)%mod;
        if(!row[a])row[a] = 1,sumr++;
        if(!col[b])col[b] = 1,sumc++;
        ckmax(maxa,a);ckmax(maxb,b);
    }
    for(int i=1;i<=max(maxa,maxb);++i)col[i] = row[i] = 0;
    cout<<ans<<endl;
}


int main(){_
    //freopen("in.in", "r", stdin);
    //freopen("out.out", "w", stdout);
    int t;cin>>t;
    while(t--)solve();
}