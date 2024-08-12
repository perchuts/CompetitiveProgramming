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

ll a[2*maxn], b[2*maxn];
int n;
void solve(){
    cin>>n;
    ii choices[4]={{1,1},{1,n},{n,1},{n,n}};
    vector<pair<ll,int>>up,down;
    for(int i=1;i<=n;++i){
        cin>>a[i];
        up.pb({a[i],i});
    }
    for(int i=1;i<=n;++i){
        cin>>b[i];
        down.pb({b[i],i});
    }
    sort(all(up));sort(all(down));
    ll ans = min(abs(a[1]-b[1])+abs(a[n]-b[n]),abs(a[1]-b[n])+abs(a[n]-b[1]));//usando 2 arestas    
    //usando 3 arestas
    for(int i=0;i<4;++i){
        int ax = choices[i].first, bx = choices[i].second;
        ll cur = abs(a[ax]-b[bx]);
        int lefta = choices[4-i-1].first, leftb = choices[4-i-1].second;
        int best = lower_bound(all(down),make_pair(a[lefta],0)) - begin(down);
        if(best==n)best--;
        if(best!=0){
            if(abs(down[best-1].first-a[lefta])<abs(down[best].first-a[lefta]))best--;
        }
        cur += abs(down[best].first - a[lefta]);
        best = lower_bound(all(up),make_pair(b[leftb],0)) - begin(up);
        if(best==n)best--;
        if(best!=0){
            if(abs(up[best-1].first-b[leftb])<abs(up[best].first-b[leftb]))best--;
        }
        cur += abs(up[best].first - b[leftb]);
        ckmin(ans,cur);
    }
    int a1 = lower_bound(all(down),make_pair(a[1],0)) - begin(down);
    int an = lower_bound(all(down),make_pair(a[n],0)) - begin(down);
    int b1 = lower_bound(all(up),make_pair(b[1],0)) - begin(up);
    int bn = lower_bound(all(up),make_pair(b[n],0)) - begin(up);
    a1=min(n-1,a1), an = min(n-1,an), b1 = min(n-1,b1), bn = min(n-1,bn);
    if(a1!=0){
        if(abs(down[a1-1].first-a[1])<abs(down[a1].first-a[1]))a1--;
    }
    if(an!=0){
        if(abs(down[an-1].first-a[n])<abs(down[an].first-a[n]))an--;
    }
    if(b1!=0){
        if(abs(up[b1-1].first-b[1])<abs(up[b1].first-b[1]))b1--;
    }
    if(bn!=0){
        if(abs(up[bn-1].first-b[n])<abs(up[bn].first-b[n]))bn--;
    }
    ans = min(ans,abs(a[1]-down[a1].first)+abs(a[n]-down[an].first)+abs(b[1]-up[b1].first)+abs(b[n]-up[bn].first));
    cout<<ans<<endl;

}


int main(){_
    //freopen("in.in", "r", stdin);
    //freopen("out.out", "w", stdout);
    int t;cin>>t;
    while(t--)solve();
}