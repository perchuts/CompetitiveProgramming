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

bool ckmin(int& a, int b){ return b < a ? a = b, true : false; }
bool ckmax(int& a, int b){ return b > a ? a = b, true : false; }

vector<int>g[maxn];
int a[2] = {3,2};
int x=0;
map<ii,int>cnv;
ii pairs[maxn];

void solve(){
    int n;cin>>n;
    bool ok=1;
    for(int i=1;i<n;i++){
        int a,b;cin>>a>>b;
        g[a].pb(b);
        g[b].pb(a);
        pairs[i] = {max(a,b),min(a,b)};
    }
    int start;
    for(int i=1;i<=n;i++){
        if(sz(g[i])>2)ok=0;
        if(sz(g[i])==1)start = i;
    }
    if(!ok){
        cout<<"-1"<<endl;
    }else{
        int prv=-1;
        for(int i=1;i<n;i++){
        int nxt = g[start][0];
        if(nxt==prv)nxt = g[start][1];
        cnv[{max(nxt,start),min(nxt,start)}]=a[x];
        x^=1;
        prv = start;
        start = nxt;
        }
        for(int i=1;i<n;i++){
        cout<<cnv[pairs[i]]<<" ";
        }
        cout<<endl;
    }
    for(int i=1;i<=n;i++)g[i].clear();
    x=0;cnv.clear();
}


int main(){_
    //freopen("in.in", "r", stdin);
    //freopen("out.out", "w", stdout);
    int t;cin>>t;
    while(t--)solve();
}