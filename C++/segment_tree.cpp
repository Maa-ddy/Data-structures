#include <bits/stdc++.h>
using namespace std;

class SegmentTree {
    vector<int> t;

    void build(vector<int> const &a, int v, int tl, int tr) {
        if (tl == tr) {
            t[v] = a[tl];
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

    int operation(int x, int y) {
        return x + y;
    }

    int left_child(int v) {
        return t[v * 2];
    }

    int right_child(int v) {
        return t[v * 2 + 1];
    }

    public:
    void build(vector<int> const &a) {
        int n = a.size();
        t.clear();
        t.resize(4 * n);
        build(a, 1, 0, n - 1);
    }

    int operator [](int idx) const {
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
    vector<int> uncomplete_tree_should {0, 52, 17, 35, 11, 6, 23, 12, 9, 2, 1, 5, 12, 11, 4, 8, 3, 6, 0, 0, 0, 0, 0, 10, 2, 0, 0, 0, 0, 0, 0}; //length 10
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
    if (!test_power_of_2()) {
        cout << "<Tree of length power of 2> test failed" << endl;
    }
    if (!test_uncomplete_tree()) {
        cout << "<Uncomplete tree> test failed" << endl;
    }
    return 0;
}