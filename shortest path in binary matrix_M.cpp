// shortest path in binary matrix
#include <bits/stdc++.h>
using namespace std;

// Parse inputs like [[0,1],[1,0]] (quotes/spaces/newlines ignored).
static vector<vector<int>> parseGrid(const string& s) {
    vector<vector<int>> g;
    vector<int> row;
    int depth = 0;
    for (size_t i = 0; i < s.size(); ++i) {
        char c = s[i];
        if (c == '[') {
            ++depth;
            if (depth == 2) row.clear();
        } else if (c == ']') {
            if (depth == 2) {
                if (!row.empty() || !g.empty()) g.push_back(row);
                row.clear();
            }
            --depth;
        } else if (c == '0' || c == '1') {
            if (depth >= 2) row.push_back(c - '0');
        }
    }
    return g;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string all, line;
    while (getline(cin, line)) all += line;

    vector<vector<int>> grid = parseGrid(all);
    if (grid.empty() || grid[0].empty()) { cout << -1 << "\n"; return 0; }

    int n = (int)grid.size();
    if ((int)grid[0].size() != n) { cout << -1 << "\n"; return 0; }

    if (grid[0][0] != 0 || grid[n-1][n-1] != 0) { cout << -1 << "\n"; return 0; }

    static const int dx[8] = {1,1,1,0,0,-1,-1,-1};
    static const int dy[8] = {1,0,-1,1,-1,1,0,-1};

    queue<pair<int,int> > q;
    grid[0][0] = 1;                 // distance from start (counts cells)
    q.push(make_pair(0,0));

    while (!q.empty()) {
        pair<int,int> p = q.front(); q.pop();
        int x = p.first, y = p.second;
        if (x == n-1 && y == n-1) { cout << grid[x][y] << "\n"; return 0; }
        for (int k = 0; k < 8; ++k) {
            int nx = x + dx[k], ny = y + dy[k];
            if (nx >= 0 && nx < n && ny >= 0 && ny < n && grid[nx][ny] == 0) {
                grid[nx][ny] = grid[x][y] + 1; // why: store distance in-place to avoid extra memory
                q.push(make_pair(nx, ny));
            }
        }
    }

    cout << -1 << "\n";
    return 0;
}
