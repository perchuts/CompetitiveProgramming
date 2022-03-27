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

// upper bound for answer is n*m
// upper bound for answer is m-1
// dp[i][j] = cuts for n = i and m = j
// dp[i][j] = 
int main(){_
    int n,m;cin>>n>>m;
    int ans = 0;
    for(int i=1;i<m;i++)ans += (i*n)%m==0;
    cout<<m-1-ans<<endl;
}