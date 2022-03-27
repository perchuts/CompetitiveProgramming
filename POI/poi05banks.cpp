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
//[pos][number]
//[1e6][10] => 1e7 ok!;
int freq[10001][10];
int possible[10][10][10][10];
int main(){_
    int n;cin>>n;

    for(int i=1;i<=n;i++){
        int cursz;cin>>cursz;
        string s;cin>>s;
        for(int j=0;j<=9;j++){
            freq[cursz-1][j] = (int(s[cursz-1]-'0')==j ? cursz-1 : -1);
            for(int k=cursz-2;k>=0;k--){
                if(int(s[k]-'0')==j)freq[k][j] = k;
                else freq[k][j] = freq[k+1][j];
            }
        }
        for(int i=0;i<=9;i++){
         for(int j=0;j<=9;j++){
            for(int k=0;k<=9;k++){
                for(int w=0;w<=9;w++){
                        bool ok = 1;
                        int it = freq[0][i];
                        if(it==-1)ok=0;
                        if(i!=j&&ok)it = freq[it][j];
                        if(it==-1)ok=0;
                        if(j!=k&&ok)it = freq[it][k];
                        if(it==-1)ok=0;
                        if(k!=w&&ok)it = freq[it][w];
                        if(it==-1)ok=0;
                        possible[i][j][k][w]|=(!ok);
                    }
                }
            }
        }
    }
    int ans = 0;
    for(int i=0;i<=9;i++)
        for(int j=0;j<=9;j++)
            for(int k=0;k<=9;k++)
                for(int w=0;w<=9;w++)
                    ans+=!possible[i][j][k][w];
    cout<<ans<<endl;
}