// BFS Shortest Reach 
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int q;
    if (!(cin >> q)) return 0;
    while (q--) {
        int n, m;
        cin >> n >> m;
        vector<vector<int>> g(n + 1);
        g.shrink_to_fit();
        for (int i = 0; i < m; ++i) {
            int u, v;
            cin >> u >> v;
            if (u >= 1 && u <= n && v >= 1 && v <= n && u != v) {
                g[u].push_back(v);
                g[v].push_back(u);
            }
        }
        int s;
        cin >> s;

        vector<int> dist(n + 1, -1);
        queue<int> bfs;
        dist[s] = 0;
        bfs.push(s);

        while (!bfs.empty()) {
            int x = bfs.front(); bfs.pop();
            for (int y : g[x]) {
                if (dist[y] == -1) {            // why: first time = shortest hops
                    dist[y] = dist[x] + 1;
                    bfs.push(y);
                }
            }
        }

        bool first = true;
        for (int i = 1; i <= n; ++i) {
            if (i == s) continue;
            if (!first) cout << ' ';
            first = false;
            if (dist[i] == -1) cout << -1;
            else cout << dist[i] * 6;
        }
        cout << "\n";
    }
    return 0;
}
