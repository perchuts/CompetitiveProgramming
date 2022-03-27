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

struct point{
    int x, y, ind;
}v[20011];

int idx[20011],le[20011],ri[20011], y[20011];
int main(){_
    int n,t;cin>>n>>t;
    vector<int>cx,cy;

    for(int i=1;i<=n;++i){
        cin>>v[i].x>>v[i].y;
        cx.pb(v[i].x);cy.pb(v[i].y);
        v[i].ind = i;
    }
                                                                                    
    sort(all(cx));sort(all(cy));

    for(int i=1;i<=n;++i){
        v[i].x = lower_bound(all(cx),v[i].x) - begin(cx);
        v[i].y = lower_bound(all(cy),v[i].y) - begin(cy);
    }

    sort(v+1,v+1+n, [&](const point &a, const point &b){
        return a.x < b.x;
    });

    for(int i=1;i<=n;++i)idx[i] = v[i].ind, y[i] = v[i].y;

    for(int i=1;i<=n;++i){
        for(int j=1;j<i;++j){
            if(y[j]>y[i])ri[i]++;
            if(y[j]<y[i])le[i]++;
        }
    }
    
    int best = inf, minx = -1, miny = -1;

    for(int i=1;i<=n;++i){
        int pr[20011]={};
        for(int j=1;j<i;++j)pr[y[j]]++;
        for(int i=1;i<=n;++i)pr[i]+=pr[i-1];
        int l = 0;
        for(int j=i+1;j<=n;++j){
            if(y[j]<y[i]){
                ++l;continue;
            }
            int cur = j - ri[j] - l - pr[y[j]];
            if(cur<best&&cur>=t){
                best = cur;
                minx = i, miny = j;
            }
            if(best==t)break;
        }    
        if(best==t)break;
        int r = 0;
        for(int j=i+1;j<=n;++j){
            if(y[j]>y[i]){
                ++r;continue;
            }
            int cur = j - r - le[j] - pr[n] + pr[y[j]];
            if(cur<best&&cur>=t){
                best = cur;
                minx = i, miny = j;
            }
            if(best==t)break;
        }   
        if(best==t)break;
    }
    cout<<idx[minx]<<" "<<idx[miny]<<endl;
}