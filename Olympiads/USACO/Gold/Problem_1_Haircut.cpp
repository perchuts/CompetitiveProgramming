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
vector<int>v[maxn];
ll bit[maxn],n;

void insert(int x,ll delta=1LL){
    while(x<=n){
        bit[x]+=delta;
        x+=x&(-x);
    }
}

ll query(int x){
    int ans = 0LL;
    while(x){
        ans+=bit[x];
        x-=x&(-x);
    }
    return ans;
}

int main(){_
    freopen("haircut.in", "r", stdin);
    freopen("haircut.out", "w", stdout);
    cin>>n;
    for(int i=1,x;i<=n;i++){
        cin>>x;
        v[x].pb(i);
        insert(i);
    }
    ll curans=0;
    cout<<curans<<endl;
    for(int i=0;i<n-1;i++){
        for(auto x:v[i])insert(x,-1);
        for(auto x:v[i])curans+=query(x);
        cout<<curans<<endl;
    }

}