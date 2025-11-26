// network delay time
#include <bits/stdc++.h>
using namespace std;

// Grab all non-negative integers from a string [helper]
static vector<int> extract_ints(const string& t) {
    vector<int> z;
    for (size_t i = 0; i < t.size(); ++i) {
        if (isdigit(t[i])) {
            long long x = 0;
            while (i < t.size() && isdigit(t[i])) { x = x*10 + (t[i]-'0'); ++i; }
            z.push_back((int)x);
        }
    }
    return z;
}

// Parse first top-level [[...]] into list of triples
static vector<array<int,3>> parse_times(const string& s, size_t& end_pos) {
    vector<array<int,3>> edges;
    end_pos = string::npos;

    size_t start = s.find("[[");
    if (start == string::npos) return edges;

    int depth = 0;
    vector<int> nums;
    for (size_t i = start; i < s.size(); ++i) {
        char c = s[i];
        if (c == '[') ++depth;
        else if (c == ']') {
            --depth;
            if (depth == 0) { end_pos = i; break; }
        } else if (isdigit(c)) {
            long long x = 0;
            while (i < s.size() && isdigit(s[i])) { x = x*10 + (s[i]-'0'); ++i; }
            nums.push_back((int)x);
            --i;
        }
    }
    for (size_t i = 0; i + 2 < nums.size(); i += 3) {
        edges.push_back({nums[i], nums[i+1], nums[i+2]});
    }
    return edges;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s, line;
    while (getline(cin, line)) s += line;

    // 1) parse times
    size_t arr_end;
    vector<array<int,3>> edges = parse_times(s, arr_end);

    // 2) parse n and k (from remainder or entire string if needed)
    int n = 0, k = 0;
    string tail = (arr_end != string::npos && arr_end + 1 < s.size()) ? s.substr(arr_end + 1) : s;
    vector<int> rest = extract_ints(tail);
    if (rest.size() >= 2) {
        n = rest[0];
        k = rest[1];
    } else {
        // fallback: try entire string (handles "times n k" without labels)
        rest = extract_ints(s);
        // remove numbers that belonged to edges
        size_t used = edges.size() * 3;
        if (rest.size() >= used + 2) {
            n = rest[used];
            k = rest[used + 1];
        }
    }

    if (n <= 0 || k <= 0) { cout << -1 << "\n"; return 0; }

    // 3) build graph 1..n
    vector<vector<pair<int,int>>> g(n + 1);
    for (const auto& e : edges) {
        int u = e[0], v = e[1], w = e[2];
        if (u >= 1 && u <= n && v >= 1 && v <= n) g[u].push_back({v, w});
    }

    // 4) Dijkstra
    const int INF = 1e9;
    vector<int> dist(n + 1, INF);
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;
    dist[k] = 0;
    pq.push({0, k});

    while (!pq.empty()) {
        pair<int,int> cur = pq.top(); pq.pop();
        int d = cur.first, u = cur.second;
        if (d != dist[u]) continue;
        for (size_t i = 0; i < g[u].size(); ++i) {
            int v = g[u][i].first, w = g[u][i].second;
            if (dist[v] > d + w) {
                dist[v] = d + w;
                pq.push({dist[v], v});
            }
        }
    }

    int ans = 0;
    for (int i = 1; i <= n; ++i) {
        if (dist[i] == INF) { cout << -1 << "\n"; return 0; }
        if (dist[i] > ans) ans = dist[i];
    }
    cout << ans << "\n";
    return 0;
}
