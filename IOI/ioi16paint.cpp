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

bool dp[2*maxn][101], can[2*maxn][101],no[2*maxn],yes[2*maxn],mark[2*maxn];

int pref[2*maxn], prv[2*maxn], nxt[2*maxn];

string solve_puzzle(string s,vector<int> c){

    int n = sz(s), k = sz(c);
    c.insert(begin(c),0);

    int cur = 0;
    for(int i=1;i<=n;++i){
        prv[i] = cur;
        if(s[i-1]=='X')cur = i;
    }
    cur = 0;
    for(int i=n;i>=1;--i){
        nxt[i] = cur;
        if(s[i]=='X')cur = i;
    }

    for(int i=0;i<n;++i){
        pref[i+1] = pref[i];
        if(s[i]=='_')pref[i+1]++;
    }

    for(int j=1;j<=k;++j){
        for(int i=1;i<=n;++i){
            if(j==1){

            }else{

            }
        }
    }

    for(int j=1;j<=k;++j)
        for(int i=1;i<=n;++i)
            cout<<dp[i][j]<<" \n"[i==n];

    int allowed = n;

    for(int j=k;j>=1;--j){//know all sq that can be "_"
        int last = allowed;
        bool flag = 0;
        for(int i=allowed;i>=1;--i){
            if(dp[i][j]){
                for(int w=last;w>i;w--)no[w]=1;
                if(!flag)allowed = i - c[j] - 1, flag = 1;
                last = i;
            }
        }
        if(j==1)for(int i=allowed+1;i>=1;--i)no[i]=1;
    }

    for(int i=1;i<=n;++i)cout<<no[i]<<" \n"[i==n];
    allowed = n;
    for(int j=k;j>=1;--j){//know all sq that can be "x"
        int last = allowed, cur = allowed;
        bool flag = 0;
        for(int i=allowed;i>=1;--i){
            if(dp[i][j]){
                for(int w = min(cur,i);w>i-c[j];--w)yes[w]=1;
                if(!flag)allowed = i - c[j] - 1, flag = 1;
                last = i, cur = i - c[j];
            }
        }
    }
    for(int i=1;i<=n;++i)cout<<yes[i]<<" \n"[i==n];

    for(int i=0;i<n;++i){
        if(s[i]!='.')continue;
        if(yes[i+1]&&no[i+1])s[i]='?';
        else if(yes[i+1])s[i]='X';
        else s[i]='_';
    }

    return s;
}


int main(){
    string s;int k;cin>>s>>k;
    vector<int>c(k);
    for(auto& x:c)cin>>x;
    cout<<solve_puzzle(s,c);
}