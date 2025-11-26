// Kruskal (MST): Really Special Subtree — HackerRank
#include <bits/stdc++.h>
using namespace std;

struct DSU {
    vector<int> p, r;
    explicit DSU(int n) : p(n+1), r(n+1, 0) { iota(p.begin(), p.end(), 0); }
    int find(int x){ return p[x]==x ? x : p[x]=find(p[x]); }
    bool unite(int a,int b){
        a=find(a); b=find(b);
        if(a==b) return false;
        if(r[a]<r[b]) swap(a,b);
        p[b]=a;
        if(r[a]==r[b]) ++r[a];       // why: keep trees shallow for near O(α(n))
        return true;
    }
};

struct Edge {
    int u,v,w;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    if (!(cin >> n >> m)) return 0;

    vector<Edge> edges;
    edges.reserve(m);
    for (int i = 0; i < m; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        edges.push_back({u, v, w});
    }

    sort(edges.begin(), edges.end(), [](const Edge& a, const Edge& b){
        if (a.w != b.w) return a.w < b.w;
        long long ka = (long long)a.u + a.v + a.w;
        long long kb = (long long)b.u + b.v + b.w;
        return ka < kb;
    });

    DSU dsu(n);
    long long ans = 0;
    int picked = 0;

    for (const auto& e : edges) {
        if (dsu.unite(e.u, e.v)) {
            ans += e.w;
            if (++picked == n - 1) break;
        }
    }

    cout << ans << "\n";
    return 0;
}
