//clone graph 
#include <bits/stdc++.h>
using namespace std;

struct Node {
    int val;
    vector<Node*> neighbors;
    Node(): val(0) {}
    explicit Node(int _val): val(_val) {}
    Node(int _val, vector<Node*> _n): val(_val), neighbors(move(_n)) {}
};

// --- Parser for inputs like [[2,4],[1,3]] / [[]] / [] ---
static vector<vector<int>> parseAdjList(const string& s) {
    vector<vector<int>> adj;
    if (s.empty()) return adj;
    int depth = 0;
    for (size_t i = 0; i < s.size(); ++i) {
        char c = s[i];
        if (c == '[') {
            ++depth;
            if (depth == 2) adj.emplace_back();          // new inner list
        } else if (c == ']') {
            if (depth == 0) continue;
            --depth;
        } else if (isdigit(c)) {
            long long x = 0;
            while (i < s.size() && isdigit(s[i])) { x = x*10 + (s[i]-'0'); ++i; }
            --i;
            if (!adj.empty()) adj.back().push_back((int)x);
        }
    }
    return adj;
}

// --- Clone Graph (BFS) ---
static Node* cloneGraph(Node* node) {
    if (!node) return nullptr;
    unordered_map<Node*, Node*> mp;
    queue<Node*> q;
    mp[node] = new Node(node->val);
    q.push(node);

    while (!q.empty()) {
        Node* cur = q.front(); q.pop();
        Node* curClone = mp[cur];
        for (Node* nb : cur->neighbors) {
            if (!mp.count(nb)) {
                mp[nb] = new Node(nb->val);              // why: ensure unique clone per original
                q.push(nb);
            }
            curClone->neighbors.push_back(mp[nb]);
        }
    }
    return mp[node];
}

// --- Build graph from adjacency list, nodes are 1..n ---
static Node* buildGraph(const vector<vector<int>>& adj) {
    if (adj.empty()) return nullptr;
    int n = (int)adj.size();
    vector<Node*> nodes(n + 1, nullptr);
    for (int i = 1; i <= n; ++i) nodes[i] = new Node(i);
    for (int i = 1; i <= n; ++i)
        for (int v : adj[i-1]) nodes[i]->neighbors.push_back(nodes[v]);
    return nodes[1];
}

// --- Collect adjacency of a connected clone and print as [[...],...] ---
static void printAdjFromClone(Node* start) {
    if (!start) { cout << "[]\n"; return; }
    unordered_map<int, vector<int>> adjMap;
    unordered_set<int> seen;
    queue<Node*> q;
    q.push(start); seen.insert(start->val);
    int maxVal = 0;

    while (!q.empty()) {
        Node* cur = q.front(); q.pop();
        maxVal = max(maxVal, cur->val);
        for (Node* nb : cur->neighbors) {
            adjMap[cur->val].push_back(nb->val);
            if (!seen.count(nb->val)) { seen.insert(nb->val); q.push(nb); }
        }
        sort(adjMap[cur->val].begin(), adjMap[cur->val].end());
    }

    int n = (int)seen.size();              // connected graph size
    cout << "[";
    for (int i = 1; i <= n; ++i) {
        cout << "[";
        if (adjMap.count(i)) {
            const auto& v = adjMap[i];
            for (size_t j = 0; j < v.size(); ++j) {
                if (j) cout << ",";
                cout << v[j];
            }
        }
        cout << "]";
        if (i != n) cout << ",";
    }
    cout << "]\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // Read entire input as one line (e.g., [[2,4],[1,3],[2,4],[1,3]])
    string input, line;
    while (getline(cin, line)) input += line;
    // Trim spaces
    input.erase(remove_if(input.begin(), input.end(), ::isspace), input.end());

    auto adj = parseAdjList(input);
    Node* original = buildGraph(adj);
    Node* cloned = cloneGraph(original);
    printAdjFromClone(cloned);
    return 0;
}
