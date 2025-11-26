// Number of island
#include <bits/stdc++.h>
using namespace std;

// Parse inputs like:
// [
//   ["1","1","0"],
//   ["0","1","0"]
// ]
static vector<vector<char>> parseGrid(const string& s) {
    vector<vector<char>> g;
    vector<char> row;
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
            if (depth >= 2) row.push_back(c);
        }
    }
    return g;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string all, line;
    while (getline(cin, line)) all += line;

    vector<vector<char>> grid = parseGrid(all);
    if (grid.empty()) { cout << 0 << "\n"; return 0; }

    const int m = (int)grid.size();
    const int n = (int)grid[0].size();
    int islands = 0;

    const int dr[4] = {1,-1,0,0};
    const int dc[4] = {0,0,1,-1};

    for (int r = 0; r < m; ++r) {
        for (int c = 0; c < n; ++c) {
            if (grid[r][c] != '1') continue;
            ++islands;
            stack<pair<int,int> > st;
            st.push(make_pair(r,c));
            grid[r][c] = '0'; // why: mark visited in-place

            while (!st.empty()) {
                pair<int,int> p = st.top(); st.pop();
                int x = p.first, y = p.second;
                for (int k = 0; k < 4; ++k) {
                    int nx = x + dr[k], ny = y + dc[k];
                    if (nx >= 0 && nx < m && ny >= 0 && ny < n && grid[nx][ny] == '1') {
                        grid[nx][ny] = '0';
                        st.push(make_pair(nx, ny));
                    }
                }
            }
        }
    }

    cout << islands << "\n";
    return 0;
}
