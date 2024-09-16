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
const int maxn = 1e5+100;
const int _log = 20;
template<typename X, typename Y> bool ckmin(X& x, const Y& y) { return (y < x) ? (x=y,1):0; }
template<typename X, typename Y> bool ckmax(X& x, const Y& y) { return (x < y) ? (x=y,1):0; }
vector<int>visited;
int lvl[10*maxn], par[10*maxn][_log], current = 1, parent = 0;
char letter[10*maxn];
void Init(){
    visited.pb(0);
    //model to a graph:
    //Every node represents a TypeLetter command.
    //Then we will have a tree.
    //TypeLetter will add a path from current node to a new node and we
    //will walk to this new node.
    //UndoCommands will return us to U-th last node visited 
    //GetLetter asks us for P-th first node in the path from root to current node.
    //To keep track of visited nodes, we can just use a vector.
    //we cant answer queries offline :sad:
    //its rather simple: binary lifting to answer GetLetter
    //to do this, we will only need an additional lvl array.
}

void TypeLetter(char l){
    cout<<"typing letter "<<l<<"after "<<parent<<endl;
    letter[current] = l;
    par[current][0] = parent, lvl[current] = lvl[parent]+1;
    for(int i=1;i<_log;++i){
        if(par[current][i-1])par[current][i] = par[par[current][i-1]][i-1];
    }
    visited.pb(current);
    parent = current++;
}

void UndoCommands(int u){
    int commandsDone = sz(visited);
    int now = visited[commandsDone-u];
    parent = par[now][0];
    visited.pb(parent);
    cout<<"undoing "<<u<<" commands and returning to node "<<parent<<endl;
}

char GetLetter(int p){
    int target = lvl[parent] - p + 1;
    cout<<"currently at node "<<parent<<" and i want to go up by "<<target<<endl;
    int cur = parent;
    for(int i=_log-1;~i;--i){
        if(lvl[par[cur][i]]>target)cur = par[cur][i];
    }
    cur = par[cur][0];
    cout<<"found "<<cur<<"as target"<<endl;
    return letter[cur];
}

int main() {
  Init();

  int tmp,cmd_num;
  tmp = scanf("%d", &cmd_num);
  assert(tmp == 1);

  int i;
  for (i = 0; i < cmd_num; i++) {
    char cmd;
    tmp = scanf(" %c", &cmd);
    assert(tmp == 1);
    if (cmd == 'T') {
      char letter;
      tmp = scanf(" %c", &letter);
      assert(tmp == 1);
      TypeLetter(letter);
    }
    else if (cmd == 'U') {
      int number;
      tmp = scanf("%d", &number);
      assert(tmp == 1);
      UndoCommands(number);
    }
    else if (cmd == 'P') {
      int index;
      char letter;
      tmp = scanf("%d", &index);
      assert(tmp == 1);
      letter = GetLetter(index);
      printf("%d %c\n", letter);
    }
  }
  
  puts("Let's test for cheating!!");

  return 0;

}