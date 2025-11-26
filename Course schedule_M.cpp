//course schedule
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // Read everything from stdin (works for one-line or multi-line)
    string s, line;
    while (getline(cin, line)) s += line;

    // Extract all non-negative integers in order
    vector<int> nums;
    for (size_t i = 0; i < s.size(); ++i) {
        if (isdigit(s[i])) {
            long long x = 0;
            while (i < s.size() && isdigit(s[i])) { x = x*10 + (s[i]-'0'); ++i; }
            nums.push_back((int)x);
        }
    }

    if (nums.empty()) { cout << "false\n"; return 0; } // no input case

    int n = nums[0];
    if (n <= 0) { cout << "true\n"; return 0; }        // 0 courses is trivially finishable

    vector<vector<int>> adj(n);
    vector<int> indeg(n, 0);

    // Remaining numbers are pairs [a,b]
    for (size_t i = 1; i + 1 < nums.size(); i += 2) {
        int a = nums[i];
        int b = nums[i + 1];
        if (a < 0 || a >= n || b < 0 || b >= n) continue; // ignore out-of-range silently
        adj[b].push_back(a);       // edge: take b before a
        ++indeg[a];
    }

    queue<int> q;
    for (int i = 0; i < n; ++i) if (indeg[i] == 0) q.push(i);

    int taken = 0;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        ++taken;
        for (int v : adj[u]) {
            if (--indeg[v] == 0) q.push(v);
        }
    }

    cout << (taken == n ? "true" : "false") << "\n";
    return 0;
}
