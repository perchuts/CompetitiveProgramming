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
string s;
int cnt[30],n,k;

bool possible(int x){
    int needed = k*x;
    int sobra = 0;
    for(int i=0;i<='z'-'a';i++){
        needed -= cnt[i]-(cnt[i]%2);
        sobra+=(cnt[i]%2);
    }
    if(x&1)return sobra>=needed&&needed<=k;    
    else return needed<=0;
}



void solve(){
    
    cin>>n>>k;
    cin>>s;
    for(int i=0;i<30;i++)cnt[i]=0;
    for(int i=0;i<n;i++)
        cnt[s[i]-'a']++;
    int l = 1,r=n/k,ans=1;
    while(l<=r){
        int md = l+(r-l)/2;
        if(possible(md)){
            ans = md;
            l = md+1;
        }else{
            r = md-1;
        }
    }
    cout<<ans<<endl;
}


int main(){_
    //freopen("in.in", "r", stdin);
    //freopen("out.out", "w", stdout);
    int t;cin>>t;
    while(t--)solve();
}