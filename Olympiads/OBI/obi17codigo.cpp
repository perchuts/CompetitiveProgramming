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
#define f first
#define s second
using namespace std;

template<typename X, typename Y> bool ckmin(X& x, const Y& y) { return (y < x) ? (x=y,1):0; }
template<typename X, typename Y> bool ckmax(X& x, const Y& y) { return (x < y) ? (x=y,1):0; }


string pref[11],suf[12];
map<string,bool>pr,sf;
int main(){_
    int words;cin>>words;
    pr[""]=1,sf[""]=1,suf[11]="",pref[0]="";
    for(int i=1;i<=words;i++){
        string x;cin>>x;
        for(int j=0;j<10;j++){
            pref[j+1] = pref[j] + x[j]; 
        }
        for(int j=9;~j;j--){
            suf[j+1] = x[j]+suf[j+2]; 
        }
        for(int j=0;j<10;j++){
            if((pr[suf[j+1]]&&sf[pref[j]])){
                cout<<x<<endl;
                return 0;
            }
        }
        for(int j=1;j<=10;j++){
            pr[pref[j]] = 1;
            sf[suf[j]] = 1;
        }
    }    

    cout<<"ok"<<endl;
}