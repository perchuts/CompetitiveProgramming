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


void solve(){
    int n,c;cin>>n>>c;
    vector<int>v(n),cnt(c+1);
    for(auto& x:v)cin>>x;
    for(auto x:v)cnt[x]++;

    for(int i=1;i<=c;++i)cnt[i]+=cnt[i-1];

    bool ok = 1;

    for(int i=c;i>=1;--i){
        if(cnt[i]-cnt[i-1]==0)continue;
        for(int j=2*i-1;j<=c;j+=i){
            if(cnt[j]-cnt[j-i]&&cnt[j/i]-cnt[j/i-1]==0)ok = 0;
        }
        if(cnt[c]-cnt[c-c%i-1]&&cnt[c/i]-cnt[c/i-1]==0)ok = 0;
    }

    cout<<(ok?"Yes":"No")<<endl;
}

int main(){_
    //freopen("in.in", "r", stdin);
    //freopen("out.out", "w", stdout);
    int t;cin>>t;
    while(t--)solve();
}