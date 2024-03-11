#define FASTIO ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
typedef pair<ll, ll> pll;
typedef pair<int, int> pii;
#define mp make_pair
#define pb push_back
#define sz(v) ((int)v.size())
#define all(v) v.begin(), v.end()
#define parseArray(A, n) for ( ll K = 0; K < n; K++) { cin >> A[K]; }
#define debug(c) cerr << "dbg>>> "; for (auto e: c) cerr << e << " "; cerr << endl;
ll modInverse(ll a, ll b){ return 1<a ? b - modInverse(b%a, a)*b/a : 1; }
ll gcd(ll a, ll b){ return b?gcd(b, a % b):a; }
ll lcm(ll a, ll b){ return (a*b)/gcd(a, b); }
#define PI 3.14159265358979323846
#define uniq(v) v.resize(distance(v.begin(), unique(all(v))))
#define low_b(v, x) lower_bound(all(v), x) - v.begin()
#define upp_b(v, x) upper_bound(all(v), x) - v.begin()
vector<vector<int>> read_tree(int n) {
  vector<vector<int>> tree;
  tree.resize(n);
  for (int k = 0; k < n - 1; k++) {
    int from, to; cin >> from >> to;
    tree[from - 1].pb(to - 1);
    tree[to - 1].pb(from - 1);
  }
  return tree;
}

ll n, m;
vector<vector<int>> g;
typedef ll ResultNode;                                              // CHANGEME
ResultNode identity = -1e12;

class ResultsContainer {                                            // CHANGEME
    set<pair<ResultNode, int>> values;
    map<int, ResultNode> reverse_values;
    bool marked; // specific

    public:

    ResultsContainer(bool is_marked) {
        marked = is_marked; // specific
    }

    ResultsContainer() {
        marked = false; // specific
    }
    
    void insert(int to, ResultNode v) {
        values.insert({v, to});
        reverse_values[to] = v;
    }

    ResultNode remove(int id) {
        ResultNode removed = reverse_values[id];
        values.erase(removed);
        return removed;
    }

    ResultNode merged_value() {
        if (values.empty()) return identity;
        ResultNode ans = values.rbegin()->second;
        if (ans < 0 && marked) { // specific
            return 0;
        }
        return ans;
    }

};

vector<ResultsContainer> results;
#define operation(x, y) max(x, y)                                   // CHANGEME

void dfs(int u, int p) {
  for (int to: g[u]) {
    if (to == p) continue;
    dfs(to, u);
    ResultNode child_result = results[to].merged_value();
    results[u].insert(to, child_result);
  }
}

ResultNode detatch(int detatchable, int detatchee) {
    return results[detatchable].remove(detatchee);
}

void reattatch(int reattatchable, int reattatchee_idx, ResultNode reattatchee) {
    results[reattatchable].insert(reattatchee_idx, reattatchee);
}

void reroot() {
    deque<pii> q;
    q.push({0, -1});
    while (!q.empty()) {
        pii me = q.front(); q.pop();
        ResultNode result = identity;
        if (!results[me.first].empty()) result = results[me.first].rbegin()->first; // CHANGEME
        if (me.second != -1) {
            ResultNode upward_result = identity;
            ResultNode detatched = detatch(me.second, me.first);
            ResultNode value_from_detatched_parent = results.merged_value();
            result = operation(result, value_from_detatched_parent);
            reattatch(me.second, me.first, detatched);
            
            if (upward_result < 0) { // specific
                if (marked[me.second]) upward_result = 1;
            }
            result = operation(result, 1 + upward_result);  // CHANGEME
        }
    }
}


void solve(int case_idx) {
  cin >> n >> m;
  marked.clear(); marked.resize(n);
  for (int k = 0; k < n; k++) marked[k] = 0;
  depths.clear(); depths.resize(n);
  for (int k = 0; k < m; k++) {
    ll x; cin >> x;
    marked[x - 1] = 1;
  }
  g = read_tree(n);
  dfs(0, -1);
  queue<pii> q;
  q.push({0, -1});
  ll ans = 1e12;
  while (!q.empty()) {
    pii me = q.front(); q.pop();
    ll dpth = -1e12;
    if (!depths[me.first].empty()) dpth = depths[me.first].rbegin()->first;
    if (me.second != -1) {
      ll upward_dpth = -1e12;
      if (!depths[me.second].empty()) {
        auto biggest = depths[me.second].rbegin();
        if (biggest->second == me.first ) {
          if (sz(depths[me.second]) > 1) {
            biggest++;
            upward_dpth = 1 + (biggest->first);
          }
        } else {
          upward_dpth = 1 + (biggest->first);
        }
      }
      if (upward_dpth < 0) {
        if (marked[me.second]) upward_dpth = 1;
      }
      dpth = max(dpth, upward_dpth);
      depths[me.first].insert({upward_dpth, me.second});
    }
    ans = min(ans, dpth);
    for (int to: g[me.first]) {
      if (to == me.second) continue;
      q.push({to, me.first});
    }
  }
  cout << max(ans, 0ll) << "\n";
}

int main(){
  FASTIO;
  ll t; cin >> t;
  for (int k = 0; k < t; k++) solve(k + 1);
  return 0;
}