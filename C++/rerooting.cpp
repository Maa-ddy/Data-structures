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

typedef ll ResultNode;  // the result for the dfs traversal
ResultNode identity = -1e12;
vector<set<pair<ResultNode, int>> downward;
vector<map<int, ResultNode>> reverse_downward;

ResultNode best(ResultNode x, ResultNode y) {
    return max(x, y);
}

ResultNode dfs(int u, int p) {
  ResultNode ans = identity;
  for (int to: g[u]) {
    if (to == p) continue;
    ResultNode child_result = dfs(to, u);
    downward[u].insert({child_result, to});
    reverse_downward[u][to] = child_result;
    ans = best(ans, dpth);
  }
  if (ans < 0 && marked[u]) ans = 0;    // specific to the example
  return 1 + ans;                       // specific to the example
}

void reroot() {
    deque<pii> q;
    q.push({0, -1});
    while (!q.empty()) {
        pii me = q.front(); q.pop();
        ResultNode result = identity;
        if (!depths[me.first].empty()) result = depths[me.first].rbegin()->first;
        if (me.second != -1) {
            ResultNode upward_result = identity;
            if (!downward[me.second].empty()) {
                // detatch me.first from downward
                // calculate result of parent
                // calculate me result
                // insert to me the result
                // insert to parent the previously detatched result
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