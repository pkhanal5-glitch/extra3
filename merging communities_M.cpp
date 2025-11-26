// HackerRank — Merging Communities
#include <bits/stdc++.h>
using namespace std;

struct DSU {
    vector<int> p, sz;
    explicit DSU(int n) : p(n+1), sz(n+1, 1) { iota(p.begin(), p.end(), 0); }
    int find(int x) { return p[x] == x ? x : p[x] = find(p[x]); }
    void unite(int a, int b) {
        a = find(a); b = find(b);
        if (a == b) return;
        if (sz[a] < sz[b]) swap(a, b); // why: keep tree shallow
        p[b] = a; sz[a] += sz[b];
    }
    int size(int x) { return sz[find(x)]; }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    if (!(cin >> n >> q)) return 0;
    DSU dsu(n);

    for (int k = 0; k < q; ++k) {
        char op;
        cin >> op;
        if (op == 'M') {
            int i, j; cin >> i >> j;
            dsu.unite(i, j);
        } else if (op == 'Q') {
            int i; cin >> i;
            cout << dsu.size(i) << "\n";
        } else {
            // ignore malformed op if any leftovers present on a line
            string rest; getline(cin, rest);
        }
    }
    return 0;
}
