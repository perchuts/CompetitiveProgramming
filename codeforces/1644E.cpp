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

ll sufd[2*maxn],sufr[2*maxn];
void solve(){
    ll n;cin>>n;
    string s;cin>>s;
    int m = sz(s);
    ll ans = n*n;
    for(int i=m-1;~i;--i)sufd[i]=sufd[i+1]+(s[i]=='D'),sufr[i]=sufr[i+1]+(s[i]=='R');
    int i = 0;
    while(i<m&&s[i]==s[0])ans-=n-1,i++;
    if(i==m)ans = n;
    for(;i<m-1;++i){
        ans -= s[i]=='R'?sufd[i]:sufr[i];
    }
    cout<<ans<<endl;
    for(int i=0;i<m;++i)sufd[i] = sufr[i] = 0;
}


int main(){_
    //freopen("in.in", "r", stdin);
    //freopen("out.out", "w", stdout);
    int t;cin>>t;
    while(t--)solve();
}