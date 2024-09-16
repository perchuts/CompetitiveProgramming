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



int main(){_
    vector<int>st;
    auto binsearch = [&](int x){
        int l = 0, r = sz(st) - 1, ans = 0;
        while(l<=r){
            int md = l + (r-l+1)/2;
            if(st[md]>x)ans = md, l = md+1;
            else r = md-1;
        }
        return 1LL*(sz(st)-ans);
    };
    int n;cin>>n;
    ll ans = 0;
    for(int i=1;i<=n;i++){
        int x;cin>>x;
        if(i>1)ans+=binsearch(x);
        while(sz(st)&&st.back()<x)st.pop_back();
        st.push_back(x);
    }    
    cout<<ans<<endl;
}