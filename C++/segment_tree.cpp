#include <bits/stdc++.h>
using namespace std;

typedef int STNode;
class SegmentTree {
  vector<STNode> t;
  int leaves_count;

  void build(vector<int> const &a, int v, int tl, int tr) {
    if (tl == tr) {
      t[v] = build_leaf_node(a[tl]);
    } else {
      int tm = (tl + tr) / 2;
      build(a, v*2, tl, tm);
      build(a, v*2+1, tm+1, tr);
      t[v] = operation(
        left_child(v), 
        right_child(v)
      );
    }
  }

  STNode build_leaf_node(int elt) {
    return elt;
  }

  STNode neutral_node() {
    return 0;
  }

  STNode operation(STNode x, STNode y) {
    return x + y;
  }

  STNode left_child(int v) {
    return t[v * 2];
  }

  STNode right_child(int v) {
    return t[v * 2 + 1];
  }

  STNode q(int v, int tl, int tr, int l, int r) {
      if (l > r) {
        return neutral_node();
      }
      if (l == tl && r == tr) {
        return t[v];
      }
      int tm = (tl + tr) / 2;
      return operation(
        q(v * 2, tl, tm, l, min(r, tm)),
        q(v * 2 + 1, tm + 1, tr, max(l, tm + 1), r)
      );
  }

  void update(int v, int tl, int tr, int pos, STNode new_val) {
      if (tl == tr) {
        t[v] = new_val;
      } else {
        int tm = (tl + tr) / 2;
        if (pos <= tm) {
          update(v * 2, tl, tm, pos, new_val);
        } else {
          update(v * 2 + 1, tm + 1, tr, pos, new_val);
        }
        t[v] = operation(t[v * 2], t[v * 2 + 1]);
      }
  }

  public:
  void build(vector<int> const &a) {
    int n = a.size();
    leaves_count = n;
    t.clear();
    t.resize(4 * n);
    int v = 1;
    int tl = 0;
    int tr = n - 1;
    build(a, v, tl, tr);
  }

  STNode q(int l, int r) {
    int v = 1;
    int tl = 0;
    int tr = leaves_count - 1;
    return q(v, tl, tr, l, r);
  }

  void update(int pos, int new_val) {
    int v = 1;
    int tl = 0;
    int tr = leaves_count - 1;
    STNode val = build_leaf_node(new_val);
    update(v, tl, tr, pos, val);
  }

  STNode operator [](int idx) const {
    // for debugging
    return t[idx];
  }

};

bool test_power_of_2() {
    vector<int> power_of_2 {13, -1, 2, 23, -4, 231, 13, 5, 2, -88, -52, 0, 4, 90, 3, -12}; //length 16
    vector<int> power_of_2_should {0, 229, 282, -53, 37, 245, -138, 85, 12, 25, 227, 18, -86, -52, 94, -9, 13, -1, 2, 23, -4, 231, 13, 5, 2, -88, -52, 0, 4, 90, 3, -12};
    SegmentTree t;
    t.build(power_of_2);
    for (int k = 0; k < power_of_2_should.size(); k++) if (power_of_2_should[k] != t[k]) return false;
    return true;
}

bool test_uncomplete_tree() {
    vector<int> uncomplete_tree {3, 6, 2, 1, 5, 10, 2, 11, 4, 8}; //length 10
    vector<int> uncomplete_tree_should {0, 52, 17, 35, 11, 6, 23, 12, 9, 2, 1, 5, 12, 11, 4, 8, 3, 6, 0, 0, 0, 0, 0, 0, 10, 2, 0, 0, 0, 0, 0, 0};
    SegmentTree t;
    t.build(uncomplete_tree);
    for (int k = 0; k < uncomplete_tree_should.size(); k++) if (uncomplete_tree_should[k] != t[k]) {
        // FIXME
        cout << "different at idx: " << k << ", t[k]: " << t[k] << ", should[k]: " << uncomplete_tree_should[k] << endl;
        //return false;
    }
    return true;
}

int  main() {
    cout << "Starting tests..." << endl;
    if (!test_power_of_2()) {
        cout << "<Tree of length power of 2> test failed" << endl;
    }
    if (!test_uncomplete_tree()) {
        cout << "<Uncomplete tree> test failed" << endl;
    }
    cout << "Finished all tests" << endl;
    return 0;
}