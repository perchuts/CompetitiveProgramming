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
const int maxn = 3e5+100;

template<typename X, typename Y> bool ckmin(X& x, const Y& y) { return (y < x) ? (x=y,1):0; }
template<typename X, typename Y> bool ckmax(X& x, const Y& y) { return (x < y) ? (x=y,1):0; }


void solve(){
    int n,a,b,c;cin>>n>>a>>b>>c;
    int x = 5e5,y=5e5,z=5e5;
    for(int i=0;i<=a;++i){
        int j = a - i,  k = c - i;
        if(min(j,k)>=0&&j+k==b){
            if(x+y+z>i+j+k)x = i,y = j, z = k;
        }
    }
    if(x+y+z>=n)cout<<"NO"<<endl;
    else{

        vector<ii>edges;

        int cur = 4;

        auto constroi = [&] (int source, int dest, int qtd){
            if(qtd==1)edges.pb({source,dest});
            else{
                edges.pb({source,cur});
                for(int i=0;i<qtd-2;++i){
                    edges.pb({cur,cur+1});
                    ++cur;
                }
                edges.pb({cur++,dest});
            }
        };
        if(x==0){
            constroi(2,1,y), constroi(3,1,z);
        }else if(y==0){
            constroi(1,2,x), constroi(3,2,z);
        }else if(z==0){
            constroi(1,3,x), constroi(2,3,y);
        }else{
            constroi(1,2,x+y);
            int centro = edges[x-1].second;
            constroi(3,centro,z);
        }
        while(cur!=n+1)edges.pb({1,cur++});
        cout<<"YES"<<endl;
        for(auto [x,y]:edges)cout<<x<<" "<<y<<endl;
    }
}


int main(){_
    //freopen("in.in", "r", stdin);
    //freopen("out.out", "w", stdout);
    int t;cin>>t;
    while(t--)solve();
}