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
#define inf (int)(2e9+1)
#define mod (int)(1e9+7)

using namespace std;

bool type[10];
int expected[10];
string questions[10];

ii val[maxn];

vector<int>ans,cur;
int main() {
    ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
    int t;cin>>t;
    while(t--){

        int n,m;cin>>n>>m;
        for(int i=0;i<n;i++){
            cin>>expected[i];
        }
        for(int i=0;i<n;i++)cin>>questions[i];
        ans.resize(m),cur.resize(m);

        int best=-1;

        for(int i=0;i<(1<<n);i++){
            int x=i;
            for(int j=0;j<n;j++,x>>=1){
                type[j]=x&1;       
            }

            for(int j=0;j<m;j++){
                val[j]={0,j};
                for(int k=0;k<n;k++){
                    val[j].first+=int(questions[k][j]-'0')*(type[k]?1:-1);
                }
            }

            sort(val,val+m);

            for(int j=0;j<m;j++)
                cur[val[j].second]=j+1;

            int now=0;
            for(int j=0;j<m;j++)
                now+=(j+1)*val[j].first;

            for(int j=0;j<n;j++)
                now+=(type[j]?-expected[j]:expected[j]);

            if(now>best){
                best=now;
                ans=cur;
            }

        }
        for(auto x:ans)cout<<x<<" ";
        cout<<endl;
    }
}   